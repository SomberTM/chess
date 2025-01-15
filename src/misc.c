#include "misc.h"

Bitboard pop_lsb(Bitboard* bb) {
    Bitboard lsb = *bb & -*bb;
    *bb &= (*bb - 1);
    return lsb;
}

Square pop_lsb_position(Bitboard* bb) {
    Square position = __builtin_ctzll(*bb);
    *bb &= (*bb - 1);
    return position;
}
