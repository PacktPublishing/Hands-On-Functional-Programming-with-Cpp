#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <functional>

using namespace std;

auto increment = [](const int value) { return value + 1; };
auto square = [](int value){ return value * value; };

auto simpleCompose(function<int(int)> f, function<int(int)> g){
    return [=](auto x){return f(g(x));};
}

TEST_CASE("Increments twice with composed lambda"){
    auto incrementTwice = simpleCompose(increment, increment);
    CHECK_EQ(3, incrementTwice(1));
}

TEST_CASE("Increments square with composed lambda"){
    auto incrementSquare = simpleCompose(increment, square);
    CHECK_EQ(5, incrementSquare(2));
}

template <class F, class G>
auto compose(F f, G g){
  return [=](auto value){return f(g(value));};
}

TEST_CASE("Increments twice with generic composed lambda"){
    auto incrementTwice = compose(increment, increment);
    CHECK_EQ(3, incrementTwice(1));
}

TEST_CASE("Increments square with generic composed lambda"){
    auto incrementSquare = compose(increment, square);
    CHECK_EQ(5, incrementSquare(2));
}

TEST_CASE("Square the increment"){
    auto squareIncrement = compose(square, increment);
    CHECK_EQ(9, squareIncrement(2));
}
