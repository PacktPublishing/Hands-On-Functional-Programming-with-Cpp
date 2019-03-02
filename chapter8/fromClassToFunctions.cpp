#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
using namespace std;
using namespace std::placeholders;

class Calculator{
    private:
        int first;
        int second;

    public:
        Calculator(int first, int second): first(first), second(second){}

        int add() const {
            return first + second;
        }

        int multiply() const {
            return first * second;
        }

        int mod() const {
            return first % second;
        }

        int revert() const {
            return -first;
        }

};

TEST_CASE("Adds"){
    Calculator calculator(1, 2);

    int result = calculator.add();

    CHECK_EQ(result, 3);
}

TEST_CASE("Multiplies"){
    Calculator calculator(3, 2);

    int result = calculator.multiply();

    CHECK_EQ(result, 6);
}

TEST_CASE("Modulo"){
    Calculator calculator(3, 2);

    int result = calculator.mod();

    CHECK_EQ(result, 1);
}

TEST_CASE("Revert"){
    Calculator calculator(3, 2);

    int result = calculator.revert();

    CHECK_EQ(result, -3);
}

auto add = [](auto first, auto second){
    return first + second;
};

auto multiply = [](auto first, auto second){
    return first * second;
};

auto mod = [](auto first, auto second){
    return first % second;
};

auto revert = [](auto value){
    return -value;
};

auto initialize = [] (auto first, auto second) -> map<string, function<int()>>{
    return  {
        {"add", bind(add, first, second)},
        {"multiply", bind(multiply, first, second)},
        {"mod", bind(mod, first, second)},
        {"revert", bind(revert, first)}
    };
};


TEST_CASE("Adds"){
    auto calculator = initialize(1, 2);

    int result = calculator["add"]();

    CHECK_EQ(result, 3);
}

TEST_CASE("Multiplies"){
    auto calculator = initialize(3, 2);

    int result = calculator["multiply"]();

    CHECK_EQ(result, 6);
}

TEST_CASE("Modulo"){
    auto calculator = initialize(3, 2);

    int result = calculator["mod"]();

    CHECK_EQ(result, 1);
}

TEST_CASE("Revert"){
    auto calculator = initialize(3, 2);

    int result = calculator["revert"]();

    CHECK_EQ(result, -3);
}


