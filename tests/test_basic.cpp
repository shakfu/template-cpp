#include "doctest.h"

int factorial(int number) { 
    return number <= 1 ? number : factorial(number - 1) * number;
}

int add(int x, int y) {
    return x+y;
}


TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}


TEST_CASE("testing the add function") {
    CHECK(add(1,2) == 3);
    CHECK(add(2,1) == 3);
    CHECK(add(3,0) == 3);
    CHECK(add(0,3) == 3);
}
