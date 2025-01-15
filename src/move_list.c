#include <stdlib.h>

#include "move_list.h"

void add_move(MoveList* move_list, Move move) {
    if (contains_move(move_list, move)) return;

    move_list->moves[move_list->length++] = move;
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
    return ((int)get_from_square(ma)) - ((int)get_from_square(mb));
}

void sort_move_list_by_from_square(MoveList* move_list) {
    qsort(move_list->moves, move_list->length, sizeof(Move), compare_moves);
}