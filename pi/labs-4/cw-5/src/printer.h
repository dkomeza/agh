#pragma once

#include "warcaby.h"

enum PrintType {
  ERROR,
  NORMAL,
  SUCCESS,
};

void print_board(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player);
void print_possible_moves(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player);

void print_message(enum PrintType type, const char* message);