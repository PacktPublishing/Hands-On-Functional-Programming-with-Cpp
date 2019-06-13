#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
using namespace std;
using namespace std::placeholders;

class Calculator{
    private:
        const int first;
        const int second;

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

        int negateInt() const {
            return -first;
        }

};

TEST_CASE("Adds"){
    Calculator calculator(1, 2);

    const int result = calculator.add();

    CHECK_EQ(result, 3);
}

TEST_CASE("Multiplies"){
    Calculator calculator(3, 2);

    const int result = calculator.multiply();

    CHECK_EQ(result, 6);
}

TEST_CASE("Modulo"){
    Calculator calculator(3, 2);

    const int result = calculator.mod();

    CHECK_EQ(result, 1);
}

TEST_CASE("Revert"){
    Calculator calculator(3, 2);

    const int result = calculator.negateInt();

    CHECK_EQ(result, -3);
}

auto add = [](const auto first, const auto second){
    return first + second;
};

auto multiply = [](const auto first, const auto second){
    return first * second;
};

auto mod = [](const auto first, const auto second){
    return first % second;
};

auto negateInt = [](const auto value){
    return -value;
};

auto initialize = [] (const auto first, const auto second) -> map<string, function<int()>>{
    return  {
        {"add", bind(add, first, second)},
        {"multiply", bind(multiply, first, second)},
        {"mod", bind(mod, first, second)},
        {"negateInt", bind(negateInt, first)}
    };
};


TEST_CASE("Adds"){
    auto calculator = initialize(1, 2);

    const int result = calculator["add"]();

    CHECK_EQ(result, 3);
}

TEST_CASE("Multiplies"){
    auto calculator = initialize(3, 2);

    const int result = calculator["multiply"]();

    CHECK_EQ(result, 6);
}

TEST_CASE("Modulo"){
    auto calculator = initialize(3, 2);

    const int result = calculator["mod"]();

    CHECK_EQ(result, 1);
}

TEST_CASE("Revert"){
    auto calculator = initialize(3, 2);

    const int result = calculator["negateInt"]();

    CHECK_EQ(result, -3);
}
