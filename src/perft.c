#include <string.h>
#include <stdio.h>

#include "perft.h"
#include "move_list.h"
#include "move_gen.h"

uint64_t perft(Game* game, int depth) {
    MoveList move_list = { .length = 0, .moves = {} };
    uint64_t nodes = 0;

    if (depth == 0) return 1ULL;

    generate_legal_moves(game, &move_list);

    if (depth == 1) return move_list.length;

    for (size_t i = 0; i < move_list.length; i++) {
        Move move = move_list.moves[i];
        make_move(game, move);
        uint64_t decremented_depth_nodes = perft(game, depth - 1);
        printf("%s%s: %lld\n", SQUARE_NAMES[get_from_square(move)], SQUARE_NAMES[get_to_square(move)], decremented_depth_nodes);
        nodes += decremented_depth_nodes;
        undo_move(game, move);
    }

    return nodes;
}