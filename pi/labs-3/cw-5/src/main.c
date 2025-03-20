#include <stdio.h>
#include "state.h"

int main(void)
{
  printf("Hello\n");

  while (shouldRun)
  {
    step();
  }

  return 0;
}
