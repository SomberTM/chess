#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#define MOVE_LIST_CAPACITY 1024

#include <stddef.h>
#include <stdbool.h>

#include "move.h"

typedef struct {
    size_t length;
    Move moves[MOVE_LIST_CAPACITY];
} MoveList;

/**
 * Adds the given move to the provided move list ignoring duplicate moves
 */
void add_move(MoveList*, Move);
bool contains_move(const MoveList*, Move);
bool cmp_move_lists(const MoveList*, const MoveList*);
void sort_move_list_by_from_square(MoveList*);


#endif