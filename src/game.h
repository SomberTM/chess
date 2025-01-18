#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#include "bitboard.h"
#include "move.h"

typedef struct {
	bool empty_board;
} GameOptions;

typedef struct {
	Bitboard pieces[2][6];

	// index = halfmove_count
	Bitboard history[1024][2][6];
	Move move_history[1024];
	uint8_t halfmove_count;
	uint8_t fullmove_count;

	// indexed by color, returns true/false
	bool has_kingside_castling_rights[2];
	bool has_queenside_castling_rights[2];
	Color turn;
} Game;

typedef struct {
	Color color;
	Piece piece;
	Square square;
} PieceLocInfo;

Game* create_game();
Game* create_game_with_options(GameOptions);
void destroy_game(Game**);

Move get_last_move(const Game*);

Bitboard get_bitboard_for_color(const Game*, Color);
Bitboard get_bitboard_for_piece(const Game*, Piece);
Bitboard get_bitboard(const Game*);
bool get_piece_on_square(Bitboard[2][6], Square, PieceLocInfo*);
Square get_en_pessant_square(const Game*, Color);

/*
 * Places the given piece on the provided square, overwriting any
 * piece in the target location
 */
void put_piece(Game*, Color, Piece, Square);

void make_move(Game*, Move);
void make_move_for_piece(Game*, Move, Color, Piece);
void undo_move(Game*, Move);
void undo_move_for_piece(Game*, Move, Color, Piece);


#endif // !GAME_H
