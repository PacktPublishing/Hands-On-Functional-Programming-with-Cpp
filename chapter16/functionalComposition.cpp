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

auto powerOf2 = [](const int exponent){
    return pow(2, exponent);
};

auto increment = [](const int value){
    return value + 1;
};

TEST_CASE("Composition"){
    auto incrementPowerOf2 = [](const int exponent){
        return increment(powerOf2(exponent));
    };

    CHECK_EQ(9, incrementPowerOf2(3));
}

namespace Functions{
    int incrementPowerOf2(const int exponent){
        return increment(powerOf2(exponent));
    };
}

TEST_CASE("Composition"){
    CHECK_EQ(9, Functions::incrementPowerOf2(3));
}

template <class F, class G>
auto compose(F f, G g){
  return [=](auto value){return f(g(value));};
}

TEST_CASE("Composition"){
    auto incrementPowerOf2 = compose(increment, powerOf2); 

    CHECK_EQ(9, incrementPowerOf2(3));
}


