#include "test_utils.h"
#include "game.h"

void test_make_promotion_moves() {
    GameOptions options = { .empty_board = true };
    Game* game = create_game_with_options(options);

    put_piece(game, WHITE, PAWN, E7);
    put_piece(game, WHITE, PAWN, C7);
    put_piece(game, BLACK, KNIGHT, D8);

    make_move(game, create_move(E7, D8, QUEEN_PROMOTION_WITH_CAPTURE));
    make_move(game, create_move(C7, C8, KNIGHT_PROMOTION));

    PieceLocInfo info;
    TEST_ASSERT(get_piece_on_square(game->pieces, D8, &info) && info.piece == QUEEN, "Pawn capture promotion to queen");
    TEST_ASSERT(get_piece_on_square(game->pieces, C8, &info) && info.piece == KNIGHT, "Pawn promoted to knight");
}

int main() {
    TEST(test_make_promotion_moves, "Pawn promotion moves");

    return 0;
}