#ifndef MISC_H
#define MISC_H

#include <stdint.h>
#include "bitboard.h"

Bitboard pop_lsb(Bitboard*);
Square pop_lsb_position(Bitboard*);

#endif