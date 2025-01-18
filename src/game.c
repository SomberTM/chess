#include <assert.h>
#include <stdlib.h>

#include "game.h"
#include "bitboard.h"

Game* create_game() {
	GameOptions options = {};
	return create_game_with_options(options);
}

Game* create_game_with_options(GameOptions options) {
	Game* game = malloc(sizeof(Game));
	assert(game != NULL);

	for (Color c = WHITE; c <= BLACK; c++) {
		for (Piece p = PAWN; p <= KING; p++) {
			Bitboard bb = 0;
			if (!options.empty_board)
				bb = create_bitboard_for_piece(c, p);
			game->pieces[c][p] = bb;
		}
	}

	game->turn = WHITE;
	game->halfmove_count = 0;
	game->fullmove_count = 0;

	game->has_kingside_castling_rights[WHITE] = true;
	game->has_queenside_castling_rights[WHITE] = true;

	game->has_kingside_castling_rights[BLACK] = true;
	game->has_queenside_castling_rights[BLACK] = true;

	return game;
}

void destroy_game(Game** game) {
	assert(game != NULL);
	free(*game);
	*game = NULL;
}

Move get_last_move(const Game* game) {
	assert(game != NULL);

	if (game->halfmove_count == 0) {
		return 0;
	}

	return game->move_history[game->halfmove_count - 1];
}

Bitboard get_bitboard_for_color(const Game* game, Color color) {
	assert(game != NULL);

	Bitboard for_color = create_bitboard();
	for (Piece piece = PAWN; piece <= KING; piece++) {
		for_color |= game->pieces[color][piece];
	}

	return for_color;
}

Bitboard get_bitboard_for_piece(const Game* game, Piece piece) {
	assert(game != NULL);
	assert(piece != NONE);

	return game->pieces[WHITE][piece] | game->pieces[BLACK][piece];
}

Bitboard get_bitboard(const Game* game) {
	assert(game != NULL);

	return get_bitboard_for_color(game, WHITE) | get_bitboard_for_color(game, BLACK);
}

bool get_piece_on_square(Bitboard pieces[2][6], Square square, PieceLocInfo* info) {
	Bitboard square_bitboard = square_to_bitboard(square);

	for (Color c = WHITE; c <= BLACK; c++) {
		for (Piece p = PAWN; p <= KING; p++) {
			Bitboard piece_bitboard = pieces[c][p];
			if (piece_bitboard & square_bitboard) {
				if (info != NULL) {
					info->color = c;
					info->piece = p;
					info->square = square;
				}
				return true;
			}
		}
	}

	return false;
}

Square get_en_pessant_square(const Game* game, Color color) {
	if (game->halfmove_count == 0) return NIL;

	Move last_move = game->move_history[game->halfmove_count - 1];
	if (get_flag(last_move) != DOUBLE_PAWN_PUSH) return NIL;

	Square from = get_from_square(last_move);
	Square to = get_to_square(last_move);

	if (to > from && color == BLACK) {
		// white move
		return to - 8;
	} else if (to < from && color == WHITE) {
		// black move
		return to + 8;
	}
}

void put_piece(Game* game, Color color, Piece piece, Square square) {
	assert(game != NULL);

	PieceLocInfo info;
	if (get_piece_on_square(game->pieces, square, &info)) {
		toggle_square(&game->pieces[info.color][info.piece], square);
	}

	game->pieces[color][piece] |= (1ULL << square);
}

void make_move(Game* game, Move move) {
	PieceLocInfo info;
	assert(get_piece_on_square(game->pieces, get_from_square(move), &info));
	make_move_for_piece(game, move, info.color, info.piece);
}

void make_move_for_piece(Game* game, Move move, Color color, Piece piece) {
	// disable for testing / spamming moves
	// assert(game->turn == color);

	// save the game state before applying the move
	for (Color c = WHITE; c <= BLACK; c++)
		for (Piece p = PAWN; p <= KING; p++) 
			game->history[game->halfmove_count][c][p] = game->pieces[c][p];

	Square from_square = get_from_square(move);
	Square to_square = get_to_square(move);
	MoveFlag flag = get_flag(move);
	Piece promotion_piece = get_promotion_piece(flag);

	PieceLocInfo captured_piece_info;

	toggle_square(&game->pieces[color][piece], from_square);

	switch (flag) {
		case QUIET_MOVE:
		case DOUBLE_PAWN_PUSH:
			toggle_square(&game->pieces[color][piece], to_square);
			break;
		case KINGSIDE_CASTLING:
			toggle_square(&game->pieces[color][piece], to_square);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? H1 : H8);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? F1 : F8);
			break;
		case QUEENSIDE_CASTLING:
			toggle_square(&game->pieces[color][piece], to_square);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? A1 : A8);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? D1 : D8);
			break;
		case CAPTURE:
			assert(get_piece_on_square(game->pieces, to_square, &captured_piece_info));
			toggle_square(&game->pieces[captured_piece_info.color][captured_piece_info.piece], captured_piece_info.square);

			toggle_square(&game->pieces[color][piece], to_square);
			break;
		case EN_PASSANT_CAPTURE:
			toggle_square(&game->pieces[color][piece], to_square);

			Square en_pessant_square = color == WHITE ? to_square - 8 : to_square + 8;
			toggle_rank(&game->pieces[!color][PAWN], en_pessant_square);
			break;
		case KNIGHT_PROMOTION:
		case BISHOP_PROMOTION:
		case ROOK_PROMOTION:
		case QUEEN_PROMOTION:
			toggle_square(&game->pieces[color][promotion_piece], to_square);
			break;
		case KNIGHT_PROMOTION_WITH_CAPTURE:
		case BISHOP_PROMOTION_WITH_CAPTURE:
		case ROOK_PROMOTION_WITH_CAPTURE:
		case QUEEN_PROMOTION_WITH_CAPTURE:
			assert(get_piece_on_square(game->pieces, to_square, &captured_piece_info));
			toggle_square(&game->pieces[captured_piece_info.color][captured_piece_info.piece], captured_piece_info.square);

			toggle_square(&game->pieces[color][promotion_piece], to_square);
			break;
	}

	if (piece == KING) {
		game->has_kingside_castling_rights[color] = false;
		game->has_queenside_castling_rights[color] = false;
	} else if (piece == ROOK) {
		if (from_square == A1 || from_square == A8)
			game->has_queenside_castling_rights[color] = false;
		if (from_square == H1 || from_square == H8)
			game->has_kingside_castling_rights[color] = false;
	}

	// we can increment full moves after black's turn
	if (game->turn == BLACK)
		game->fullmove_count++;

	game->turn = !game->turn;
	game->move_history[game->halfmove_count++] = move;
}

void undo_move(Game* game, Move move) {
	if (game->halfmove_count == 0) return;

	PieceLocInfo info;
	assert(get_piece_on_square(game->pieces, get_to_square(move), &info));
	undo_move_for_piece(game, move, info.color, info.piece);
}

void undo_move_for_piece(Game* game, Move move, Color color, Piece piece) {
	Bitboard pieces[2][6] = {};

	for (Color c = WHITE; c <= BLACK; c++) {
		for (Piece p = PAWN; p <= KING; p++) {
			pieces[c][p] = game->history[game->halfmove_count - 1][c][p];
			game->history[game->halfmove_count - 1][c][p] = 0;
		}
	}

	Square from_square = get_from_square(move);
	Square to_square = get_to_square(move);
	MoveFlag flag = get_flag(move);
	Piece promotion_piece = get_promotion_piece(flag);

	PieceLocInfo captured_piece_info;

	toggle_square(&game->pieces[color][piece], to_square);

	switch (flag) {
		case QUIET_MOVE:
		case DOUBLE_PAWN_PUSH:
			toggle_square(&game->pieces[color][piece], from_square);
			break;
		case KINGSIDE_CASTLING:
			toggle_square(&game->pieces[color][piece], from_square);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? H1 : H8);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? F1 : F8);
			game->has_kingside_castling_rights[color] = true;
			break;
		case QUEENSIDE_CASTLING:
			toggle_square(&game->pieces[color][piece], from_square);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? A1 : A8);
			toggle_square(&game->pieces[color][ROOK], color == WHITE ? D1 : D8);
			game->has_queenside_castling_rights[color] = true;
		case CAPTURE:
			toggle_square(&game->pieces[color][piece], from_square);

			assert(get_piece_on_square(pieces, to_square, &captured_piece_info));
			toggle_square(&game->pieces[captured_piece_info.color][captured_piece_info.piece], captured_piece_info.square);
			break;
		case EN_PASSANT_CAPTURE:
			toggle_square(&game->pieces[color][piece], from_square);

			Square en_pessant_square = color == WHITE ? to_square - 8 : to_square + 8;
			toggle_square(&game->pieces[!color][PAWN], en_pessant_square);
			break;
		case KNIGHT_PROMOTION:
		case BISHOP_PROMOTION:
		case ROOK_PROMOTION:
		case QUEEN_PROMOTION:
			toggle_square(&game->pieces[color][promotion_piece], from_square);
			break;
		case KNIGHT_PROMOTION_WITH_CAPTURE:
		case BISHOP_PROMOTION_WITH_CAPTURE:
		case ROOK_PROMOTION_WITH_CAPTURE:
		case QUEEN_PROMOTION_WITH_CAPTURE:
			assert(get_piece_on_square(pieces, to_square, &captured_piece_info));
			toggle_square(&game->pieces[captured_piece_info.color][captured_piece_info.piece], captured_piece_info.square);

			toggle_square(&game->pieces[color][promotion_piece], from_square);
			break;
	}

	if (game->turn == WHITE)
		game->fullmove_count--;

	game->turn = !game->turn;
	game->move_history[game->halfmove_count--] = 0;
}
