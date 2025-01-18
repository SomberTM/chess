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

void test_starting_position_knight_moves() {
	MoveList actual = {};

	Game* game = create_game();

	MoveList expected = {
		.length = 8,
		.moves = {
			create_move(B1, A3, QUIET_MOVE), create_move(B1, C3, QUIET_MOVE),
			create_move(G1, F3, QUIET_MOVE), create_move(G1, H3, QUIET_MOVE),

			create_move(B8, A6, QUIET_MOVE), create_move(B8, C6, QUIET_MOVE),
			create_move(G8, F6, QUIET_MOVE), create_move(G8, H6, QUIET_MOVE),
		}
	};


	generate_knight_moves(&actual, game->pieces[WHITE][KNIGHT], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK));
	generate_knight_moves(&actual, game->pieces[BLACK][KNIGHT], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE));

	bool success = cmp_move_lists(&expected, &actual);
	TEST_ASSERT(success, "Move lists did not match expected %d moves got %d moves", expected.length, actual.length);

	destroy_game(&game);
}

void test_knight_moves_with_captures() {
	MoveList actual = {};

	Game* game = create_game();
	make_move(game, create_move(B1, C3, QUIET_MOVE));
	make_move(game, create_move(D7, D5, DOUBLE_PAWN_PUSH));

	MoveList expected = {
		.length = 12,
		.moves = {
			create_move(C3, B1, QUIET_MOVE), create_move(C3, A4, QUIET_MOVE),
			create_move(C3, B5, QUIET_MOVE), create_move(C3, E4, QUIET_MOVE),
			create_move(C3, D5, CAPTURE),

			create_move(G1, F3, QUIET_MOVE), create_move(G1, H3, QUIET_MOVE),

			create_move(B8, A6, QUIET_MOVE), create_move(B8, C6, QUIET_MOVE),
			create_move(B8, D7, QUIET_MOVE),
			create_move(G8, F6, QUIET_MOVE), create_move(G8, H6, QUIET_MOVE),
		}
	};

	generate_knight_moves(&actual, game->pieces[WHITE][KNIGHT], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK));
	generate_knight_moves(&actual, game->pieces[BLACK][KNIGHT], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE));

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

void test_knight_moves() {
	TEST(test_starting_position_knight_moves, "Starting position knight moves");
	TEST(test_knight_moves_with_captures, "Knight moves with captures");
}

void test_starting_position_bishop_moves() {
	MoveList actual = {};

	Game* game = create_game();

	MoveList expected = {
		.length = 0,
		.moves = {}
	};

	generate_bishop_moves(&actual, game->pieces[WHITE][BISHOP], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK));
	generate_bishop_moves(&actual, game->pieces[BLACK][BISHOP], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE));

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

void test_bishop_moves() {
	TEST(test_starting_position_bishop_moves, "Starting position bishop moves");
}

void test_starting_position_rook_moves() {
	MoveList actual = {};

	Game* game = create_game();

	MoveList expected = {
		.length = 0,
		.moves = {}
	};

	generate_rook_moves(&actual, game->pieces[WHITE][ROOK], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK));
	generate_rook_moves(&actual, game->pieces[BLACK][ROOK], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE));

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

void test_rook_moves() {
	TEST(test_starting_position_rook_moves, "Starting position rook moves");
}

void test_starting_position_queen_moves() {
	MoveList actual = {};

	Game* game = create_game();

	MoveList expected = {
		.length = 0,
		.moves = {}
	};

	generate_queen_moves(&actual, game->pieces[WHITE][QUEEN], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK));
	generate_queen_moves(&actual, game->pieces[BLACK][QUEEN], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE));

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

void test_queen_moves() {
	TEST(test_starting_position_queen_moves, "Starting position queen moves");
}

void test_starting_position_king_moves() {
	MoveList actual = {};

	Game* game = create_game();

	MoveList expected = {
		.length = 0,
		.moves = {}
	};

	generate_king_moves(&actual, game->pieces[WHITE][KING], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK), true, true);
	generate_king_moves(&actual, game->pieces[BLACK][KING], get_bitboard_for_color(game, BLACK), get_bitboard_for_color(game, WHITE), true, true);

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

void test_king_moves_with_captures() {
	MoveList actual = {};

	GameOptions options = { .empty_board = true };
	Game* game = create_game_with_options(options);

	put_piece(game, WHITE, KING, D4);
	put_piece(game, BLACK, PAWN, D5);
	put_piece(game, BLACK, PAWN, D3);
	put_piece(game, BLACK, PAWN, E4);
	put_piece(game, BLACK, PAWN, C4);

	MoveList expected = {
		.length = 8,
		.moves = {
			create_move(D4, C5, QUIET_MOVE), create_move(D4, E5, QUIET_MOVE),
			create_move(D4, C3, QUIET_MOVE), create_move(D4, E3, QUIET_MOVE),

			create_move(D4, D5, CAPTURE), create_move(D4, E4, CAPTURE),
			create_move(D4, D3, CAPTURE), create_move(D4, C4, CAPTURE)
		}
	};

	generate_king_moves(&actual, game->pieces[WHITE][KING], get_bitboard_for_color(game, WHITE), get_bitboard_for_color(game, BLACK), false, false);

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

void test_king_moves() {
	TEST(test_starting_position_king_moves, "Starting position king moves");
	TEST(test_king_moves_with_captures, "King moves with captures");
}

void test_prune_moves_putting_king_in_check() {
	MoveList actual = {};

	GameOptions options = { .empty_board = true };
	Game* game = create_game_with_options(options);

	game->has_kingside_castling_rights[WHITE] = false;
	game->has_queenside_castling_rights[WHITE] = false;

	put_piece(game, WHITE, KING, F1);
	put_piece(game, WHITE, PAWN, E2);
	put_piece(game, WHITE, BISHOP, F2);
	put_piece(game, BLACK, BISHOP, A6);
	put_piece(game, BLACK, ROOK, F8);

	MoveList expected = {
		.length = 3,
		.moves = {
			create_move(F1, E1, QUIET_MOVE), create_move(F1, G1, QUIET_MOVE), 
			create_move(F1, G2, QUIET_MOVE)
		}
	};

	// will only generate white moves
	game->turn = WHITE;
	generate_legal_moves(game, &actual);

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

void test_prune_illegal_moves() {
	TEST(test_prune_moves_putting_king_in_check, "Prune moves that put king in check");
}

void test_number_of_moves() {
	Game* game = create_game();

	MoveList moves = {};

	generate_moves(game, &moves);
	TEST_ASSERT(moves.length == 20, "Should have 20 starting moves");

	memset(&moves, 0, sizeof(moves));
	make_move(game, create_move(E2, E4, DOUBLE_PAWN_PUSH));
	make_move(game, create_move(E7, E5, DOUBLE_PAWN_PUSH));
	
	generate_moves(game, &moves);
	bool success = moves.length == 29;
	TEST_ASSERT(success, "Should have 29  moves after e2e4 and e7e5 got %d", moves.length);

	if (!success) {
		sort_move_list_by_from_square(&moves);
		TEST_LOG_MOVE_LIST(moves, "Actual");
	}

	destroy_game(&game);
}


void test_move_counts() {
	TEST(test_number_of_moves, "Number of moves");
}

int main() {
	TEST(test_create_moves, "Create moves");

	test_pawn_moves();
	test_knight_moves();
	test_bishop_moves();
	test_rook_moves();
	test_queen_moves();
	test_king_moves();

	test_move_counts();
	test_prune_illegal_moves();

	return 0;
}
