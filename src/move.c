#include <assert.h>

#include "move.h"
#include "bitboard.h"

Move create_move(uint8_t from, uint8_t to, MoveFlag flag) {
	assert(from != to);

	return from | (to << 6) | (flag << 12);
}

uint8_t get_from_square(Move move) {
	return move & 0x3F;
}

uint8_t get_to_square(Move move) {
	return (move >> 6) & 0x3F;
}

MoveFlag get_flag(Move move) {
	return (move >> 12) & 0xF;
}

Bitboard generate_quiet_pawn_moves(Bitboard pawns, Bitboard occupied_squares, Color color) {
	Bitboard single_push;
	Bitboard double_push;
	Bitboard unoccupied_squares = ~occupied_squares;

	if (color == WHITE) {
		single_push = (pawns >> 8) & unoccupied_squares;
		double_push = ((pawns & RANK_2) >> 16) & unoccupied_squares;
	} else if (color == BLACK) {
		single_push = (pawns << 8) & unoccupied_squares;
		double_push = ((pawns & RANK_7) << 16) & unoccupied_squares;
	}

	return single_push | double_push;
}

Bitboard generate_capture_pawn_moves(Bitboard pawns, Bitboard other_color_pieces, Color color) {
	Bitboard left_captures;
	Bitboard right_captures;

	if (color == WHITE) {
		left_captures = (pawns >> 7) & other_color_pieces & ~FILE_H;
		right_captures = (pawns >> 9) & other_color_pieces & ~FILE_A;
	} else if (color == BLACK) {
		left_captures = (pawns << 9) & other_color_pieces & ~FILE_H;
		right_captures = (pawns << 7) & other_color_pieces & ~FILE_A;
	}

	return left_captures | right_captures;
}

Bitboard generate_en_pessant_pawn_moves(Bitboard pawns, Bitboard en_pessant_bitboard, Color color) {
	return generate_capture_pawn_moves(pawns, en_pessant_bitboard, color);
}
