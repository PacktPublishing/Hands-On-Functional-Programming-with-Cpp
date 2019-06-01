#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <range/v3/all.hpp>

using namespace std;
using namespace std::placeholders;

TEST_CASE("Increment"){
    auto increment =  [](auto value) { return value + 1;};

    CHECK_EQ(2, increment(1));
}

TEST_CASE("Increment"){
    auto increment =  [](int value) { return value + 1;};

    CHECK_EQ(2, increment(1));
}

TEST_CASE("Increment"){
    auto increment =  [](int value) -> int { return value + 1;};

    CHECK_EQ(2, increment(1));
}

TEST_CASE("One"){
    auto one =  []{ return 1;};

    CHECK_EQ(1, one());
}

TEST_CASE("Capture value"){
    int value = 5;
    auto addToValue =  [value](int toAdd) { return value + toAdd;};

    CHECK_EQ(6, addToValue(1));
}

TEST_CASE("Capture value by reference"){
    int value = 5;
    auto addToValue =  [&value](int toAdd) { return value + toAdd;};

    CHECK_EQ(6, addToValue(1));
}

TEST_CASE("Capture all values by value"){
    int first = 5;
    int second = 10;
    auto addToValues = [=](int toAdd) { return first + second + toAdd;};

    CHECK_EQ(16, addToValues(1));
}

TEST_CASE("Capture all values by reference"){
    int first = 5;
    int second = 10;
    auto addToValues = [&](int toAdd) { return first + second + toAdd;};

    CHECK_EQ(16, addToValues(1));
}

TEST_CASE("Increment mutable - NOT RECOMMENDED"){
    auto increment =  [](int& value) mutable { return ++value;};

    int value = 1;
    CHECK_EQ(2, increment(value));
    CHECK_EQ(2, value);
}

/*
// Not supported in g++ 8
TEST_CASE("Increment"){
    auto one = []() consteval { return 1;};

    CHECK_EQ(1, one());
}
*/


TEST_CASE("Increment"){
    auto increment =  [](int value) noexcept { return value + 1;};

    CHECK_EQ(2, increment(1));
}

TEST_CASE("Increment"){
    auto increment =  [](int value) throw() { return value + 1;};

    CHECK_EQ(2, increment(1));
}

/*
// Not supported in g++ 8
TEST_CASE("Increment"){
    auto increment =  [] <typename T>(T value) -> requires NumericType<T> { return value + 1;};

    CHECK_EQ(2, increment(1));
}
*/
