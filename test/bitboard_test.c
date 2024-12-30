#include "bitboard.h"
#include "test_utils.h"

void test_create_white_pawn_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, PAWN);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0xff000000000000, "Incorrect white pawn bitboard");
}

void test_create_white_knight_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, KNIGHT);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x4200000000000000, "Incorrect white knight bitboard");
}

void test_create_white_bishop_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, BISHOP);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x2400000000000000, "Incorrect white bishop bitboard");
}

void test_create_white_rook_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, ROOK);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x8100000000000000, "Incorrect white rook bitboard");
}

void test_create_white_queen_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, QUEEN);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x800000000000000, "Incorrect white queen bitboard");
}

void test_create_white_king_bitboard() {
	Bitboard bb = create_bitboard_for_piece(WHITE, KING);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x1000000000000000, "Incorrect white king bitboard");
}


void test_create_black_pawn_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, PAWN);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0xff00, "Incorrect black pawn bitboard");
}

void test_create_black_knight_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, KNIGHT);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x42, "Incorrect black knight bitboard");
}

void test_create_black_bishop_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, BISHOP);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x24, "Incorrect black bishop bitboard");
}

void test_create_black_rook_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, ROOK);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x81, "Incorrect black rook bitboard");
}

void test_create_black_queen_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, QUEEN);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x8, "Incorrect black queen bitboard");
}

void test_create_black_king_bitboard() {
	Bitboard bb = create_bitboard_for_piece(BLACK, KING);
	TEST_LOG_BB(bb);
	TEST_ASSERT(bb == 0x10, "Incorrect black king bitboard");
}

int main() {
	TEST(test_create_white_pawn_bitboard, "Default white pawn bitboard");
	TEST(test_create_white_knight_bitboard, "Default white knight bitboard");
	TEST(test_create_white_bishop_bitboard, "Default white bishop bitboard");
	TEST(test_create_white_rook_bitboard, "Default white rook bitboard");
	TEST(test_create_white_queen_bitboard, "Default white queen bitboard");
	TEST(test_create_white_king_bitboard, "Default white king bitboard");


	TEST(test_create_black_pawn_bitboard, "Default black pawn bitboard");
	TEST(test_create_black_knight_bitboard, "Default black knight bitboard");
	TEST(test_create_black_bishop_bitboard, "Default black bishop bitboard");
	TEST(test_create_black_rook_bitboard, "Default black rook bitboard");
	TEST(test_create_black_queen_bitboard, "Default black queen bitboard");
	TEST(test_create_black_king_bitboard, "Default black king bitboard");
}
