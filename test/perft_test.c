#include "test_utils.h"
#include "perft.h"

void test_perft_starting_position() {
    Game* game = create_game();

    const uint64_t expected_perft_results[6] = {1, 20, 400, 8902, 197281, 4865609};
    size_t num_expected_perft_results = sizeof(expected_perft_results) / sizeof(expected_perft_results[0]);

    for (size_t i = 0; i < num_expected_perft_results; i++) {
        uint64_t nodes = perft(game, i);
        uint64_t expected = expected_perft_results[i];
        TEST_ASSERT(nodes == expected, "Failed perft depth %d expected %d got %d", i, expected, nodes);
    }
}

int main(int argc, const char* argv[]) {
    test_perft_starting_position();
}