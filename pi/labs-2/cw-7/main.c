#include <stdio.h>

int main(void)
{
  int height = 9;

  int i = 0;
  do
  {
    int j = 0;
    do
    {
      printf(" ");
      j++;
    } while (j < height - i - 1);

    j = 0;

    do
    {
      printf("*");
      j++;
    } while (j < 2 * i + 1);

    printf("\n");

    i++;
  } while (i < height);

  i = 0;
  do
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

    i++;
  } while (i < 2);
}
