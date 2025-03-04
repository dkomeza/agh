#include <stdio.h>
#include "math/math_utils.h"
#include "math/advanced_math_utils.h"

int main(void) {
  printf("2 + 3 = %d\n", add(2,3));
  printf("2 - 3 = %d\n", subtract(2, 3));

  if (is_prime(2137))
      printf("2137 jest pierwsze\n");
  else
      printf("2137 nie jest pierwsze\n");

  return 0;
}
