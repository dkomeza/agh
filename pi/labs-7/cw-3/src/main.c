#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#include "game.h"
#include "utils/utils.h"

#define MAX_MOVES 100000

void print_path(dumb_vector_t *path)
{
  int recap[BOARD_SIZE][BOARD_SIZE] = {0};
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
}

typedef struct
{
  int new_value;
  char move;
} move_t;

void get_move_table(move_t *move_table)
{
  int random_moves = rand() % 15 + 1;
  char file_name[] = "files/ANTxx.txt";
  if (random_moves >= 1 && random_moves < 10)
  {
    file_name[9] = '0';
    file_name[10] = '0' + random_moves;
  }
  else
  {
    file_name[9] = '0' + (random_moves / 10);
    file_name[10] = '0' + (random_moves % 10);
  }

  FILE *move_file = fopen(file_name, "r");
  if (move_file == NULL)
  {
    fprintf(stderr, "Failed to open file: %s\n", file_name);
    return;
  }

  int move_counter = 0;
  int line_counter = 0;

  while (!feof(move_file))
  {
    char move = fgetc(move_file);
    if (move == EOF)
      break;
    if (move == '\n')
    {
      line_counter++;
      move_counter = 0;
      continue;
    }
    if (isalnum(move) == 0)
      continue;

    if (line_counter == 0)
    {
      move_table[move_counter].new_value = move - '0';
      move_counter++;
    }
    else
    {
      move_table[move_counter].move = move;
      move_counter++;
    }
  }
  fclose(move_file);
}

struct board_size
{
  int x;
  int y;
};
typedef struct board_size board_size_t;

int **get_board(board_size_t *board_size, int selection)
{
  char file_name[30];

  if (selection < 10)
  {
    snprintf(file_name, sizeof(file_name), "files/World0%d.txt", selection);
  }
  else
  {
    snprintf(file_name, sizeof(file_name), "files/World%d.txt", selection);
  }

  FILE *file = fopen(file_name, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Failed to open file: %s\n", file_name);
    return NULL;
  }

  // Get the board size, (length of the first line)

  while (1)
  {
    char c = fgetc(file);
    if (c == EOF)
      break;
    if (c == '\n')
    {
      board_size->x = 0;
      board_size->y += 1;
    }
    if (isdigit(c) == 0)
      continue;

    board_size->x += 1;
  }

  int **board = malloc(sizeof(int *) * board_size->y);
  for (int i = 0; i < board_size->y; i++)
  {
    board[i] = malloc(sizeof(int) * board_size->x);
  }
  fseek(file, 0, SEEK_SET);

  // Read the board from the file
  for (int i = 0; i < board_size->y; i++)
  {
    for (int j = 0; j < board_size->x; j++)
    {
      char c = fgetc(file);
      if (c == EOF)
        break;
      if (c == '\n')
        break;
      if (isdigit(c) == 0)
        continue;

      board[i][j] = c - '0';
    }
  }
  fclose(file);
  return board;
}

int main(void)
{
  srand(time(NULL));

  move_t moves[8] = {};
  get_move_table(moves);

  // Get the file name number from the user
  int file_number = 1;
  // do
  // {
  //   printf("Enter the file number (1-15): ");
  //   scanf("%d", &file_number);
  // } while (file_number < 1 || file_number > 15);

  board_size_t board_size = {0, 0};
  int **board = get_board(&board_size, file_number);

  // Print the board
  for (int i = 0; i < board_size.y; i++)
  {
    for (int j = 0; j < board_size.x; j++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  // int board[BOARD_SIZE][BOARD_SIZE] = {0};

  // dumb_vector_t *path = create_dumb_vector(0);

  // if (path == NULL)
  // {
  //   fprintf(stderr, "Failed to create path vector\n");
  //   return 1;
  // }

  // init_board(board);

  // print_board(board);
  // while (should_play)
  // {
  //   play_game(board, path);

  //   if (move_counter > MAX_MOVES)
  //   {
  //     should_play = 0;
  //   }
  // }

  // print_path(path);

  // return 0;
}