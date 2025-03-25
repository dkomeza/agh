#include <stdio.h>
#include "state.h"

int main(void)
{
  for (int i = 0; i < 100; ++i)
  {
    memory[i] = Z0;
  }

  // Initial position and state
  position = 0;
  state = S0;

  while (shouldRun)
  {
    step();
  }

  return 0;
}
