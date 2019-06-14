#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

auto increment = [](const int value) { return value + 1; };

TEST_CASE("Increments value"){
    CHECK_EQ(2, increment(1));
}

TEST_CASE("Increments twice"){
    CHECK_EQ(3, increment(increment(1)));
}

auto incrementTwiceLambda = [](int value){return increment(increment(value));};

TEST_CASE("Increments result of addition with lambda"){
    CHECK_EQ(3, incrementTwiceLambda(1));
}

auto square = [](int value){ return value * value; };

TEST_CASE("Squares the number"){
    CHECK_EQ(4, square(2));
}

auto incrementSquareLambda = [](int value) { return increment(square(value));};

TEST_CASE("Increments the squared number"){
    CHECK_EQ(5, incrementSquareLambda(2));
}

template <class F, class G>
auto compose(F f, G g){
  return [=](auto value){return f(g(value));};
}

TEST_CASE("Increments twice with composed lambda"){
    auto incrementTwice = compose(increment, increment);
    CHECK_EQ(3, incrementTwice(1));
}


TEST_CASE("Increments square with composed lambda"){
    auto incrementSquare = compose(increment, square);
    CHECK_EQ(5, incrementSquare(2));
}
