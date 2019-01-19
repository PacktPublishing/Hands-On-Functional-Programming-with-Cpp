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

TEST_CASE("any_of"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK(any_of(abc.begin(), abc.end(), trueForAll));
    CHECK(!any_of(abc.begin(), abc.end(), falseForAll));
    CHECK(any_of(abc.begin(), abc.end(), equalsChara));
    CHECK(any_of(abc.begin(), abc.end(), notChard));
}

auto any_of_collection = [](auto collection, auto lambda){
    return any_of(collection.begin(), collection.end(), lambda);
};

TEST_CASE("any_of_collection"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK(any_of_collection(abc, trueForAll));
    CHECK(!any_of_collection(abc, falseForAll));
    CHECK(any_of_collection(abc, equalsChara));
    CHECK(any_of_collection(abc, notChard));
}



TEST_CASE("transform"){
    vector<char> abc = {'a', 'b', 'c'};

    vector<char> aaa(3);
    transform(abc.begin(), abc.end(), aaa.begin(), [](auto element){return 'a';});
    CHECK_EQ(vector<char>({'a', 'a', 'a'}), aaa);
}

template<typename Destination>
auto transform_all = [](auto const source, auto lambda){
    Destination destination(source.size());
    transform(source.begin(), source.end(), destination.begin(), lambda);
    return destination;
};

template<>
auto transform_all<string> = [](auto const source, auto lambda){
    string destination;
    transform(source.begin(), source.end(),  back_inserter(destination), lambda);
    return destination;
};

TEST_CASE("transform all"){
    vector<char> abc = {'a', 'b', 'c'};

    auto aaa = transform_all<vector<char>>(abc, [](auto element){return 'a';});
    CHECK_EQ(vector<char>({'a', 'a', 'a'}), aaa);
}

auto turnAllToa = [](auto x) { return 'a';};

auto makeCaps = [](auto x) { return toupper(x);};

auto toNumber = [](auto x) { return (int)x - 'a' + 1;};

TEST_CASE("transform all"){
    vector<char> abc = {'a', 'b', 'c'};

    CHECK_EQ(vector<char>({'a', 'a', 'a'}), transform_all<vector<char>>(abc, turnAllToa));
    CHECK_EQ("aaa", transform_all<string>(abc,turnAllToa));
    CHECK_EQ("ABC", transform_all<string>(abc, makeCaps));

    vector<int> expected = {1, 2, 3};
    CHECK_EQ(expected, transform_all<vector<int>>(abc, toNumber));
}

