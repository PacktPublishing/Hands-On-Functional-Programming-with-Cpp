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

int sumOfEvenNumbersStructured(const list<int>& numbers){
    int sum = 0;
    for(auto number : numbers){
        if(number % 2 == 0) sum += number;
    }
    return sum;
};

auto isEven = [](const auto number){
    return number % 2 == 0;
};

auto isMultipleOf3 = [](const auto number){
    return number % 3 == 0;
};

auto pickNumbers  = [](const auto& numbers, auto predicate){
    list<int> pickedNumbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(pickedNumbers), predicate);
    return pickedNumbers;
};

auto sum = [](const auto& numbers){
    return accumulate(numbers.begin(), numbers.end(), 0);
};

auto sumOfEvenNumbersFunctional = [](const auto& numbers){
    return sum(pickNumbers(numbers, isEven));
};

auto sumOfEvenNumbersLazy = [](const auto& numbers){
    return ranges::accumulate(ranges::view::filter(numbers, isEven), 0);
};

auto sumOfMultiplesOf6 = [](const auto& numbers){
    return ranges::accumulate(
            numbers | ranges::view::filter(isEven) | ranges::view::filter(isMultipleOf3), 0);
};

TEST_CASE("Sum of even numbers and of multiples of 6"){
    list<int> numbers{1, 2, 5, 6, 10, 12, 17, 25};

    CHECK_EQ(30, sumOfEvenNumbersStructured(numbers));
    CHECK_EQ(30, sumOfEvenNumbersFunctional(numbers));
    CHECK_EQ(30, sumOfEvenNumbersLazy(numbers));
    CHECK_EQ(18, sumOfMultiplesOf6(numbers));
}

auto sortedListOfEvenNumbers = [](auto& numbers){
    numbers |= ranges::action::sort;
    return numbers;
};

TEST_CASE("Sort numbers"){
    vector<int> numbers{1, 12, 5, 20, 2, 10, 17, 25, 4};
    vector<int> expected{1, 2, 4, 5, 10, 12, 17, 20, 25};

    numbers |= ranges::action::sort;

    CHECK_EQ(expected, numbers);
}

TEST_CASE("Sort numbers and pick unique"){
    vector<int> numbers{1, 1, 12, 5, 20, 2, 10, 17, 25, 4};
    vector<int> expected{1, 2, 4, 5, 10, 12, 17, 20, 25};

    numbers |= ranges::action::sort | ranges::action::unique;

    CHECK_EQ(expected, numbers);
}

TEST_CASE("Infinite series"){
    vector<int> values = ranges::view::ints(1) | ranges::view::take(5);
    vector<int> expected{1, 2, 3, 4, 5};

    CHECK_EQ(expected, values);
}

TEST_CASE("Infinite series"){
    vector<char> values = ranges::view::iota('a') | ranges::view::take(5);
    vector<char> expected{'a', 'b', 'c', 'd', 'e'};

    CHECK_EQ(expected, values);
}

TEST_CASE("Linear distributed"){
    vector<int> values = ranges::view::linear_distribute(1, 10, 5);
    vector<int> expected{1, 3, 5, 7, 10};

    CHECK_EQ(expected, values);
}


