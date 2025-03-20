#include "state.h"

enum Symbol memory[100] = {};
int position = 0;
enum State state = S0;
int shouldRun = 1;

void step()
{
  switch (state)
  {
  case S0:
    switch (memory[position])
    {
    case Z0:
      shouldRun = 0;
      break;
    case Z1:
      
      break;
    }
    break;

  case S1:
    break;
  }
}