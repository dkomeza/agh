#include "warcaby.h"
#include <stdio.h>

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

  for (int i = 0; i < PAWN_ROWS; i++)
  {
    for (int j = 0; j < BOARD_SIZE - 1; j += 2)
    {
      int x1 = j + (i % 2);
      int x2 = j + ((i + 1) % 2);

      board[i][x1].pawn = PAWN;
      board[i][x1].player = PLAYER_1;

      board[BOARD_SIZE - 1 - i][x2].pawn = PAWN;
      board[BOARD_SIZE - 1 - i][x2].player = PLAYER_2;
    }
  }
};

void print_board(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player)
{
  printf("\n");
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    printf("  %d ", BOARD_SIZE - i); // Numery wierszy
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j].player == HIGHLIGHT)
        printf("\033[42m"); // Highlight the selected pawn
      else if ((i + j) % 2 == 0)
        printf("\033[47m");
      else
        printf("\033[43m");

      if (board[i][j].player == player || board[i][j].player == HIGHLIGHT)
        printf("\033[36m");
      else
        printf("\033[31m");

      switch (board[i][j].pawn)
      {
      case EMPTY:
        printf("   ");
        break;
      case PAWN:
        printf(" \u265F ");
        break;
      case QUEEN:
        printf(" \u265B ");
        break;
      case MARKED:
        printf(" \u2715 ");
        break;
      default:
        break;
      }

      printf("\033[0m");
    }
    printf("\n");
  }

  printf("    ");
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    printf(" %c ", 'A' + i); // Numery kolumn
  }
  printf("\n");
}

void show_possible_moves(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player)
{
  int row = selected_pawn / BOARD_SIZE;
  int col = selected_pawn % BOARD_SIZE;

  board[row][col].player = HIGHLIGHT; // Highlight the selected pawn

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
      }
    }
  }

  // Check for possible captures
  // for (int i = -1; i <= 1; i += 2)
  // {
  //   int new_col = col + i;
  //   int new_row = row + direction;

  //   if (new_col >= 0 && new_col < BOARD_SIZE && new_row >= 0 && new_row < BOARD_SIZE)
  //   {
  //     if (board[new_col][new_row].pawn != EMPTY && board[new_col][new_row].player != player)
  //     {
  //       int capture_col = new_col + i;
  //       int capture_row = new_row + direction;

  //       if (capture_col >= 0 && capture_col < BOARD_SIZE && capture_row >= 0 && capture_row < BOARD_SIZE)
  //       {
  //         if (board[capture_col][capture_row].pawn == EMPTY)
  //         {
  //           board[capture_col][capture_row].pawn = MARKED;
  //         }
  //       }
  //     }
  //   }
  // }

  // Print the board with marked moves
  print_board(board, player);
  printf("Possible moves marked with checkmarks.\n");
}

void make_move(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, int selected_move, enum Player player)
{
  int row = selected_pawn / BOARD_SIZE;
  int col = selected_pawn % BOARD_SIZE;

  int new_row = selected_move / BOARD_SIZE;
  int new_col = selected_move % BOARD_SIZE;

  // Move the pawn
  board[new_row][new_col].pawn = board[row][col].pawn;
  board[new_row][new_col].player = player;

  // Clear the old position
  board[row][col].pawn = EMPTY;
  board[row][col].player = NOONE;

  // Clear the marked moves
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
