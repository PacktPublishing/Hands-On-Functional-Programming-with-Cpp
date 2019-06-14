#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto trueForAll = [](auto x) { return true; };
auto falseForAll = [](auto x) { return false; };
auto equalsChara = [](auto x){ return x == 'a';};
auto notChard = [](auto x){ return x != 'd';};

TEST_CASE("all_of"){
    vector abc{'a', 'b', 'c'};

    CHECK(all_of(abc.begin(), abc.end(), trueForAll));
    CHECK(!all_of(abc.begin(), abc.end(), falseForAll));
    CHECK(!all_of(abc.begin(), abc.end(), equalsChara));
    CHECK(all_of(abc.begin(), abc.end(), notChard));
}

auto all_of_collection = [](const auto& collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

TEST_CASE("all_of_collection"){
    vector abc{'a', 'b', 'c'};

    CHECK(all_of_collection(abc, trueForAll));
    CHECK(!all_of_collection(abc, falseForAll));
    CHECK(!all_of_collection(abc, equalsChara));
    CHECK(all_of_collection(abc, notChard));
}

TEST_CASE("any_of"){
    vector abc{'a', 'b', 'c'};

    CHECK(any_of(abc.begin(), abc.end(), trueForAll));
    CHECK(!any_of(abc.begin(), abc.end(), falseForAll));
    CHECK(any_of(abc.begin(), abc.end(), equalsChara));
    CHECK(any_of(abc.begin(), abc.end(), notChard));
}

auto any_of_collection = [](const auto& collection, auto lambda){
    return any_of(collection.begin(), collection.end(), lambda);
};

TEST_CASE("any_of_collection"){
    vector abc{'a', 'b', 'c'};

    CHECK(any_of_collection(abc, trueForAll));
    CHECK(!any_of_collection(abc, falseForAll));
    CHECK(any_of_collection(abc, equalsChara));
    CHECK(any_of_collection(abc, notChard));
}

TEST_CASE("transform"){
    vector abc{'a', 'b', 'c'};

    vector<char> aaa(3);
    transform(abc.begin(), abc.end(), aaa.begin(), [](auto element){return 'a';});
    CHECK_EQ(vector{'a', 'a', 'a'}, aaa);
}

TEST_CASE("transform-fixed") { 
    const auto abc = vector{'a', 'b', 'c'}; 
    vector<char> aaa; 
    aaa.reserve(abc.size()); 
    transform(abc.begin(), abc.end(), back_inserter(aaa), [](const char elem) { return 'a'; }); 
    CHECK_EQ(vector{'a', 'a', 'a'}, aaa); 
}

template<typename Destination>
auto transform_all = [](const auto& source, auto lambda){
    Destination destination;
    destination.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(destination), lambda);
    return destination;
};

TEST_CASE("transform all"){
    vector abc{'a', 'b', 'c'};

    auto aaa = transform_all<vector<char>>(abc, [](const char ){return 'a';});

    CHECK_EQ(vector{'a', 'a', 'a'}, aaa);
}

auto turnAllToa = [](auto x) { return 'a';};

auto makeCaps = [](auto x) { return toupper(x);};

auto toNumber = [](const char x) { return (int)x - 'a' + 1;};

TEST_CASE("transform all"){
    vector abc = {'a', 'b', 'c'};

    CHECK_EQ(vector{'a', 'a', 'a'}, transform_all<vector<char>>(abc, turnAllToa));
    CHECK_EQ("aaa", transform_all<string>(abc,turnAllToa));
    CHECK_EQ("ABC", transform_all<string>(abc, makeCaps));

    vector expected{1, 2, 3};
    CHECK_EQ(expected, transform_all<vector<int>>(abc, toNumber));
}

TEST_CASE("accumulate"){
    vector values{1, 12, 23, 45};

    auto add = [](int first, int second){return first + second;};
    int result = accumulate(values.begin(), values.end(), 0, add);
    CHECK_EQ(1 + 12 + 23 + 45, result);

    int resultWithInit100 = accumulate(values.begin(), values.end(), 100, add);
    CHECK_EQ(1 + 12 + 23 + 45 + 100, resultWithInit100);
    

    vector<string> strings{"Alex", "is", "here"};
    auto concatenate = [](const string first, const string second) -> string{
        return first + second;
    };

    string concatenated = accumulate(strings.begin(), strings.end(), string(), concatenate);
    CHECK_EQ("Alexishere", concatenated);

    string concatenatedWithPrefix = accumulate(strings.begin(), strings.end(), string("Pre_"), concatenate);
    CHECK_EQ("Pre_Alexishere", concatenatedWithPrefix);
}

auto equals1 = [](auto value){ return value == 1; };
auto greaterThan11 = [](auto value) { return value > 11; };
auto greaterThan50 = [](auto value) { return value > 50; };

TEST_CASE("find if"){
    vector<int> values{1, 12, 23, 45};

    auto result1 = find_if(values.begin(), values.end(), equals1);
    CHECK_EQ(*result1, 1);

    auto result12 = find_if(values.begin(), values.end(), greaterThan11);
    CHECK_EQ(*result12, 12);

    auto resultNotFound = find_if(values.begin(), values.end(), greaterThan50);
    CHECK_EQ(resultNotFound, values.end());
}

auto findInCollection = [](const auto& collection, auto lambda){
    auto result = find_if(collection.begin(), collection.end(), lambda);
    return (result == collection.end()) ? nullopt : optional(*result);
};

TEST_CASE("find in collection"){
    vector<int> values{1, 12, 23, 45};

    auto result1 = findInCollection(values, equals1);
    CHECK_EQ(result1, 1);

    auto result12 = findInCollection(values, greaterThan11);
    CHECK_EQ(result12, 12);

    auto resultNotFound = findInCollection(values, greaterThan50);
    CHECK(!resultNotFound.has_value());
}
