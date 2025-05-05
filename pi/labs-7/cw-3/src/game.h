#pragma once

#include "utils/utils.h"

#define BOARD_SIZE 101

void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
void print_board(int board[BOARD_SIZE][BOARD_SIZE]);
void play_game(int board[BOARD_SIZE][BOARD_SIZE], dumb_vector_t *path);

extern int should_play;
extern int move_counter;