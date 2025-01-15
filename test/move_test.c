#include <string.h>

#include "test_utils.h"
#include "bitboard.h"
#include "move.h"
#include "move_gen.h"
#include "move_list.h"
#include "game.h"

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

/*
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

void test_pawn_moves_with_captures() {
	Bitboard expected;
	Bitboard actual;
	Bitboard occupied;
	
	Bitboard white_pawns = WHITE_PAWN_LAYOUT;
	toggle_square(&white_pawns, C2);
	toggle_square(&white_pawns, C4);
	toggle_square(&white_pawns, E2);
	toggle_square(&white_pawns, E4);

	occupied = create_bitboard();
	toggle_rank(&occupied, RANK_5);

	expected = create_bitboard();
	toggle_square(&expected, B5);
	toggle_square(&expected, D5);
	toggle_square(&expected, F5);

	actual = generate_capture_pawn_moves(white_pawns, occupied, WHITE);

	TEST_LOG("Expected white captures: %lld | Actual white captures: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White captures");

	Bitboard black_pawns = BLACK_PAWN_LAYOUT;
	toggle_square(&black_pawns , A7);
	toggle_square(&black_pawns , A5);
	toggle_square(&black_pawns , H7);
	toggle_square(&black_pawns , H5);

	occupied = create_bitboard();
	toggle_rank(&occupied, RANK_4);

	expected = create_bitboard();
	toggle_square(&expected, B4);
	toggle_square(&expected, G4);

	actual = generate_capture_pawn_moves(black_pawns, occupied, BLACK);

	TEST_LOG("Expected black captures: %lld | Actual black captures: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black captures");
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
	TEST_LOG("Expected en pessant moves: %lld | Actual en pessant moves: %lld", expected, actual);
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
	TEST_LOG("Expected en pessant moves: %lld | Actual en pessant moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "En pessant failed for black");
}

void test_intitial_knight_moves_no_occupied_squares() {
	Bitboard expected;
	Bitboard actual;

	Bitboard white_knights = create_bitboard_for_piece(WHITE, KNIGHT);

	expected = create_bitboard();
	toggle_square(&expected, A3);
	toggle_square(&expected, C3);
	toggle_square(&expected, F3);
	toggle_square(&expected, H3);

	actual = generate_quiet_knight_moves(white_knights, RANK_2); // only pawns as occupied
	TEST_LOG("Expected knight moves: %lld | Actual knight moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White knight moves");

	Bitboard black_knights = create_bitboard_for_piece(BLACK, KNIGHT);

	expected = create_bitboard();
	toggle_square(&expected, A6);
	toggle_square(&expected, C6);
	toggle_square(&expected, F6);
	toggle_square(&expected, H6);

	actual = generate_quiet_knight_moves(black_knights, RANK_7);
	TEST_LOG("Expected knight moves: %lld | Actual knight moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black knight moves");
}

void test_initial_rook_moves() {
	Bitboard expected;
	Bitboard actual;
	Bitboard occupied;

	Bitboard white_rooks = create_bitboard_for_piece(WHITE, ROOK);

	expected = 0;
	occupied = create_bitboard_for_piece(WHITE, KNIGHT) | create_bitboard_for_piece(WHITE, PAWN);
	actual = generate_quiet_rook_moves(white_rooks, occupied);

	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White rook moves with initial pawn and knight blockers");

	occupied = create_bitboard_for_piece(WHITE, PAWN);
	toggle_square(&occupied, A1);
	toggle_square(&occupied, H1);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_1);
	toggle_square(&expected, A1);
	toggle_square(&expected, H1);

	actual = generate_quiet_rook_moves(white_rooks, occupied);

	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White rook moves with pawn blockers and 1st rank open");


	Bitboard black_rooks = create_bitboard_for_piece(BLACK, ROOK);

	expected = 0;
	occupied = create_bitboard_for_piece(BLACK, KNIGHT) | create_bitboard_for_piece(BLACK, PAWN);
	actual = generate_quiet_rook_moves(black_rooks, occupied);

	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black rook moves with initial pawn and knight blockers");

	occupied = create_bitboard_for_piece(BLACK, PAWN);
	toggle_square(&occupied, A8);
	toggle_square(&occupied, H8);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_8);
	toggle_square(&expected, A8);
	toggle_square(&expected, H8);

	actual = generate_quiet_rook_moves(black_rooks, occupied);

	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "Black rook moves with pawn blockers and 1st rank open");
}

void test_rook_moves_with_occupied_squares() {
	Bitboard expected;
	Bitboard actual;
	Bitboard occupied;

	Bitboard white_rooks = create_bitboard();
	toggle_square(&white_rooks, C6);

	occupied = create_bitboard_for_piece(WHITE, PAWN) | create_bitboard_for_piece(BLACK, PAWN);
	toggle_square(&occupied, F6);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_6);
	toggle_square(&expected, C6);
	toggle_square(&expected, F6);
	toggle_square(&expected, G6);
	toggle_square(&expected, H6);
	toggle_square(&expected, C5);
	toggle_square(&expected, C4);
	toggle_square(&expected, C3);

	actual = generate_quiet_rook_moves(white_rooks, occupied);
	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_ASSERT(expected == actual, "White rook moves with occupied squares");


	Bitboard black_rooks = create_bitboard();
	toggle_square(&black_rooks, C5);
	toggle_square(&black_rooks, F3);

	occupied = create_bitboard_for_piece(WHITE, PAWN) | create_bitboard_for_piece(BLACK, PAWN);
	toggle_square(&occupied, C5);
	toggle_square(&occupied, F3);

	expected = create_bitboard();
	toggle_rank(&expected, RANK_5);
	toggle_rank(&expected, RANK_3);
	toggle_square(&expected, C6);
	toggle_square(&expected, C5);
	toggle_square(&expected, C4);
	toggle_square(&expected, F6);
	toggle_square(&expected, F4);
	toggle_square(&expected, F3);

	actual = generate_quiet_rook_moves(black_rooks, occupied);
	TEST_LOG("Expected rook moves: %lld | Actual rook moves: %lld", expected, actual);
	TEST_LOG_BB_PRETTY(expected);
	TEST_LOG_BB_PRETTY(actual);
	TEST_ASSERT(expected == actual, "White rook moves with occupied squares");
}
*/

void test_starting_position_pawn_moves() {
	MoveList actual = { 0, {} };

	Game* game = create_game();

	Bitboard position = get_bitboard(game);

	MoveList expected = { 
		.length = 32, 
		.moves = {
			create_move(A2, A3, QUIET_MOVE), create_move(A2, A4, DOUBLE_PAWN_PUSH),
			create_move(B2, B3, QUIET_MOVE), create_move(B2, B4, DOUBLE_PAWN_PUSH),
        	create_move(C2, C3, QUIET_MOVE), create_move(C2, C4, DOUBLE_PAWN_PUSH),
        	create_move(D2, D3, QUIET_MOVE), create_move(D2, D4, DOUBLE_PAWN_PUSH),
        	create_move(E2, E3, QUIET_MOVE), create_move(E2, E4, DOUBLE_PAWN_PUSH),
        	create_move(F2, F3, QUIET_MOVE), create_move(F2, F4, DOUBLE_PAWN_PUSH),
        	create_move(G2, G3, QUIET_MOVE), create_move(G2, G4, DOUBLE_PAWN_PUSH),
        	create_move(H2, H3, QUIET_MOVE), create_move(H2, H4, DOUBLE_PAWN_PUSH),

	        create_move(A7, A6, QUIET_MOVE), create_move(A7, A5, DOUBLE_PAWN_PUSH),
        	create_move(B7, B6, QUIET_MOVE), create_move(B7, B5, DOUBLE_PAWN_PUSH),
        	create_move(C7, C6, QUIET_MOVE), create_move(C7, C5, DOUBLE_PAWN_PUSH),
        	create_move(D7, D6, QUIET_MOVE), create_move(D7, D5, DOUBLE_PAWN_PUSH),
        	create_move(E7, E6, QUIET_MOVE), create_move(E7, E5, DOUBLE_PAWN_PUSH),
        	create_move(F7, F6, QUIET_MOVE), create_move(F7, F5, DOUBLE_PAWN_PUSH),
        	create_move(G7, G6, QUIET_MOVE), create_move(G7, G5, DOUBLE_PAWN_PUSH),
        	create_move(H7, H6, QUIET_MOVE), create_move(H7, H5, DOUBLE_PAWN_PUSH)
		}
	};

	generate_pawn_moves(&actual, game->pieces[WHITE][PAWN], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK), NIL, WHITE);
	generate_pawn_moves(&actual, game->pieces[BLACK][PAWN], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE), NIL, BLACK);

	bool success = cmp_move_lists(&expected, &actual);
	TEST_ASSERT(success, "Move lists did not match expected %d moves got %d moves", expected.length, actual.length);
	if (!success) {
		TEST_LOG_MOVE_LIST(expected, "Expected");
		TEST_LOG_MOVE_LIST(actual, "Actual");
	}

	destroy_game(&game);
}

void test_pawn_moves_with_occupied_and_captures_squares() {
	MoveList actual = { 0, {} };

	Game* game = create_game();
	// magical pawns can fly!
	make_move(game, create_move(A2, A6, QUIET_MOVE));
	make_move(game, create_move(G7, G3, QUIET_MOVE));
	make_move(game, create_move(D7, D4, QUIET_MOVE));

	Bitboard position = get_bitboard(game);

	MoveList expected = { 
		.length = 28, 
		.moves = {
			create_move(B2, B3, QUIET_MOVE), create_move(B2, B4, DOUBLE_PAWN_PUSH),
        	create_move(C2, C3, QUIET_MOVE), create_move(C2, C4, DOUBLE_PAWN_PUSH),
        	create_move(D2, D3, QUIET_MOVE),
        	create_move(E2, E3, QUIET_MOVE), create_move(E2, E4, DOUBLE_PAWN_PUSH),
        	create_move(F2, F3, QUIET_MOVE), create_move(F2, F4, DOUBLE_PAWN_PUSH),
        	create_move(H2, H3, QUIET_MOVE), create_move(H2, H4, DOUBLE_PAWN_PUSH),
			create_move(A6, B7, CAPTURE), create_move(F2, G3, CAPTURE), create_move(H2, G3, CAPTURE),

        	create_move(B7, B6, QUIET_MOVE), create_move(B7, B5, DOUBLE_PAWN_PUSH),
        	create_move(C7, C6, QUIET_MOVE), create_move(C7, C5, DOUBLE_PAWN_PUSH),
        	create_move(E7, E6, QUIET_MOVE), create_move(E7, E5, DOUBLE_PAWN_PUSH),
        	create_move(F7, F6, QUIET_MOVE), create_move(F7, F5, DOUBLE_PAWN_PUSH),
        	create_move(H7, H6, QUIET_MOVE), create_move(H7, H5, DOUBLE_PAWN_PUSH),
			create_move(D4, D3, QUIET_MOVE),
			create_move(B7, A6, CAPTURE), create_move(G3, F2, CAPTURE), create_move(G3, H2, CAPTURE)
		}
	};

	generate_pawn_moves(&actual, game->pieces[WHITE][PAWN], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK), NIL, WHITE);
	generate_pawn_moves(&actual, game->pieces[BLACK][PAWN], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE), NIL, BLACK);

	bool success = cmp_move_lists(&expected, &actual);
	TEST_ASSERT(success, "Move lists did not match expected %d moves got %d moves", expected.length, actual.length);
	if (!success) {
		sort_move_list_by_from_square(&expected);
		sort_move_list_by_from_square(&actual);
		TEST_LOG_MOVE_LIST(expected, "Expected");
		TEST_LOG_MOVE_LIST(actual, "Actual");
	}

	destroy_game(&game);
}

void test_pawn_moves_with_en_pessant() {
	MoveList actual = { 0, {} };

	Game* game = create_game();
	make_move(game, create_move(D7, D4, QUIET_MOVE));
	make_move(game, create_move(E2, E4, DOUBLE_PAWN_PUSH));

	Bitboard position = get_bitboard(game);

	MoveList expected = { 
		.length = 30, 
		.moves = {
			create_move(A2, A3, QUIET_MOVE), create_move(A2, A4, DOUBLE_PAWN_PUSH),
			create_move(B2, B3, QUIET_MOVE), create_move(B2, B4, DOUBLE_PAWN_PUSH),
        	create_move(C2, C3, QUIET_MOVE), create_move(C2, C4, DOUBLE_PAWN_PUSH),
        	create_move(D2, D3, QUIET_MOVE),
			create_move(E4, E5, QUIET_MOVE),
        	create_move(F2, F3, QUIET_MOVE), create_move(F2, F4, DOUBLE_PAWN_PUSH),
        	create_move(G2, G3, QUIET_MOVE), create_move(G2, G4, DOUBLE_PAWN_PUSH),
        	create_move(H2, H3, QUIET_MOVE), create_move(H2, H4, DOUBLE_PAWN_PUSH),

	        create_move(A7, A6, QUIET_MOVE), create_move(A7, A5, DOUBLE_PAWN_PUSH),
        	create_move(B7, B6, QUIET_MOVE), create_move(B7, B5, DOUBLE_PAWN_PUSH),
        	create_move(C7, C6, QUIET_MOVE), create_move(C7, C5, DOUBLE_PAWN_PUSH),
			create_move(D4, D3, QUIET_MOVE),
        	create_move(E7, E6, QUIET_MOVE), create_move(E7, E5, DOUBLE_PAWN_PUSH),
        	create_move(F7, F6, QUIET_MOVE), create_move(F7, F5, DOUBLE_PAWN_PUSH),
        	create_move(G7, G6, QUIET_MOVE), create_move(G7, G5, DOUBLE_PAWN_PUSH),
        	create_move(H7, H6, QUIET_MOVE), create_move(H7, H5, DOUBLE_PAWN_PUSH),
			create_move(D4, E3, EN_PASSANT_CAPTURE)
		}
	};

	generate_pawn_moves(&actual, game->pieces[WHITE][PAWN], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK), get_en_pessant_square(game, WHITE), WHITE);
	generate_pawn_moves(&actual, game->pieces[BLACK][PAWN], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE), get_en_pessant_square(game, BLACK), BLACK);

	bool success = cmp_move_lists(&expected, &actual);
	TEST_ASSERT(success, "Move lists did not match expected %d moves got %d moves", expected.length, actual.length);
	if (!success) {
		sort_move_list_by_from_square(&expected);
		sort_move_list_by_from_square(&actual);
		TEST_LOG_MOVE_LIST(expected, "Expected");
		TEST_LOG_MOVE_LIST(actual, "Actual");
	}

	destroy_game(&game);
}

void test_pawn_moves() {
	TEST(test_starting_position_pawn_moves, "Starting position pawn moves");
	TEST(test_pawn_moves_with_occupied_and_captures_squares, "Pawn moves with occupied and captures squares");
	TEST(test_pawn_moves_with_en_pessant, "Pawn moves with en pessant");
}

void test_number_of_starting_position_moves() {
	Game* game = create_game();

	MoveList moves = {};

	generate_moves(game, &moves);
	TEST_ASSERT(moves.length == 20, "Should have 20 starting moves");

	memset(&moves, 0, sizeof(moves));
	make_move(game, create_move(E2, E4, DOUBLE_PAWN_PUSH));
	make_move(game, create_move(E7, E5, DOUBLE_PAWN_PUSH));

	generate_moves(game, &moves);
	bool success = moves.length == 25;
	TEST_ASSERT(success, "Should have 19 moves after e2e4 and e7e5 got %d", moves.length);

	if (!success) {
		sort_move_list_by_from_square(&moves);
		TEST_LOG_MOVE_LIST(moves, "Actual");
	}

	destroy_game(&game);
}

void test_move_counts() {
	TEST(test_number_of_starting_position_moves, "Number of starting moves");
}

int main() {
	TEST(test_create_moves, "Create moves");

	test_move_counts();

	test_pawn_moves();

/*
	TEST(test_initial_pawn_moves_no_occupied_squares, "Initial pawn moves no occupied squares");
	TEST(test_initial_pawn_moves_with_occupied_squares, "Initial pawn moves with occupied squares");
	TEST(test_pawn_moves_no_occupied_squares, "Pawn moves no occupied squares");
	TEST(test_pawn_moves_with_occupied_squares, "Pawn moves with occupied squares");
	TEST(test_pawn_moves_with_captures, "Pawn moves with captures");
	TEST(test_en_pessant_moves, "En pessant");

	TEST(test_intitial_knight_moves_no_occupied_squares, "Initial knight moves no occupied squares");

	TEST(test_initial_rook_moves, "Initial rook moves");
	TEST(test_rook_moves_with_occupied_squares, "Rook moves with occupied squares");
*/

	return 0;
}
