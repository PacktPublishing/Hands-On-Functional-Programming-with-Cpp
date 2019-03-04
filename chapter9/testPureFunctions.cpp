#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto greaterThan = [](auto first, auto second){
    return first > second;
};

TEST_CASE("Greater Than"){
    int first = 3;
    int second = 2;

    bool result = greaterThan(first, second);

    CHECK(result);
}

TEST_CASE("Not Greater Than when first is less than second"){
    int first = 2;
    int second = 3;

    bool result = greaterThan(first, second);

    CHECK_FALSE(result);
}

TEST_CASE("Not Greater Than when first equals second"){
    int first = 2;

    bool result = greaterThan(first, first);

    CHECK_FALSE(result);
}

TEST_CASE("Greater than") {
    struct Data {
        int first;
        int second;
        bool expected;
    } data;

    SUBCASE("2 is greater than 1") { data.first = 2; data.second = 1; data.expected = true; }
    SUBCASE("2 is not greater than 2") { data.first = 2; data.second = 2; data.expected = false; }
    SUBCASE("2 is not greater than 3") { data.first = 2; data.second = 3; data.expected = false; }
    
    CAPTURE(data);
    
    CHECK_EQ(greaterThan(data.first, data.second), data.expected);
}
