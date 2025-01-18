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

Piece get_promotion_piece(MoveFlag flag) {
	switch (flag) {
		case KNIGHT_PROMOTION:
		case KNIGHT_PROMOTION_WITH_CAPTURE:
			return KNIGHT;
		case BISHOP_PROMOTION:
		case BISHOP_PROMOTION_WITH_CAPTURE:
			return BISHOP;
		case ROOK_PROMOTION:
		case ROOK_PROMOTION_WITH_CAPTURE:
			return ROOK;
		case QUEEN_PROMOTION:
		case QUEEN_PROMOTION_WITH_CAPTURE:
			return QUEEN;
		default:
			return NONE;
	}
}