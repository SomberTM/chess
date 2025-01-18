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
void generate_king_moves(MoveList*, Bitboard, Bitboard, Bitboard, bool, bool);

// Generates moves for the current sides turn based on the game and board state
void generate_moves(const Game*, MoveList*);

// Generates moves for the current color based on the board state,
// it doesnt take into account whose turn it is accoridng to the game
void generate_moves_for_color(const Game*, MoveList*, Color);

void prune_illegal_moves(Game*, MoveList*, Color);

void generate_legal_moves(Game*, MoveList*);

bool is_king_in_check(const Game*, const MoveList*, Color);

#endif