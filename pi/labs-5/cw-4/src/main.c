#include <stdio.h>
#include <unistd.h>

#include "game.h"
#include "utils.h"

#define MAX_MOVES 100000

int main(void)
{
  int board[BOARD_SIZE][BOARD_SIZE] = {0};
  int recap[BOARD_SIZE][BOARD_SIZE] = {0};

  dumb_vector_t *path = create_dumb_vector(0);

  if (path == NULL)
  {
    fprintf(stderr, "Failed to create path vector\n");
    return 1;
  }

  init_board(board);

  print_board(board);
  while (should_play)
  {
    play_game(board, path);

    if (move_counter > MAX_MOVES)
    {
      printf("Game over! You made too many moves.\n");
      break;
    }
  }

  printf("\n\n\n\n\n");

  print_board(board);

  printf("\n\n\n\n\n");

  for (int i = 0; i < size(path); i++)
  {
    int pos = get(path, i);
    int x = pos % BOARD_SIZE;
    int y = pos / BOARD_SIZE;
    recap[x][y] = 1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
      for (int j = 0; j < BOARD_SIZE; j++)
      {
        if (i == x && j == y)
        {
          printf("\033[48;2;255;0;0m  ");
        }
        else if (recap[i][j] == 1)
        {
          printf("\033[48;2;255;255;255m  ");
        }
        else
        {
          printf("\033[48;2;0;0;0m  ");
        }
        printf("\033[0m");
      }
      printf("\n");
    }

    if (i < size(path) - 1)
    {
      printf("\033[%dA", BOARD_SIZE);
    }

    // usleep(1000);
  }

  return 0;
}