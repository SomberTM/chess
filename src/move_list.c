#include <stdlib.h>
#include <assert.h>

#include "move_list.h"

void add_move(MoveList* move_list, Move move) {
    if (contains_move(move_list, move)) return;

    move_list->moves[move_list->length++] = move;
}

void remove_move(MoveList* move_list, Move move) {
    size_t idx;

    for (idx = 0; idx < move_list->length; idx++) {
        if (move_list->moves[idx] == move) break;
    } 

    remove_move_at(move_list, idx);
}

void remove_move_at(MoveList* move_list, size_t idx) {
    assert(idx < move_list->length);

    move_list->moves[idx] = 0;

    for (size_t i = idx+ 1; i < move_list->length; i++) {
        move_list->moves[i - 1] = move_list->moves[i];
    }

    move_list->length--;
}

bool contains_move(const MoveList* move_list, Move move) {
    if (move_list->length == 0) return false;

    for (size_t i = 0; i < move_list->length; i++)
        if (move_list->moves[i] == move) return true;
    
    return false;
}

bool cmp_move_lists(const MoveList* lhs, const MoveList* rhs) {
    if (lhs->length != rhs->length) return false;

    for (size_t i = 0; i < lhs->length; i++) 
        if (!contains_move(rhs, lhs->moves[i])) return false;

    return true;
}

int compare_moves(const void* a, const void* b) {
    Move ma = *(Move*)a;
    Move mb = *(Move*)b;

    int from_a = get_from_square(ma);
    int from_b = get_from_square(mb); 

    if (from_a == from_b)
        return ((int)get_to_square(ma)) - ((int)get_to_square(mb));

    return from_a - from_b;
}

void sort_move_list_by_from_square(MoveList* move_list) {
    qsort(move_list->moves, move_list->length, sizeof(Move), compare_moves);
}
