#pragma once

#define BOARD_SIZE 8
#define PAWN_ROWS 2

enum Pionek
{
  EMPTY,
  PAWN,
  QUEEN,
  MARKED // Used for marking possible moves
};

enum Player
{
  NOONE,
  PLAYER_1,
  PLAYER_2,
  HIGHLIGHT // Used for highlighting the current pawn
};

struct Field
{
  enum Pionek pawn;
  enum Player player;
};

void init_board(struct Field board[BOARD_SIZE][BOARD_SIZE]);
void make_move(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, int selected_move, enum Player player);
void player_change(enum Player *current_player);
int check_win(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player);
int generate_possible_moves(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player);
void clear_marked_moves(struct Field board[BOARD_SIZE][BOARD_SIZE]);