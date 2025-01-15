#include <assert.h>
#include <stdlib.h>

#include "game.h"
#include "bitboard.h"

Game* create_game() {
	GameOptions options = {}
	return create_game_with_options(options);
}

Game* create_game_with_options(GameOptions options) {
	Game* game = malloc(sizeof(Game));
	assert(game != NULL);

	if (!options.empty_board) {
		for (Color c = WHITE; c <= BLACK; c++) {
			for (Piece p = PAWN; p <= KING; p++) {
				game->pieces[c][p] = create_bitboard_for_piece(c, p);
			}
		}
	}

	game->turn = WHITE;
	game->halfmove_count = 0;
	game->fullmove_count = 0;
	game->has_king_moved[WHITE] = false;
	game->has_king_moved[BLACK] = false;

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

bool get_piece_on_square(const Game* game, Square square, PieceLocInfo* info) {
	Bitboard square_bitboard = square_to_bitboard(square);

	for (Color c = WHITE; c <= BLACK; c++) {
		for (Piece p = PAWN; p <= KING; p++) {
			Bitboard piece_bitboard = game->pieces[c][p];
			if (piece_bitboard & square_bitboard) {
				info->color = c;
				info->piece = p;
				info->square = square;
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

void make_move(Game* game, Move move) {
	PieceLocInfo info;
	assert(get_piece_on_square(game, get_from_square(move), &info));
	make_move_for_piece(game, move, info.color, info.piece);
}

void make_move_for_piece(Game* game, Move move, Color color, Piece piece) {
	// disable for testing / spamming moves
	// assert(game->turn == color);

	// save the game state before applying the move
	for (Color c = WHITE; c <= BLACK; c++)
		for (Piece p = PAWN; p <= KING; p++) 
			game->history[game->halfmove_count][c][p] = game->pieces[c][p];

	switch (get_flag(move)) {
		case QUIET_MOVE:
		case DOUBLE_PAWN_PUSH:
			toggle_square(&game->pieces[color][piece], get_from_square(move));
			toggle_square(&game->pieces[color][piece], get_to_square(move));
			break;
	}

	// we can increment full moves after black's turn
	if (game->turn == BLACK)
		game->fullmove_count++;

	game->turn = !game->turn;
	game->move_history[game->halfmove_count++] = move;
}
