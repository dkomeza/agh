#include "advanced_math_utils.h"

bool is_even(int a) {
    return a % 2 == 0;
}

bool is_prime(int a) {
    if (a < 2) {
        return 0;
    }

    int i = 2;

    while (i*i <= a) {
        if (a % i == 0) {
            return 0;
        }

        i++;
    }

    return 1;
}

bool is_palindrome(int a) {
    int reversed = 0;
    int original = a;

    while (a != 0) {
        reversed = reversed * 10 + a % 10;
        a = a / 10;
    }

    return original == reversed;
}
