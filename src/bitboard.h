#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

// Square-Representation using Little Endian Rank-File Mapping
#define A1 56
#define B1 57
#define C1 58
#define D1 59
#define E1 60
#define F1 61
#define G1 62
#define H1 63

#define A2 48
#define B2 49
#define C2 50
#define D2 51
#define E2 52
#define F2 53
#define G2 54
#define H2 55

#define A3 40
#define B3 41
#define C3 42
#define D3 43
#define E3 44
#define F3 45
#define G3 46
#define H3 47

#define A4 32
#define B4 33
#define C4 34
#define D4 35
#define E4 36
#define F4 37
#define G4 38
#define H4 39

#define A5 24
#define B5 25
#define C5 26
#define D5 27
#define E5 28
#define F5 29
#define G5 30
#define H5 31

#define A6 16
#define B6 17
#define C6 18
#define D6 19
#define E6 20
#define F6 21
#define G6 22
#define H6 23

#define A7 8
#define B7 9
#define C7 10
#define D7 11
#define E7 12
#define F7 13
#define G7 14
#define H7 15

#define A8 0
#define B8 1
#define C8 2
#define D8 3
#define E8 4
#define F8 5
#define G8 6
#define H8 7

// Ranks
#define RANK_1 ((1ULL << A1) | (1ULL << B1) | (1ULL << C1) | (1ULL << D1) | (1ULL << E1) | (1ULL << F1) | (1ULL << G1) | (1ULL << H1))
#define RANK_2 ((1ULL << A2) | (1ULL << B2) | (1ULL << C2) | (1ULL << D2) | (1ULL << E2) | (1ULL << F2) | (1ULL << G2) | (1ULL << H2))
#define RANK_3 ((1ULL << A3) | (1ULL << B3) | (1ULL << C3) | (1ULL << D3) | (1ULL << E3) | (1ULL << F3) | (1ULL << G3) | (1ULL << H3))
#define RANK_4 ((1ULL << A4) | (1ULL << B4) | (1ULL << C4) | (1ULL << D4) | (1ULL << E4) | (1ULL << F4) | (1ULL << G4) | (1ULL << H4))
#define RANK_5 ((1ULL << A5) | (1ULL << B5) | (1ULL << C5) | (1ULL << D5) | (1ULL << E5) | (1ULL << F5) | (1ULL << G5) | (1ULL << H5))
#define RANK_6 ((1ULL << A6) | (1ULL << B6) | (1ULL << C6) | (1ULL << D6) | (1ULL << E6) | (1ULL << F6) | (1ULL << G6) | (1ULL << H6))
#define RANK_7 ((1ULL << A7) | (1ULL << B7) | (1ULL << C7) | (1ULL << D7) | (1ULL << E7) | (1ULL << F7) | (1ULL << G7) | (1ULL << H7))
#define RANK_8 ((1ULL << A8) | (1ULL << B8) | (1ULL << C8) | (1ULL << D8) | (1ULL << E8) | (1ULL << F8) | (1ULL << G8) | (1ULL << H8))

// Files
#define FILE_A ((1ULL << A1) | (1ULL << A2) | (1ULL << A3) | (1ULL << A4) | (1ULL << A5) | (1ULL << A6) | (1ULL << A7) | (1ULL << A8))
#define FILE_B ((1ULL << B1) | (1ULL << B2) | (1ULL << B3) | (1ULL << B4) | (1ULL << B5) | (1ULL << B6) | (1ULL << B7) | (1ULL << B8))
#define FILE_C ((1ULL << C1) | (1ULL << C2) | (1ULL << C3) | (1ULL << C4) | (1ULL << C5) | (1ULL << C6) | (1ULL << C7) | (1ULL << C8))
#define FILE_D ((1ULL << D1) | (1ULL << D2) | (1ULL << D3) | (1ULL << D4) | (1ULL << D5) | (1ULL << D6) | (1ULL << D7) | (1ULL << D8))
#define FILE_E ((1ULL << E1) | (1ULL << E2) | (1ULL << E3) | (1ULL << E4) | (1ULL << E5) | (1ULL << E6) | (1ULL << E7) | (1ULL << E8))
#define FILE_F ((1ULL << F1) | (1ULL << F2) | (1ULL << F3) | (1ULL << F4) | (1ULL << F5) | (1ULL << F6) | (1ULL << F7) | (1ULL << F8))
#define FILE_G ((1ULL << G1) | (1ULL << G2) | (1ULL << G3) | (1ULL << G4) | (1ULL << G5) | (1ULL << G6) | (1ULL << G7) | (1ULL << G8))
#define FILE_H ((1ULL << H1) | (1ULL << H2) | (1ULL << H3) | (1ULL << H4) | (1ULL << H5) | (1ULL << H6) | (1ULL << H7) | (1ULL << H8))

// Default white piece positions
#define WHITE_PAWN_LAYOUT ((1ULL << A2) | (1ULL << B2) | (1ULL << C2) | (1ULL << D2) | (1ULL << E2) | (1ULL << F2) | (1ULL << G2) | (1ULL << H2))
#define WHITE_KNIGHT_LAYOUT ((1ULL << B1) | (1ULL << G1))
#define WHITE_BISHOP_LAYOUT ((1ULL << C1) | (1ULL << F1))
#define WHITE_ROOK_LAYOUT ((1ULL << A1) | (1ULL << H1))
#define WHITE_QUEEN_LAYOUT (1ULL << D1)
#define WHITE_KING_LAYOUT (1ULL << E1)

// Default black piece positions
#define BLACK_PAWN_LAYOUT ((1ULL << A7) | (1ULL << B7) | (1ULL << C7) | (1ULL << D7) | (1ULL << E7) | (1ULL << F7) | (1ULL << G7) | (1ULL << H7))
#define BLACK_KNIGHT_LAYOUT ((1ULL << B8) | (1ULL << G8))
#define BLACK_BISHOP_LAYOUT ((1ULL << C8) | (1ULL << F8))
#define BLACK_ROOK_LAYOUT ((1ULL << A8) | (1ULL << H8))
#define BLACK_QUEEN_LAYOUT (1ULL << D8)
#define BLACK_KING_LAYOUT (1ULL << E8)

#define ULL uint64_t
typedef ULL Bitboard;

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
void print_bitboard(Bitboard);
void toggle_square(Bitboard*, uint8_t);
void toggle_rank(Bitboard*, Bitboard);

#endif // !BITBOARD_H
