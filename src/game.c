#include <assert.h>
#include <stdlib.h>

#include "game.h"
#include "bitboard.h"

Game* create_game() {
	Game* game = malloc(sizeof(Game));
	assert(game != NULL);

	game->white_pieces[PAWN] = create_bitboard_for_piece(WHITE, PAWN);
	game->white_pieces[KNIGHT] = create_bitboard_for_piece(WHITE, KNIGHT);
	game->white_pieces[BISHOP] = create_bitboard_for_piece(WHITE, BISHOP);
	game->white_pieces[ROOK] = create_bitboard_for_piece(WHITE, ROOK);
	game->white_pieces[QUEEN] = create_bitboard_for_piece(WHITE, QUEEN);
	game->white_pieces[KING] = create_bitboard_for_piece(WHITE, KING);

	game->black_pieces[PAWN] = create_bitboard_for_piece(BLACK, PAWN);
	game->black_pieces[KNIGHT] = create_bitboard_for_piece(BLACK, KNIGHT);
	game->black_pieces[BISHOP] = create_bitboard_for_piece(BLACK, BISHOP);
	game->black_pieces[ROOK] = create_bitboard_for_piece(BLACK, ROOK);
	game->black_pieces[QUEEN] = create_bitboard_for_piece(BLACK, QUEEN);
	game->black_pieces[KING] = create_bitboard_for_piece(BLACK, KING);

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

	if (color == WHITE) {
		return game->white_pieces[PAWN]
			| game->white_pieces[KNIGHT]
			| game->white_pieces[BISHOP]
			| game->white_pieces[ROOK]
			| game->white_pieces[QUEEN]
			| game->white_pieces[KING];
	} else if (color == BLACK) {
		return game->black_pieces[PAWN]
			| game->black_pieces[KNIGHT]
			| game->black_pieces[BISHOP]
			| game->black_pieces[ROOK]
			| game->black_pieces[QUEEN]
			| game->black_pieces[KING];
	}

	return 0;
}

Bitboard get_bitboard_for_piece(const Game* game, Piece piece) {
	assert(game != NULL);
	assert(piece != NONE);

	return game->white_pieces[piece] | game->black_pieces[piece];
}

Bitboard get_bitboard(const Game* game) {
	assert(game != NULL);

	return get_bitboard_for_color(game, WHITE) | get_bitboard_for_color(game, BLACK);
}

Bitboard get_en_pessant_bitboard(const Game* game) {
	assert(game != NULL);

	Move last_move = get_last_move(game);
	if (last_move == 0) {
		return 0;
	}

	if (get_flag(last_move) != DOUBLE_PAWN_PUSH) {
		return 0;
	}

	Bitboard bitboard = create_bitboard();

	uint8_t from = get_from_square(last_move);
	uint8_t to = get_to_square(last_move);

	if (to > from) {
		toggle_square(&bitboard, to - 8);
	} else {
		toggle_square(&bitboard, from - 8);
	}

	return bitboard;
}

Piece get_piece_on_square(const Game* game, uint8_t square) {
	assert(game != NULL);

	Bitboard square_bb = (1ULL << square);
	if (get_bitboard_for_piece(game, PAWN) & square_bb) return PAWN;
	if (get_bitboard_for_piece(game, KNIGHT) & square_bb) return KNIGHT;
	if (get_bitboard_for_piece(game, BISHOP) & square_bb) return BISHOP;
	if (get_bitboard_for_piece(game, ROOK) & square_bb) return ROOK;
	if (get_bitboard_for_piece(game, QUEEN) & square_bb) return QUEEN;
	if (get_bitboard_for_piece(game, KING) & square_bb) return KING;

	return NONE;
}
