#include <assert.h>

#include "bitboard.h"
#include "move.h"
#include "misc.h"

Move create_move(Square from, Square to, MoveFlag flag) {
	assert(from != to);

	return from | (to << 6) | (flag << 12);
}

inline Square get_from_square(Move move) {
	return (move & 0x3F);
}

inline Square get_to_square(Move move) {
	return ((move >> 6) & 0x3F);
}

inline MoveFlag get_flag(Move move) {
	return ((move >> 12) & 0xF);
}

/*
Bitboard generate_knight_moves(Bitboard knights) {
	Bitboard moves = create_bitboard();

	moves |= (knights << 6) & ~FILE_G & ~FILE_H; // two left, one up
	moves |= (knights >> 10) & ~FILE_G & ~FILE_H; // two left, one down
	moves |= (knights << 10) & ~FILE_A & ~FILE_B; // two right, one up
	moves |= (knights >> 6) & ~FILE_A & ~FILE_B; // two right, one down

	moves |= (knights << 15) & ~FILE_H; // one left, two up
	moves |= (knights >> 17) & ~FILE_H; // one left, two down
	moves |= (knights << 17) & ~FILE_A; // one right, two up
	moves |= (knights >> 15) & ~FILE_A; // one right, two down
	
	return moves;
}

Bitboard generate_quiet_knight_moves(Bitboard knights, Bitboard occupied_squares) {
	return generate_knight_moves(knights) & ~occupied_squares;
}

Bitboard generate_capture_knight_moves(Bitboard knights, Bitboard other_color_pieces) {
	return generate_knight_moves(knights) & other_color_pieces;
}

// Update with magic bbs in the future
Bitboard generate_quiet_rook_moves(Bitboard rooks, Bitboard occupied_squares) {
	Bitboard moves = create_bitboard();

	while (rooks) {
		Square rook_square = pop_lsb_position(&rooks);

		// enumerate all 4 cardinal direction until we hit an occupied square
		// we use char as our loop var type since it can be < 0, an unsigned int
		// type such as Square would overflow.

		for (char i = rook_square + EAST; i % 8 != 0; i += EAST) {
			Bitboard target = 1ULL << i;
			if (occupied_squares & target) break;
			moves |= target;
		}

		for (char i = rook_square + WEST; (i + 1) % 8 != 0; i += WEST) {
			Bitboard target = 1ULL << i;
			if (occupied_squares & target) break;
			moves |= target;
		}

		for (char i = rook_square + NORTH; i < 64; i += NORTH) {
			Bitboard target = 1ULL << i;
			if (occupied_squares & target) break;
			moves |= target;
		}

		for (char i = rook_square + SOUTH; i >= 0; i += SOUTH) {
			Bitboard target = 1ULL << i;
			if (occupied_squares & target) break;
			moves |= target;
		}
	}

	return moves;
}

Bitboard generate_capture_rook_moves(Bitboard rooks, Bitboard other_pieces) {
	Bitboard captures = create_bitboard();

	while (rooks) {
		Square rook_square = pop_lsb_position(&rooks);

		// enumerate all 4 cardinal direction until we hit an occupied square
		// we use char as our loop var type since it can be < 0, an unsigned int
		// type such as Square would overflow.

		for (char i = rook_square + EAST; i % 8 != 0; i += EAST) {
			Bitboard target = 1ULL << i;
			if (other_pieces & target) { 
				captures |= target;
				break;
			}
		}

		for (char i = rook_square + WEST; (i + 1) % 8 != 0; i += WEST) {
			Bitboard target = 1ULL << i;
			if (other_pieces & target) { 
				captures |= target;
				break;
			}
		}

		for (char i = rook_square + NORTH; i < 64; i += NORTH) {
			Bitboard target = 1ULL << i;
			if (other_pieces & target) { 
				captures |= target;
				break;
			}
		}

		for (char i = rook_square + SOUTH; i >= 0; i += SOUTH) {
			Bitboard target = 1ULL << i;
			if (other_pieces & target) { 
				captures |= target;
				break;
			}
		}
	}

	return captures;
}
*/