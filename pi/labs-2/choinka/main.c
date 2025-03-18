#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int height = 9;
  sranddev();

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < height - i - 1; j++)
    {
      printf(" ");
    }
    for (int j = 0; j < 2 * i + 1; j++)
    {
      if (i == 0) {
        printf("★");
        continue;
      }

      if (rand() % 10 < 2)
        printf("¤");
      else
        printf("*");
    }
    printf("\n");
  }

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < height - 1 - i; j++)
    {
      printf(" ");
    }

    for (int j = 0; j < 2 * i; j++)
    {
      printf("*");
    }
    printf("*\n");
  }
}
