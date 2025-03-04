#include <stdio.h>
#include <assert.h>
#include "../src/math/math_utils.h"
#include "../src/math/advanced_math_utils.h"

void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    printf("Test add() passed!\n");
}

void test_subtract() {
    assert(subtract(2, 3) == -1);
    assert(subtract(-1, 1) == -2);
    printf("Test subtract() passed!\n");
}

void test_is_even() {
    assert(is_even(2) == 1);
    assert(is_even(3) == 0);
    printf("Test is_even() passed!\n");
}

void test_is_prime() {
    assert(is_prime(2) == 1);
    assert(is_prime(2137) == 1);
    printf("Test is_prime() passed!\n");
}

int main() {
    test_add();
    test_subtract();
    test_is_even();
    test_is_prime();
    printf("All tests passed!\n");
    return 0;
}
