#include "printer.h"

#include <stdio.h>

void print_board(struct Field board[BOARD_SIZE][BOARD_SIZE], enum Player player) {
  printf("\n");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("  %d ", BOARD_SIZE - i);  // Numery wierszy
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j].player == HIGHLIGHT)
        printf("\033[42m");  // Highlight the selected pawn
      else if ((i + j) % 2 == 0)
        printf("\033[47m");
      else
        printf("\033[43m");

      if (board[i][j].player == player || board[i][j].player == HIGHLIGHT)
        printf("\033[36m");
      else
        printf("\033[31m");

      switch (board[i][j].pawn) {
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
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf(" %c ", 'A' + i);  // Numery kolumn
  }
  printf("\n");
}

void print_possible_moves(struct Field board[BOARD_SIZE][BOARD_SIZE], int selected_pawn, enum Player player) {
  int moves = generate_possible_moves(board, selected_pawn, player);

  if (moves == 0) {
    print_message(ERROR, "No possible moves");
    return;
  }

  print_message(SUCCESS, "Possible moves:");
  print_board(board, player);
}

void print_message(enum PrintType type, const char* message) {
  switch (type) {
    case ERROR:
      printf("\033[31m");
      break;
    case NORMAL:
      printf("\033[32m");
      break;
    case SUCCESS:
      printf("\033[32m");
      break;
  }

  printf("%s\n", message);
  printf("\033[0m");
}