#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto add = [](const int first, const int second) { return first + second; };

TEST_CASE("Adds values"){
    CHECK_EQ(42, add(25, 17));
}

auto curryAdd = [](const int first){ 
    return [first](const int second){
        return first + second;
    };
};

TEST_CASE("Adds values using captured curry"){
    CHECK_EQ(42, curryAdd(25)(17));
}

TEST_CASE("Increments value"){
    auto increment = curryAdd(1);

    CHECK_EQ(43, increment(42));
}

auto curryAddPartialApplication = [](const int first){ 
    return bind(add, first, _1);
};

TEST_CASE("Adds values using partial application curry"){
    CHECK_EQ(42, curryAddPartialApplication(25)(17));
}

auto addThree = [](const int first, const int second, const int third){
    return first + second + third;
};

auto curriedAddThree = [](const int first){
    return [first](const int second){ 
        return [first, second](const int third){
            return first + second + third;
        };
    };
}; 

TEST_CASE("Add three with curry"){
    CHECK_EQ(42, curriedAddThree(15)(10)(17));
}

TEST_CASE("Add three with partial application curry"){
    auto add = [](int a, int b) {return a+b;};
    auto addcurryOne = [add](int a){return  bind(add, a, _1);};

    CHECK_EQ(addcurryOne(1)(2), 3);

    auto addThree = [](int a, int b, int c){return a + b + c;};
    auto addThreeCurryOne = [=](int a, int b){return bind(addThree, a, b, _1);};
    CHECK_EQ(addThreeCurryOne(1, 2)(3), 6);

    auto addThreeCurryTwo = [=](int a){return bind(addThreeCurryOne, a, _1);};
    CHECK_EQ(addThreeCurryTwo(1)(2)(3), 6);

    auto addThreeCurryThree = bind(addThreeCurryTwo, _1);
    CHECK_EQ(addThreeCurryThree(1)(2)(3), 6);
}

auto simpleCurry1 = [](auto f){
    return f;
};

auto simpleCurry2 = [](auto f){
    return [f](auto x){ return bind(f, x, _1); };
};

auto simpleCurry3 = [](auto f){
    return [f](auto x, auto y){ return bind(f, x, y, _1); };
};

auto simpleCurry4 = [](auto f){
    return [f](auto x, auto y, auto z){ return bind(f, x, y, z, _1); };
};

auto curry2 = [](auto f){
    return simpleCurry2(f);
};

auto curry3 = [](auto f){
    return curry2(simpleCurry3(f));
};

auto curry4 = [](auto f){
    return curry3(simpleCurry4(f));
};

TEST_CASE("Add three with partial application curry"){
    auto add = [](int a, int b) { return a+b; };
    CHECK_EQ(3, curry2(add)(1)(2));

    auto addThreeCurryThree = curry3(addThree);
    CHECK_EQ(6, curry3(addThree)(1)(2)(3));

    auto addFour = [](int a, int b, int c, int d){return a + b + c + d;};
    CHECK_EQ(10, curry4(addFour)(1)(2)(3)(4));
}
