#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <immer/vector.hpp>

using namespace std;
using namespace std::placeholders;

TEST_CASE("Check immutable vector"){
    const auto empty = immer::vector<int>{};
    const auto withOneElement = empty.push_back(42);

    CHECK_EQ(0, empty.size());
    CHECK_EQ(1, withOneElement.size());
    CHECK_EQ(42, withOneElement[0]);
}
 
