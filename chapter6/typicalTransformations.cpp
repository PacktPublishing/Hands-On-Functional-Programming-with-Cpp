#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;


TEST_CASE("all_of"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK_EQ(true, all_of(abc.begin(), abc.end(), [](auto x){ return true;}));
    CHECK_EQ(false, all_of(abc.begin(), abc.end(), [](auto x){ return false;}));
    CHECK_EQ(false, all_of(abc.begin(), abc.end(), [](auto x){ return x == 'a';}));
    CHECK_EQ(true, all_of(abc.begin(), abc.end(), [](auto x){ return x != 'd';}));
}

auto all_of_collection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

TEST_CASE("all_of_collection"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK_EQ(true, all_of_collection(abc, [](auto x){ return true;}));
    CHECK_EQ(false, all_of_collection(abc, [](auto x){ return false;}));
    CHECK_EQ(false, all_of_collection(abc, [](auto x){ return x == 'a';}));
    CHECK_EQ(true, all_of_collection(abc, [](auto x){ return x != 'd';}));
}

