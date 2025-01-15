#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include "move.h"
#include "bitboard.h"
#include "move_list.h"
#include "game.h"

// These are all pseudo-legal move generators meaning they do not prune moves
// that may put their own king in check

void generate_pawn_moves(MoveList*, Bitboard, Bitboard, Bitboard, Square, Color);
void generate_knight_moves(MoveList*, Bitboard, Bitboard, Bitboard);
void generate_bishop_moves(MoveList*, Bitboard, Bitboard, Bitboard);
void generate_rook_moves(MoveList*, Bitboard, Bitboard, Bitboard);
void generate_queen_moves(MoveList*, Bitboard, Bitboard, Bitboard);
void generate_king_moves(MoveList*, Bitboard, Bitboard, Bitboard);

void generate_moves(const Game*, MoveList*);

#endif