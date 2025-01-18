#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "bitboard.h"

Bitboard create_bitboard() {
	return 0;
}

Bitboard create_bitboard_for_piece(Color color, Piece piece) {
	Bitboard bitboard = create_bitboard();

	switch (piece) {
		case PAWN:
			bitboard = color == WHITE ? WHITE_PAWN_LAYOUT : BLACK_PAWN_LAYOUT;
			break;
		case KNIGHT:
			bitboard = color == WHITE ? WHITE_KNIGHT_LAYOUT : BLACK_KNIGHT_LAYOUT;
			break;
		case BISHOP:
			bitboard = color == WHITE ? WHITE_BISHOP_LAYOUT : BLACK_BISHOP_LAYOUT;
			break;
		case ROOK:
			bitboard = color == WHITE ? WHITE_ROOK_LAYOUT : BLACK_ROOK_LAYOUT;
			break;
		case QUEEN:
			bitboard = color == WHITE ? WHITE_QUEEN_LAYOUT : BLACK_QUEEN_LAYOUT;
			break;
		case KING:
			bitboard = color == WHITE ? WHITE_KING_LAYOUT : BLACK_KING_LAYOUT;
			break;
		case NONE:
			break;
	}

	return bitboard;
}

inline Bitboard square_to_bitboard(Square square) {
	return (1ULL << square);
}

void print_bitboard(Bitboard bitboard) {
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
            int s = (i * 8) + j;
            printf("%llu", (bitboard >> s) & 1);
        }
        printf("\n");
    } 
	printf("0x%llx\n", bitboard);
}

inline void toggle_square(Bitboard* bitboard, Square square) {
	(*bitboard) ^= (1ULL << square);
}

inline void toggle_rank(Bitboard* bitboard, Bitboard rank) {
	(*bitboard) ^= rank;
}

const Bitboard RANK_1 = ((1ULL << A1) | (1ULL << B1) | (1ULL << C1) | (1ULL << D1) | (1ULL << E1) | (1ULL << F1) | (1ULL << G1) | (1ULL << H1));
const Bitboard RANK_2 = ((1ULL << A2) | (1ULL << B2) | (1ULL << C2) | (1ULL << D2) | (1ULL << E2) | (1ULL << F2) | (1ULL << G2) | (1ULL << H2));
const Bitboard RANK_3 = ((1ULL << A3) | (1ULL << B3) | (1ULL << C3) | (1ULL << D3) | (1ULL << E3) | (1ULL << F3) | (1ULL << G3) | (1ULL << H3));
const Bitboard RANK_4 = ((1ULL << A4) | (1ULL << B4) | (1ULL << C4) | (1ULL << D4) | (1ULL << E4) | (1ULL << F4) | (1ULL << G4) | (1ULL << H4));
const Bitboard RANK_5 = ((1ULL << A5) | (1ULL << B5) | (1ULL << C5) | (1ULL << D5) | (1ULL << E5) | (1ULL << F5) | (1ULL << G5) | (1ULL << H5));
const Bitboard RANK_6 = ((1ULL << A6) | (1ULL << B6) | (1ULL << C6) | (1ULL << D6) | (1ULL << E6) | (1ULL << F6) | (1ULL << G6) | (1ULL << H6));
const Bitboard RANK_7 = ((1ULL << A7) | (1ULL << B7) | (1ULL << C7) | (1ULL << D7) | (1ULL << E7) | (1ULL << F7) | (1ULL << G7) | (1ULL << H7));
const Bitboard RANK_8 = ((1ULL << A8) | (1ULL << B8) | (1ULL << C8) | (1ULL << D8) | (1ULL << E8) | (1ULL << F8) | (1ULL << G8) | (1ULL << H8));

// Files
const Bitboard FILE_A = ((1ULL << A1) | (1ULL << A2) | (1ULL << A3) | (1ULL << A4) | (1ULL << A5) | (1ULL << A6) | (1ULL << A7) | (1ULL << A8));
const Bitboard FILE_B = ((1ULL << B1) | (1ULL << B2) | (1ULL << B3) | (1ULL << B4) | (1ULL << B5) | (1ULL << B6) | (1ULL << B7) | (1ULL << B8));
const Bitboard FILE_C = ((1ULL << C1) | (1ULL << C2) | (1ULL << C3) | (1ULL << C4) | (1ULL << C5) | (1ULL << C6) | (1ULL << C7) | (1ULL << C8));
const Bitboard FILE_D = ((1ULL << D1) | (1ULL << D2) | (1ULL << D3) | (1ULL << D4) | (1ULL << D5) | (1ULL << D6) | (1ULL << D7) | (1ULL << D8));
const Bitboard FILE_E = ((1ULL << E1) | (1ULL << E2) | (1ULL << E3) | (1ULL << E4) | (1ULL << E5) | (1ULL << E6) | (1ULL << E7) | (1ULL << E8));
const Bitboard FILE_F = ((1ULL << F1) | (1ULL << F2) | (1ULL << F3) | (1ULL << F4) | (1ULL << F5) | (1ULL << F6) | (1ULL << F7) | (1ULL << F8));
const Bitboard FILE_G = ((1ULL << G1) | (1ULL << G2) | (1ULL << G3) | (1ULL << G4) | (1ULL << G5) | (1ULL << G6) | (1ULL << G7) | (1ULL << G8));
const Bitboard FILE_H = ((1ULL << H1) | (1ULL << H2) | (1ULL << H3) | (1ULL << H4) | (1ULL << H5) | (1ULL << H6) | (1ULL << H7) | (1ULL << H8));

const char NORTH = 8;
const char NORTH_EAST = 9;
const char EAST = 1;
const char SOUTH_EAST = -7;
const char SOUTH = -8;
const char SOUTH_WEST = -9;
const char WEST = -1;
const char NORTH_WEST = 7;

// Default white piece positions
const Bitboard WHITE_PAWN_LAYOUT = ((1ULL << A2) | (1ULL << B2) | (1ULL << C2) | (1ULL << D2) | (1ULL << E2) | (1ULL << F2) | (1ULL << G2) | (1ULL << H2));
const Bitboard WHITE_KNIGHT_LAYOUT = ((1ULL << B1) | (1ULL << G1));
const Bitboard WHITE_BISHOP_LAYOUT = ((1ULL << C1) | (1ULL << F1));
const Bitboard WHITE_ROOK_LAYOUT = ((1ULL << A1) | (1ULL << H1));
const Bitboard WHITE_QUEEN_LAYOUT = (1ULL << D1);
const Bitboard WHITE_KING_LAYOUT = (1ULL << E1);

// Default black piece positions
const Bitboard BLACK_PAWN_LAYOUT = ((1ULL << A7) | (1ULL << B7) | (1ULL << C7) | (1ULL << D7) | (1ULL << E7) | (1ULL << F7) | (1ULL << G7) | (1ULL << H7));
const Bitboard BLACK_KNIGHT_LAYOUT = ((1ULL << B8) | (1ULL << G8));
const Bitboard BLACK_BISHOP_LAYOUT = ((1ULL << C8) | (1ULL << F8));
const Bitboard BLACK_ROOK_LAYOUT = ((1ULL << A8) | (1ULL << H8));
const Bitboard BLACK_QUEEN_LAYOUT = (1ULL << D8);
const Bitboard BLACK_KING_LAYOUT = (1ULL << E8);

const char* SQUARE_NAMES[] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "NIL"
};