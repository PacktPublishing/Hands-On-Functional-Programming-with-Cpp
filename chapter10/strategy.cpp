#include <iostream>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

class Comparator{
    public: 
        bool operator() (int first, int second) { return (first < second);}
};

TEST_CASE("Sort with functor"){
    Comparator comparator;
    vector<int> values {23, 1, 42, 83, 52, 5, 72, 11};
    vector<int> expected {1, 5, 11, 23, 42, 52, 72, 83};

    sort(values.begin(), values.end(), comparator);

    CHECK_EQ(values, expected);
}


auto compare = [](auto first, auto second) { return first < second;};

TEST_CASE("Sort with function"){
    vector<int> values {23, 1, 42, 83, 52, 5, 72, 11};
    vector<int> expected {1, 5, 11, 23, 42, 52, 72, 83};

    sort(values.begin(), values.end(), compare);

    CHECK_EQ(values, expected);
}

template<typename DestinationType>
auto transformAll = [](auto source, auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto accumulateAll = [](auto source, auto initialValue, auto lambda){
    return accumulate(source.begin(), source.end(), initialValue, lambda);
};


map<string, double> drinkPrices = {
    {"Westmalle Tripel", 15.50},
    {"Lagavulin 18y", 25.20},
};

auto happyHourBilling = [](auto price){
    return price / 2;
};

auto normalBilling = [](auto price){
    return price;
};

auto computeBill = [](auto drinks, auto billingStrategy){
    auto prices = transformAll<vector<double>>(drinks, [](auto drink){ return drinkPrices[drink]; });
    auto sum = accumulateAll(prices, 0.0, std::plus<double>());
    return billingStrategy(sum);
};

TEST_CASE("Compute total bill from list of drinks, normal billing"){
   vector<string> drinks; 
   double expectedBill;

   SUBCASE("no drinks"){
       drinks = {};
       expectedBill = 0;
   };

   SUBCASE("one drink no discount"){
       drinks = {"Westmalle Tripel"};
       expectedBill = 15.50;
   };

   SUBCASE("one another drink no discount"){
       drinks = {"Lagavulin 18y"};
       expectedBill = 25.20;
   };

  double actualBill = computeBill(drinks, normalBilling);

   CHECK_EQ(expectedBill, actualBill);
}

TEST_CASE("Compute total bill from list of drinks, happy hour"){
   vector<string> drinks; 
   double expectedBill;

   SUBCASE("no drinks"){
       drinks = {};
       expectedBill = 0;
   };

   SUBCASE("one drink happy hour"){
       drinks = {"Lagavulin 18y"};
       expectedBill = 12.60;
   };

   double actualBill = computeBill(drinks, happyHourBilling);

   CHECK_EQ(expectedBill, actualBill);
}
