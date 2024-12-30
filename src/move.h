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

Move create_move(uint8_t, uint8_t, MoveFlag);
uint8_t get_from_square(Move);
uint8_t get_to_square(Move);
MoveFlag get_flag(Move);

// might consider making moves color independent. i.e. have some mechanism
// for flipping and inverting black bitboards and treat them as white. Transformation
// opeartion may occur before or as part of the method idk.

// Simply generates the single/double push pawn moves, ignoring captures
// and special cases such as en pessant.
Bitboard generate_quiet_pawn_moves(Bitboard, Bitboard, Color);
// Generates the captures pawns can make ignoring en pessant
Bitboard generate_capture_pawn_moves(Bitboard, Bitboard, Color);
// Generates the en pessant captures pawns can make
Bitboard generate_en_pessant_pawn_moves(Bitboard, Bitboard, Color);

Bitboard generate_knight_moves(Bitboard);
Bitboard generate_quiet_knight_moves(Bitboard, Bitboard);
Bitboard generate_capture_knight_moves(Bitboard, Bitboard);

#endif // !MOVE_H
