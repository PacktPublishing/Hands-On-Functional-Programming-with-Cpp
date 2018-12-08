#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto addWrapped = [](const auto first, const auto second, const auto wrapAt) { return (first + second) % wrapAt; };

auto add = bind(addWrapped, _1, _2, 20);

TEST_CASE("Adds values"){
    CHECK_EQ(7, add(10, 17));
}

template<typename T, T one>
auto increment = bind<T>(add, _1, one);

TEST_CASE("Increments"){
    CHECK_EQ(1, increment<int, 1>(20));
}
