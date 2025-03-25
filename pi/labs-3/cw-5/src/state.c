#include "state.h"

enum Symbol memory[100] = {};
int position = 0;
enum State state = S0;
int shouldRun = 1;

void step()
{
  enum Symbol current_symbol = memory[position];
  enum State current_state = state;
  enum Symbol new_symbol;
  enum State new_state;
  int move; // -1: left, 0: none, 1: right
  int halt = 0;

  switch (current_state)
  {
  case S0:
    switch (current_symbol)
    {
    case Z0:
      new_symbol = Z1;
      new_state = S1;
      move = 1;
      break;
    case Z1:
      new_symbol = Z0;
      new_state = S0; // State doesn't matter after halt
      move = -1;
      shouldRun = 0;
      break;
    }
    break;
  case S1:
    switch (current_symbol)
    {
    case Z0:
      new_symbol = Z1;
      new_state = S0;
      move = -1;
      break;
    case Z1:
      new_symbol = Z0;
      new_state = S1;
      move = 1;
      break;
    }
    break;
  }

  // Update memory and print
  memory[position] = new_symbol;
  printf("Position %d: %c\n", position, (new_symbol == Z0) ? '0' : '1');

  // Update state
  state = new_state;

  // Move position
  switch (move)
  {
  case -1:
    position = (position > 0) ? position - 1 : 99;
    break;
  case 1:
    position = (position < 99) ? position + 1 : 0;
    break;
  case 0:
    break;
  }
}