#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "game.h"

enum Direction
{
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

typedef enum Direction direction_t;

direction_t direction = RIGHT;
int position[2] = {26, 26}; // x, y coordinates
int should_play = 1;
int move_counter = 0;

void init_board(int board[BOARD_SIZE][BOARD_SIZE])
{
  // Init the random number generator
  srand((unsigned int)time(NULL));

  // Initialize the board with some values
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      board[i][j] = rand() % 8 + 1; // Random values between 1 and 8
    }
  }
}

void print_board(int board[BOARD_SIZE][BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      switch (board[i][j])
      {
      case 1:
        printf("\033[48;2;97;152;142m  ");
        break;
      case 2:
        printf("\033[48;2;255;0;0m  ");
        break;
      case 3:
        printf("\033[48;2;255;255;0m  ");
        break;
      case 4:
        printf("\033[48;2;0;255;0m  ");
        break;
      case 5:
        printf("\033[48;2;0;0;255m  ");
        break;
      case 6:
        printf("\033[48;2;255;0;255m  ");
        break;
      case 7:
        printf("\033[48;2;0;255;255m  ");
        break;
      case 8:
        printf("\033[48;2;255;127;0m  ");
        break;

      default:
        break;
      }
      printf("\033[0m");
    }
    printf("\n");
  }
}

void move(int value)
{
  direction_t old_direction = direction;

  switch (value)
  {
  case 2:
    if (direction == LEFT)
      direction = UP;
    else
      direction++;
    return;
  case 3:
    if (direction == UP)
      direction = LEFT;
    else
      direction--;
    return;
  case 4:
    if (direction == LEFT)
      direction = UP;
    else
      direction++;
    break;
  case 5:
    if (direction == UP)
      direction = LEFT;
    else
      direction--;
    break;
  case 6:
    switch (direction)
    {
    case UP:
      direction = DOWN;
      break;
    case DOWN:
      direction = UP;
      break;
    case LEFT:
      direction = RIGHT;
      break;
    case RIGHT:
      direction = LEFT;
      break;
    }
    break;
  case 7:
    switch (direction)
    {
    case UP:
      direction = DOWN;
      return;
    case DOWN:
      direction = UP;
      return;
    case LEFT:
      direction = RIGHT;
      return;
    case RIGHT:
      direction = LEFT;
      return;
    }
    break;
  }

  switch (direction)
  {
  case UP:
    if (position[0] == 0)
      position[0] = BOARD_SIZE - 1;
    else
      position[0]--;
    break;
  case DOWN:
    if (position[0] == BOARD_SIZE - 1)
      position[0] = 0;
    else
      position[0]++;
    break;
  case LEFT:
    if (position[1] == 0)
      position[1] = BOARD_SIZE - 1;
    else
      position[1]--;
    break;
  case RIGHT:
    if (position[1] == BOARD_SIZE - 1)
      position[1] = 0;
    else
      position[1]++;
    break;
  }

  direction = old_direction;
}

void play_game(int board[BOARD_SIZE][BOARD_SIZE], dumb_vector_t *path)
{
  // Game logic goes here
  int current_value = board[position[0]][position[1]];

  switch (current_value)
  {
  case 1:
    board[position[0]][position[1]] = 7;
    move(current_value);
    break;
  case 2:
    board[position[0]][position[1]] = 4;
    move(current_value);
    break;
  case 3:
    board[position[0]][position[1]] = 2;
    move(current_value);
    break;
  case 4:
    board[position[0]][position[1]] = 6;
    move(current_value);
    break;
  case 5:
    board[position[0]][position[1]] = 3;
    move(current_value);
    break;
  case 6:
    board[position[0]][position[1]] = 5;
    move(current_value);
    break;
  case 7:
    board[position[0]][position[1]] = 8;
    move(current_value);
    break;
  case 8:
    board[position[0]][position[1]] = 1;
    move(current_value);
    break;
  default:
    break;
  }

  // Add the current position to the path
  push_back(path, position[0] * BOARD_SIZE + position[1]);

  move_counter++;
}