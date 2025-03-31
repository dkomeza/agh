#include <stdio.h>

#include "printer.h"
#include "warcaby.h"

int get_move(char ccol, int *row, int *col)
{
  *row = BOARD_SIZE - *row;

  if (ccol >= 'a')
  {
    *col = ccol - 'a';
  }
  else
  {
    *col = ccol - 'A';
  }

  if (*col > BOARD_SIZE - 1 || *col < 0)
  {
    printf("Wrong column");
    return -1;
  }

  if (*row > BOARD_SIZE - 1 || *row < 0)
  {
    printf("Wrong row");
    return -1;
  }

  return *row * BOARD_SIZE + *col;
}

int askPawn(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player)
{
  int row = 0;
  int col = 0;
  char ccol = 'a';

  print_board(board, player);
  printf("Select the pawn (ex. A5): ");
  scanf("%c%d", &ccol, &row);

  int move = get_move(ccol, &row, &col);

  if (move == -1)
    return askPawn(board, player);

  if (board[row][col].pawn == EMPTY || board[row][col].player != player)
  {
    print_message(ERROR, "Wrong choice");
    return askPawn(board, player);
  }

  int moves = generate_possible_moves(board, move, player);
  clear_marked_moves(board);
  if (moves == 0)
  {
    print_message(ERROR, "No possible moves");
    return askPawn(board, player);
  }

  return row * BOARD_SIZE + col;
}

int askMove(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player)
{
  int row = 0;
  int col = 0;
  char ccol = 'a';

  print_board(board, player);
  printf("Select the move (ex. A5): ");
  scanf("%c%d", &ccol, &row);

  int move = get_move(ccol, &row, &col);

  if (move == -1)
    return askMove(board, player);

  if (board[row][col].pawn != MARKED)
  {
    print_message(ERROR, "Wrong choice");
    return askMove(board, player);
  }

  return row * BOARD_SIZE + col;
}

int main(void)
{
  struct Field board[BOARD_SIZE][BOARD_SIZE] = {{}};
  int shouldPlay = 1;
  enum Player current_player = PLAYER_1;

  init_board(board);
  while (shouldPlay)
  {
    printf("Current player: %s\n", current_player == PLAYER_1 ? "Player 1" : "Player 2");
    int selected_pawn = askPawn(board, current_player);

    print_possible_moves(board, selected_pawn, current_player);
    int selected_move = askMove(board, current_player);
    clear_marked_moves(board);
    make_move(board, selected_pawn, selected_move, current_player);

    if (check_win(board, current_player))
    {
      printf("\n%s wins!\n", current_player == PLAYER_1 ? "Player 1" : "Player 2");
      shouldPlay = 0;
      continue;
    }

    player_change(&current_player);
  }

  return 0;
}