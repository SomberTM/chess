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

Bitboard generate_knight_moves(Bitboard knights) {
	Bitboard moves = create_bitboard();

	moves |= (knights >> 6) & ~FILE_G & ~FILE_H; // two left, one up
	moves |= (knights << 10) & ~FILE_G & ~FILE_H; // two left, one down
	moves |= (knights >> 10) & ~FILE_A & ~FILE_B; // two right, one up
	moves |= (knights << 6) & ~FILE_A & ~FILE_B; // two right, one down

	moves |= (knights >> 15) & ~FILE_H; // one left, two up
	moves |= (knights << 17) & ~FILE_H; // one left, two down
	moves |= (knights >> 17) & ~FILE_A; // one right, two up
	moves |= (knights << 15) & ~FILE_A; // one right, two down
	
	return moves;
}

Bitboard generate_quiet_knight_moves(Bitboard knights, Bitboard occupied_squares) {
	return generate_knight_moves(knights) & ~occupied_squares;
}

Bitboard generate_capture_knight_moves(Bitboard knights, Bitboard other_color_pieces) {
	return generate_knight_moves(knights) & other_color_pieces;
}
