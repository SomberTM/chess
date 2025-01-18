#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>

#include "bitboard.h"

typedef enum {
	QUIET_MOVE,
	DOUBLE_PAWN_PUSH,
	KINGSIDE_CASTLING,
	QUEENSIDE_CASTLING,
	CAPTURE,
	EN_PASSANT_CAPTURE,
	KNIGHT_PROMOTION,
	BISHOP_PROMOTION,
	ROOK_PROMOTION,
	QUEEN_PROMOTION,
	KNIGHT_PROMOTION_WITH_CAPTURE,
	BISHOP_PROMOTION_WITH_CAPTURE,
	ROOK_PROMOTION_WITH_CAPTURE,
	QUEEN_PROMOTION_WITH_CAPTURE
} MoveFlag;

typedef uint16_t Move;

Move create_move(Square, Square, MoveFlag);
Square get_from_square(Move);
Square get_to_square(Move);
MoveFlag get_flag(Move);
Piece get_promotion_piece(MoveFlag);

#endif // !MOVE_H
