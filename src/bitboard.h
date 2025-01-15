#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

// Square-Representation using Little Endian Rank-File Mapping
typedef enum {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
	NIL	
} Square;

extern const char* SQUARE_NAMES[];

typedef uint64_t Bitboard;

// Ranks
extern const Bitboard RANK_1;
extern const Bitboard RANK_2;
extern const Bitboard RANK_3;
extern const Bitboard RANK_4;
extern const Bitboard RANK_5;
extern const Bitboard RANK_6;
extern const Bitboard RANK_7;
extern const Bitboard RANK_8;

// Files
extern const Bitboard FILE_A;
extern const Bitboard FILE_B;
extern const Bitboard FILE_C;
extern const Bitboard FILE_D;
extern const Bitboard FILE_E;
extern const Bitboard FILE_F;
extern const Bitboard FILE_G;
extern const Bitboard FILE_H;

// Compass Rose
extern const char NORTH;
extern const char NORTH_EAST;
extern const char EAST;
extern const char SOUTH_EAST;
extern const char SOUTH;
extern const char SOUTH_WEST;
extern const char WEST;
extern const char NORTH_WEST;


// Default white piece positions
extern const Bitboard WHITE_PAWN_LAYOUT;
extern const Bitboard WHITE_KNIGHT_LAYOUT;
extern const Bitboard WHITE_BISHOP_LAYOUT;
extern const Bitboard WHITE_ROOK_LAYOUT;
extern const Bitboard WHITE_QUEEN_LAYOUT;
extern const Bitboard WHITE_KING_LAYOUT;

// Default black piece positions
extern const Bitboard BLACK_PAWN_LAYOUT;
extern const Bitboard BLACK_KNIGHT_LAYOUT;
extern const Bitboard BLACK_BISHOP_LAYOUT;
extern const Bitboard BLACK_ROOK_LAYOUT;
extern const Bitboard BLACK_QUEEN_LAYOUT;
extern const Bitboard BLACK_KING_LAYOUT;

typedef enum {
	WHITE,
	BLACK
} Color;

typedef enum {
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	NONE
} Piece;

Bitboard create_bitboard();
Bitboard create_bitboard_for_piece(Color, Piece);
Bitboard square_to_bitboard(Square);
void print_bitboard(Bitboard);
void toggle_square(Bitboard*, Square);
void toggle_rank(Bitboard*, Bitboard);

#endif // !BITBOARD_H
