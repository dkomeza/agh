#include "warcaby.h"

#include <stdio.h>

struct Move
{
  int field;
  int to_delete[BOARD_SIZE * BOARD_SIZE];
  int to_delete_count;
};

struct Move move_list[BOARD_SIZE * BOARD_SIZE];
int moves_count = 0;

void generate_captures(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player, int *moves);

void init_board(struct Field board[BOARD_SIZE][BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      board[i][j].pawn = EMPTY;
      board[i][j].player = NOONE;
    }
  }

  // for (int i = 0; i < PAWN_ROWS; i++) {
  //   for (int j = 0; j < BOARD_SIZE - 1; j += 2) {
  //     int x1 = j + (i % 2);
  //     int x2 = j + ((i + 1) % 2);

  //     board[i][x1].pawn = PAWN;
  //     board[i][x1].player = PLAYER_1;

  //     board[BOARD_SIZE - 1 - i][x2].pawn = PAWN;
  //     board[BOARD_SIZE - 1 - i][x2].player = PLAYER_2;
  //   }
  // }

  // Create a sample board

  board[0][2].pawn = PAWN;
  board[0][2].player = PLAYER_1;

  board[1][1].pawn = PAWN;
  board[1][1].player = PLAYER_2;
  board[3][1].pawn = PAWN;
  board[3][1].player = PLAYER_2;
};

int generate_possible_moves(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player)
{
  int moves = 0;

  int row = selected_pawn / BOARD_SIZE;
  int col = selected_pawn % BOARD_SIZE;

  int direction = (player == PLAYER_1) ? 1 : -1;

  // Check for possible moves
  for (int i = -1; i <= 1; i += 2)
  {
    int new_col = col + i;
    int new_row = row + direction;

    if (new_col >= 0 && new_col < BOARD_SIZE && new_row >= 0 && new_row < BOARD_SIZE)
    {
      if (board[new_row][new_col].pawn == EMPTY)
      {
        board[new_row][new_col].pawn = MARKED;
        move_list[moves].field = new_row * BOARD_SIZE + new_col;
        move_list[moves].to_delete_count = 0;
        move_list[moves].to_delete[0] = -1; // No captures
        moves++;
      }
    }
  }

  // Check for possible captures
  generate_captures(board, selected_pawn, player, &moves);

  moves_count = moves;
  return moves;
}

void generate_captures(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player, int *moves)
{
  int row = selected_pawn / BOARD_SIZE;
  int col = selected_pawn % BOARD_SIZE;

  int direction = (player == PLAYER_1) ? 1 : -1;

  for (int i = -1; i <= 1; i += 2)
  {
    int new_col = col + i;
    int new_row = row + direction;

    if (new_col >= 0 && new_col < BOARD_SIZE && new_row >= 0 && new_row < BOARD_SIZE)
    {
      if (board[new_row][new_col].pawn == PAWN && board[new_row][new_col].player != player)
      {
        if (new_col + i >= 0 && new_col + i < BOARD_SIZE && new_row + direction >= 0 && new_row + direction < BOARD_SIZE)
        {
          if (board[new_row + direction][new_col + i].pawn == EMPTY)
          {
            board[new_row + direction][new_col + i].pawn = MARKED;
            move_list[*moves].field = (new_row + direction) * BOARD_SIZE + new_col + i;
            move_list[*moves].to_delete[0] = new_row * BOARD_SIZE + new_col;
            move_list[*moves].to_delete_count = 1;
            moves_count++;
            (*moves)++;
            generate_captures(board, (new_row + direction) * BOARD_SIZE + new_col + i, player, moves);
          }
        }
      }
    }
  }
}

void clear_marked_moves(struct Field board[BOARD_SIZE][BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j].pawn == MARKED)
      {
        board[i][j].pawn = EMPTY;
        board[i][j].player = NOONE;
      }
    }
  }
}

void make_move(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, int selected_move, enum Player player)
{
  int row = selected_pawn / BOARD_SIZE;
  int col = selected_pawn % BOARD_SIZE;

  int new_row = selected_move / BOARD_SIZE;
  int new_col = selected_move % BOARD_SIZE;

  int directionY = new_row < row ? -1 : 1;
  int directionX = new_col < col ? -1 : 1;

  // Move the pawn
  board[new_row][new_col].pawn = board[row][col].pawn;
  board[new_row][new_col].player = player;

  // Clear the old position
  board[row][col].pawn = EMPTY;
  board[row][col].player = NOONE;
}

void player_change(enum Player *current_player)
{
  if (*current_player == PLAYER_1)
  {
    *current_player = PLAYER_2;
  }
  else
  {
    *current_player = PLAYER_1;
  }
}

int check_win(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player)
{
  int player_pawns = 0;
  int opponent_pawns = 0;

  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j].player == player)
      {
        player_pawns++;
      }
      else if (board[i][j].player != NOONE)
      {
        opponent_pawns++;
      }
    }
  }

  return player_pawns == 0 || opponent_pawns == 0;
}
