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

void print_bitboard(Bitboard bitboard) {
	for (int i = 1; i <= 64; i++) {
		printf("%llu", (bitboard >> (i - 1)) & 1);

		if (i % 8 == 0) {
			printf("\n");
		}
	}

	printf("%llx\n", bitboard);
}

void toggle_square(Bitboard* bitboard, uint8_t square) {
	(*bitboard) ^= (1ULL << square);
}

void toggle_rank(Bitboard* bitboard, Bitboard rank) {
	(*bitboard) ^= rank;
}
