#include "test_utils.h"
#include "bitboard.h"
#include "move.h"

typedef struct {
	uint8_t source;
	uint8_t dest;
	MoveFlag flag;
} MoveTest;

#define NUM_MOVE_TESTS 19
MoveTest move_tests[NUM_MOVE_TESTS] = {
	{ A2, A3, QUIET_MOVE },
	{ D1, F3, QUIET_MOVE },
	{ G1, F3, QUIET_MOVE },
	{ C1, C2, QUIET_MOVE },
	{ A2, A4, DOUBLE_PAWN_PUSH },
	{ E1, G1, KINGSIDE_CASTLING },
	{ E1, C1, QUEENSIDE_CASTLING },
	{ A3, B4, CAPTURE },
	{ A3, B5, CAPTURE },
	{ D1, D8, CAPTURE },
	{ E5, F6, EN_PASSANT_CAPTURE },
	{ G7, G8, KNIGHT_PROMOTION },
	{ E7, E8, BISHOP_PROMOTION },
	{ A7, A8, ROOK_PROMOTION },
	{ C7, C8, QUEEN_PROMOTION },
	{ G7, F8, KNIGHT_PROMOTION_WITH_CAPTURE },
	{ E7, F8, BISHOP_PROMOTION_WITH_CAPTURE },
	{ A7, B8, ROOK_PROMOTION_WITH_CAPTURE },
	{ C7, D8, QUEEN_PROMOTION_WITH_CAPTURE }
};

void test_create_moves() {
	for (int i = 0; i < NUM_MOVE_TESTS; i++) {
		MoveTest test = move_tests[i];
		Move move = create_move(test.source, test.dest, test.flag);
		TEST_LOG("Move %d to %d with flag %d", test.source, test.dest, test.flag);
		TEST_ASSERT(move == (test.source | (test.dest << 6) | (test.flag << 12)), "failed test");
	}
}

void test_initial_pawn_moves_no_occupied_squares() {
	Bitboard expected;
	Bitboard actual;

	// test white
	Bitboard white_pawns = WHITE_PAWN_LAYOUT;

	expected = create_bitboard();
	toggle_rank(&expected, RANK_3);
	toggle_rank(&expected, RANK_4);

	actual = generate_quiet_pawn_moves(white_pawns, 0, WHITE);

	TEST_LOG("Expected white pawn moves: %lld | Actual white pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White pawn moves invalid for initial layout");

	// test black
	Bitboard black_pawns = BLACK_PAWN_LAYOUT;

	expected = create_bitboard();
	toggle_rank(&expected, RANK_5);
	toggle_rank(&expected, RANK_6);

	actual = generate_quiet_pawn_moves(black_pawns, 0, BLACK);

	TEST_LOG("Expected black pawn moves: %lld | Actual black pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black pawn moves invalid for initial layout");
}

void test_initial_pawn_moves_with_occupied_squares() {
	Bitboard expected;
	Bitboard actual;

	// setup an occupied board for white and black
	Bitboard occupied = create_bitboard();
	toggle_square(&occupied, C3);
	toggle_square(&occupied, F4);
	toggle_square(&occupied, B6);
	toggle_square(&occupied, H5);

	// test white
	Bitboard white_pawns = WHITE_PAWN_LAYOUT;

	expected = create_bitboard();
	toggle_rank(&expected, RANK_3);
	toggle_rank(&expected, RANK_4);
	toggle_square(&expected, C3);
	toggle_square(&expected, F4);

	actual = generate_quiet_pawn_moves(white_pawns, occupied, WHITE);

	TEST_LOG("Expected white pawn moves: %lld | Actual white pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White pawn moves invalid for initial layout");

	// test black
	Bitboard black_pawns = BLACK_PAWN_LAYOUT;

	expected = create_bitboard();
	toggle_rank(&expected, RANK_5);
	toggle_rank(&expected, RANK_6);
	toggle_square(&expected, B6);
	toggle_square(&expected, H5);

	actual = generate_quiet_pawn_moves(black_pawns, occupied, BLACK);

	TEST_LOG("Expected black pawn moves: %lld | Actual black pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black pawn moves invalid for initial layout");
}

void test_pawn_moves_no_occupied_squares() {
	Bitboard expected;
	Bitboard actual;

	// test white
	Bitboard white_pawns = WHITE_PAWN_LAYOUT;
	// single push
	toggle_square(&white_pawns, C2);
	toggle_square(&white_pawns, C3);
	// double push
	toggle_square(&white_pawns, F2);
	toggle_square(&white_pawns, F4);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_3);
	toggle_rank(&expected, RANK_4);
	toggle_square(&expected, C3);
	toggle_square(&expected, F3);
	toggle_square(&expected, F4);
	toggle_square(&expected, F5);

	actual = generate_quiet_pawn_moves(white_pawns, 0, WHITE);

	TEST_LOG("Expected white pawn moves: %lld | Actual white pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White pawn moves invalid");

	// test black
	Bitboard black_pawns = BLACK_PAWN_LAYOUT;
	// single push
	toggle_square(&black_pawns, B7);
	toggle_square(&black_pawns, B6);
	// double push
	toggle_square(&black_pawns, F7);
	toggle_square(&black_pawns, F5);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_5);
	toggle_rank(&expected, RANK_6);
	toggle_square(&expected, B6);
	toggle_square(&expected, F6);
	toggle_square(&expected, F5);
	toggle_square(&expected, F4);

	actual = generate_quiet_pawn_moves(black_pawns, 0, BLACK);

	TEST_LOG("Expected black pawn moves: %lld | Actual black pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black pawn moves");
}

void test_pawn_moves_with_occupied_squares() {
	Bitboard expected;
	Bitboard actual;
	Bitboard occupied;

	// test white
	Bitboard white_pawns = WHITE_PAWN_LAYOUT;
	// single push
	toggle_square(&white_pawns, C2);
	toggle_square(&white_pawns, C3);
	// double push
	toggle_square(&white_pawns, F2);
	toggle_square(&white_pawns, F4);
	toggle_square(&white_pawns, B2);
	toggle_square(&white_pawns, B4);

	occupied = create_bitboard();
	toggle_square(&occupied, B5);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_3);
	toggle_rank(&expected, RANK_4);
	toggle_square(&expected, B3);
	toggle_square(&expected, B4);
	toggle_square(&expected, C3);
	toggle_square(&expected, F3);
	toggle_square(&expected, F4);
	toggle_square(&expected, F5);

	actual = generate_quiet_pawn_moves(white_pawns, occupied, WHITE);

	TEST_LOG("Expected white pawn moves: %lld | Actual white pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White pawn moves invalid");

	// test black
	Bitboard black_pawns = BLACK_PAWN_LAYOUT;
	// single push
	toggle_square(&black_pawns, B7);
	toggle_square(&black_pawns, B6);
	// double push
	toggle_square(&black_pawns, F7);
	toggle_square(&black_pawns, F5);

	occupied = create_bitboard();
	toggle_square(&occupied, F4);
	toggle_square(&occupied, B5);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_5);
	toggle_rank(&expected, RANK_6);
	toggle_square(&expected, B5);
	toggle_square(&expected, B6);
	toggle_square(&expected, F5);
	toggle_square(&expected, F6);

	actual = generate_quiet_pawn_moves(black_pawns, occupied, BLACK);

	TEST_LOG("Expected black pawn moves: %lld | Actual black pawn moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black pawn moves");
}

void test_en_pessant_moves() {
	Bitboard expected;
	Bitboard actual;
	Bitboard en_pessant;

	Bitboard white_pawns = WHITE_PAWN_LAYOUT;
	// double pawn push
	toggle_square(&white_pawns, C2);
	toggle_square(&white_pawns, C4);

	// simulate an en pessant bitboard generated by the game.
	// represents the capturable square by en pessant.
	en_pessant = create_bitboard();
	toggle_square(&en_pessant, C3);

	expected = create_bitboard();
	toggle_square(&expected, C3);

	actual = generate_en_pessant_pawn_moves(white_pawns, en_pessant, WHITE);
	TEST_ASSERT(expected == actual, "En pessant failed for white");

	Bitboard black_pawns = BLACK_PAWN_LAYOUT;
	// double pawn push
	toggle_square(&black_pawns, F7);
	toggle_square(&black_pawns, F5);

	en_pessant = create_bitboard();
	toggle_square(&en_pessant, F6);

	expected = create_bitboard();
	toggle_square(&expected, F6);

	actual = generate_en_pessant_pawn_moves(black_pawns, en_pessant, BLACK);
	TEST_ASSERT(expected == actual, "En pessant failed for black");
}

int main() {
	TEST(test_create_moves, "Create moves");
	TEST(test_initial_pawn_moves_no_occupied_squares, "Initial pawn moves no occupied squares");
	TEST(test_initial_pawn_moves_with_occupied_squares, "Initial pawn moves with occupied squares");
	TEST(test_pawn_moves_no_occupied_squares, "Pawn moves no occupied squares");
	TEST(test_pawn_moves_with_occupied_squares, "Pawn moves with occupied squares");
	TEST(test_en_pessant_moves, "En pessant");

	return 0;
}
