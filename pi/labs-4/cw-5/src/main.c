#include "warcaby.h"
#include <stdio.h>

int askPawn(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player)
{
  int row = 0;
  int col = 0;
  char ccol = 'a';

  print_board(board, player);
  printf("Select the pawn (ex. A5): ");
  scanf("%c%d", &ccol, &row);

  row = BOARD_SIZE - row;

  if (ccol >= 'a')
  {
    col = ccol - 'a';
  }
  else
  {
    col = ccol - 'A';
  }

  if (col > BOARD_SIZE - 1)
  {
    printf("Wrong column");
    return askPawn(board, player);
  }

  if (row > BOARD_SIZE - 1 || row < 0)
  {
    printf("Wrong row");
    return askPawn(board, player);
  }

  if (board[row][col].pawn == EMPTY || board[row][col].player != player)
  {
    printf("Wrong choice");
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

  row = BOARD_SIZE - row;

  if (ccol >= 'a')
  {
    col = ccol - 'a';
  }
  else
  {
    col = ccol - 'A';
  }

  if (col > BOARD_SIZE - 1)
  {
    printf("Wrong column");
    return askMove(board, player);
  }

  if (row > BOARD_SIZE - 1 || row < 0)
  {
    printf("Wrong row");
    return askMove(board, player);
  }

  if (board[row][col].pawn != MARKED)
  {
    printf("Wrong choice");
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
  // int selected_pawn = BOARD_SIZE + 3;
  // show_possible_moves(board, selected_pawn, current_player);

  while (shouldPlay)
  {
    printf("Current player: %s\n", current_player == PLAYER_1 ? "Player 1" : "Player 2");
    int selected_pawn = askPawn(board, current_player);

    show_possible_moves(board, selected_pawn, current_player);
    int selected_move = askMove(board, current_player);
    make_move(board, selected_pawn, selected_move, current_player);

    // ToDo: Check for game over conditions

    player_change(&current_player);
  }

  return 0;
}