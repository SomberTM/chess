#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#include "bitboard.h"
#include "move.h"

typedef struct {
	Bitboard white_pieces[6];
	Bitboard black_pieces[6];

	// length = halfmove_count
	Bitboard history[1024][2][6];
	Move move_history[1024];
	uint8_t halfmove_count;
	uint8_t fullmove_count;

	Color turn;
} Game;

Game* create_game();
void destroy_game(Game**);

Move get_last_move(const Game*);

Bitboard get_bitboard_for_color(const Game*, Color);
Bitboard get_bitboard_for_piece(const Game*, Piece);
Bitboard get_bitboard(const Game*);

// Gets en pessant opportunities for the current players turn
Bitboard get_en_pessant_bitboard(const Game*);

Piece get_piece_on_square(const Game*, uint8_t);

#endif // !GAME_H
