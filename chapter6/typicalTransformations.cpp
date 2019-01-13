#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto trueForAll = [](auto x) { return true; };
auto falseForAll = [](auto x) { return false; };
auto equalsChara = [](auto x){ return x == 'a';};
auto notChard = [](auto x){ return x != 'd';};

TEST_CASE("all_of"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK(all_of(abc.begin(), abc.end(), trueForAll));
    CHECK(!all_of(abc.begin(), abc.end(), falseForAll));
    CHECK(!all_of(abc.begin(), abc.end(), equalsChara));
    CHECK(all_of(abc.begin(), abc.end(), notChard));
}

auto all_of_collection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

TEST_CASE("all_of_collection"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK(all_of_collection(abc, trueForAll));
    CHECK(!all_of_collection(abc, falseForAll));
    CHECK(!all_of_collection(abc, equalsChara));
    CHECK(all_of_collection(abc, notChard));
}

