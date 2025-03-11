#include <stdio.h>

int main(void)
{
  int height = 9;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < height - i - 1; j++)
    {
      printf(" ");
    }
    for (int j = 0; j < 2 * i + 1; j++)
    {
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
