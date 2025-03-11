#include <stdio.h>

void print_tree(int height);

int main(void)
{
  int height = 5;

  while (1)
  {
    printf("Podaj wysokość choinki: ");
    fflush(stdin);
    scanf("%d", &height);

    if (height < 5 || height > 50)
    {
      printf("Proszę podać liczbę z przedziału 5-50\n");
      continue;
    }

    print_tree(height);
  }

  return 0;
}

void print_tree(int height)
{
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
}