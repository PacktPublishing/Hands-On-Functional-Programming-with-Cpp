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
    auto increment =  [](const int value) { return plus<int>()(value, 1); };

    CHECK_EQ(2, increment(1));
}

namespace Increment{
    int increment(const int value){
        return plus<int>()(value, 1);
    };
}

TEST_CASE("Increment"){
    CHECK_EQ(2, Increment::increment(1));
}

TEST_CASE("Increment"){
    auto increment = bind(plus<int>(), _1, 1);

    CHECK_EQ(2, increment(1));
}

auto curriedPower = [](const int base) {
    return [base](const int exponent) {
        return pow(base, exponent);
    };
};


TEST_CASE("Power and curried power"){
    CHECK_EQ(16, pow(2, 4));
    CHECK_EQ(16, curriedPower(2)(4));

    auto powerOf2 = curriedPower(2);
    CHECK_EQ(16, powerOf2(4));
}

template<typename F>
auto curry2(F f){
    return [=](auto first){
        return [=](auto second){
            return f(first, second);
        };
    };
}

TEST_CASE("Power and curried power"){
    auto power = [](const int base, const int exponent){
        return pow(base, exponent);
    };
    auto curriedPower = curry2(power);
    auto powerOf2 = curriedPower(2);
    CHECK_EQ(16, powerOf2(4));
}


