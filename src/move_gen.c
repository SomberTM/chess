#include <assert.h>

#include "move_gen.h"
#include "misc.h"

void generate_pawn_moves(MoveList* move_list, Bitboard pawns, Bitboard us_pieces, Bitboard enemy_pieces, Square en_pessant, Color us) {
	Bitboard single_push;
	Bitboard double_push;
	Bitboard left_captures;
	Bitboard right_captures;
	Bitboard promotion_rank;
	char from_offset;
	char lcapture_offset;
	char rcapture_offset;

	Bitboard empty = ~(us_pieces | enemy_pieces);

	Bitboard en_pessant_bitboard = 0;
	if (en_pessant != NIL) {
		en_pessant_bitboard = 1ULL << en_pessant;
	}

	enemy_pieces |= en_pessant_bitboard;

	if (us == WHITE) {
		single_push = (pawns << 8) & empty;
		double_push = ((pawns & RANK_2) << 8) & empty;
		double_push = (double_push << 8) & empty;

		left_captures = (pawns << 7) & enemy_pieces & ~FILE_H;
		right_captures = (pawns << 9) & enemy_pieces & ~FILE_A;

		promotion_rank = RANK_8;
		from_offset = -8;
		lcapture_offset = -7;
		rcapture_offset = -9;
	} else if (us == BLACK) {
		single_push = (pawns >> 8) & empty;
		double_push = ((pawns & RANK_7) >> 8) & empty;
		double_push = (double_push >> 8) & empty;

		left_captures = (pawns >> 9) & enemy_pieces & ~FILE_H;
		right_captures = (pawns >> 7) & enemy_pieces & ~FILE_A;

		promotion_rank = RANK_1;
		from_offset = 8;
		lcapture_offset = 9;
		rcapture_offset = 7;
	}

	while (single_push) {
		Square to = pop_lsb_position(&single_push);
		Square from = to + from_offset;

		if (square_to_bitboard(to) & promotion_rank) {
			add_move(move_list, create_move(from, to, KNIGHT_PROMOTION));
			add_move(move_list, create_move(from, to, BISHOP_PROMOTION));
			add_move(move_list, create_move(from, to, ROOK_PROMOTION));
			add_move(move_list, create_move(from, to, QUEEN_PROMOTION));
		} else { 
			add_move(move_list, create_move(from, to, QUIET_MOVE));
		}
	}

	while (double_push) {
		Square to = pop_lsb_position(&double_push);
		Square from = to + (2 * from_offset);
		add_move(move_list, create_move(from, to, DOUBLE_PAWN_PUSH));
	}

	while (left_captures) {
		Square to = pop_lsb_position(&left_captures);
		Square from = to + lcapture_offset;

		if (en_pessant == to) {
			add_move(move_list, create_move(from, to, EN_PASSANT_CAPTURE));
		} else if ((square_to_bitboard(to) & promotion_rank) > 0) {
			add_move(move_list, create_move(from, to, KNIGHT_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, BISHOP_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, ROOK_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, QUEEN_PROMOTION_WITH_CAPTURE));
		} else {
			add_move(move_list, create_move(from, to, CAPTURE));
		}
	}

	while (right_captures) {
		Square to = pop_lsb_position(&right_captures);
		Square from = to + rcapture_offset;

		if (en_pessant == to) {
			add_move(move_list, create_move(from, to, EN_PASSANT_CAPTURE));
		} else if ((square_to_bitboard(to) & promotion_rank) > 0) {
			add_move(move_list, create_move(from, to, KNIGHT_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, BISHOP_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, ROOK_PROMOTION_WITH_CAPTURE));
			add_move(move_list, create_move(from, to, QUEEN_PROMOTION_WITH_CAPTURE));
		} else {
			add_move(move_list, create_move(from, to, CAPTURE));
		}
	}
}

void generate_knight_moves(MoveList* move_list, Bitboard knights, Bitboard us_pieces, Bitboard enemy_pieces) {
	Bitboard quiet_moves;
	Bitboard captures;
	Bitboard empty = ~(us_pieces | enemy_pieces);

	while (knights) {
		Bitboard moves = create_bitboard();

		Square knight_square = pop_lsb_position(&knights);
		Bitboard knight = square_to_bitboard(knight_square);
		
		// upper half
		moves |= (knight << 6) & ~FILE_G & ~FILE_H; // two left, one up
		moves |= (knight << 15) & ~FILE_H; // one left, two up
		moves |= (knight << 17) & ~FILE_A; // one right, two up
		moves |= (knight << 10) & ~FILE_A & ~FILE_B; // two right, one up

		// lower half 
		moves |= (knight >> 6) & ~FILE_A & ~FILE_B; // two right, one down
		moves |= (knight >> 15) & ~FILE_A; // one right, two down
		moves |= (knight >> 17) & ~FILE_H; // one left, two down
		moves |= (knight >> 10) & ~FILE_G & ~FILE_H; // two left, one down

		quiet_moves = moves & empty;
		captures = moves & enemy_pieces;

		while (quiet_moves) {
			Square to = pop_lsb_position(&quiet_moves);
			add_move(move_list, create_move(knight_square, to, QUIET_MOVE));
		}

		while (captures) {
			Square to = pop_lsb_position(&captures);
			add_move(move_list, create_move(knight_square, to, CAPTURE));
		}
	}
}

void generate_bishop_moves(MoveList* move_list, Bitboard bishops, Bitboard us_pieces, Bitboard enemy_pieces) {
	Bitboard empty = ~(us_pieces | enemy_pieces);

	while (bishops) {
		char bishop_square = (char) pop_lsb_position(&bishops);

		for (char to = bishop_square + NORTH_EAST; to <= 63; to += NORTH_EAST) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(bishop_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(bishop_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = bishop_square + SOUTH_EAST; to >= 7; to += SOUTH_EAST) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(bishop_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(bishop_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = bishop_square + SOUTH_WEST; to >= 0; to += SOUTH_WEST) {
			Square to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(bishop_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(bishop_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = bishop_square + NORTH_WEST; to <= 56; to += NORTH_WEST) {
			Square to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(bishop_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(bishop_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}
	}
}

void generate_rook_moves(MoveList* move_list, Bitboard rooks, Bitboard us_pieces, Bitboard enemy_pieces) {
	Bitboard empty = ~(us_pieces | enemy_pieces);

	while (rooks) {
		Square rook_square = pop_lsb_position(&rooks);

		for (char to = rook_square + NORTH; to <= 63; to += NORTH) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(rook_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(rook_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = rook_square + EAST; to % 8 != 0; to += EAST) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(rook_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(rook_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = rook_square + SOUTH; to >= 0; to += SOUTH) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(rook_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(rook_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}

		for (char to = rook_square + WEST; (to + 1) % 8 != 0; to += WEST) {
			Bitboard to_bb = 1ULL << to;

			if (to_bb & empty) {
				add_move(move_list, create_move(rook_square, to, QUIET_MOVE));
			} else if (to_bb & enemy_pieces) {
				add_move(move_list, create_move(rook_square, to, CAPTURE));
				break;
			} else {
				break;
			}
		}
	}
}

void generate_queen_moves(MoveList* move_list, Bitboard queen, Bitboard us_pieces, Bitboard enemy_pieces) {
	generate_bishop_moves(move_list, queen, us_pieces, enemy_pieces);
	generate_rook_moves(move_list, queen, us_pieces, enemy_pieces);
}

Bitboard get_king_squares_with_mask(Bitboard king, Bitboard mask) {
	Bitboard squares = create_bitboard();

	squares |= (king << 7) & mask & ~RANK_1 & ~FILE_H; // NW
	squares |= (king << 8) & mask & ~RANK_1; // N
	squares |= (king << 9) & mask & ~RANK_1 & ~FILE_A; // NE
	squares |= (king << 1) & mask & ~FILE_A; // E

	squares |= (king >> 7) & mask & ~RANK_8 & ~FILE_A; // SE
	squares |= (king >> 8) & mask & ~RANK_8; // S
	squares |= (king >> 9) & mask & ~RANK_8 & ~FILE_H; // SW
	squares |= (king >> 1) & mask & ~FILE_H; // W
	
	return squares;
}

void generate_king_moves(MoveList* move_list, Bitboard king, Bitboard us_pieces, Bitboard enemy_pieces) {
	Bitboard empty = ~(us_pieces | enemy_pieces);

	Bitboard quiet_moves = get_king_squares_with_mask(king, empty);
	Bitboard captures = get_king_squares_with_mask(king, enemy_pieces);

	Square king_square = pop_lsb_position(&king);

	while (quiet_moves) {
		Square to = pop_lsb_position(&quiet_moves);
		add_move(move_list, create_move(king_square, to, QUIET_MOVE));
	}

	while (captures) {
		Square to = pop_lsb_position(&captures);
		add_move(move_list, create_move(king_square, to, CAPTURE));
	}
}

void generate_moves(const Game* game, MoveList* move_list) {
	// only deal with an empty move list
	assert(move_list->length == 0);

	Color us = game->turn;
	Color enemy = !us;

	Bitboard us_pieces = get_bitboard_for_color(game, us);
	Bitboard other_pieces = get_bitboard_for_color(game, enemy);
	Square en_pessant_square = get_en_pessant_square(game, us);

	generate_pawn_moves(move_list, game->pieces[us][PAWN], us_pieces, other_pieces, en_pessant_square, us);
	generate_knight_moves(move_list, game->pieces[us][KNIGHT], us_pieces, other_pieces);
	generate_bishop_moves(move_list, game->pieces[us][BISHOP], us_pieces, other_pieces);
	generate_rook_moves(move_list, game->pieces[us][ROOK], us_pieces, other_pieces);
	generate_queen_moves(move_list, game->pieces[us][QUEEN], us_pieces, other_pieces);
	generate_king_moves(move_list, game->pieces[us][KING], us_pieces, other_pieces);
}
