#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

auto power = [](int first, int second){
    return pow(first, second);
};

TEST_CASE("Power"){
    int maxInt = numeric_limits<int>::max();
    CHECK_EQ(1, power(0, 0));
    CHECK_EQ(0, power(0, 1));
    CHECK_EQ(0, power(0, maxInt));
    CHECK_EQ(1, power(1, 1));
    CHECK_EQ(1, power(1, 2));
    CHECK_EQ(1, power(1, maxInt));
    CHECK_EQ(1, power(2, 0));
    CHECK_EQ(2, power(2, 1));
    CHECK_EQ(4, power(2, 2));
    CHECK_EQ(maxInt, power(2, 31) - 1);
    CHECK_EQ(1, power(3, 0));
    CHECK_EQ(3, power(3, 1));
    CHECK_EQ(9, power(3, 2));
    CHECK_EQ(1, power(maxInt, 0));
    CHECK_EQ(maxInt, power(maxInt, 1));
}
