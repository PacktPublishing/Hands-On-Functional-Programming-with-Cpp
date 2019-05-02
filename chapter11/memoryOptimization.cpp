#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

const long size_1GB_64Bits = 125000000;


#if NO_MOVE_ITERATOR
auto increment = [](const auto value){
    return value + 1;
};

template<typename DestinationType>
auto transformAll = [](const auto& source, auto lambda){
    DestinationType result;
    result.resize(source.size());
    transform(source.begin(), source.end(), result.begin(), lambda);
    return result;
};

TEST_CASE("Memory"){
    auto size = size_1GB_64Bits;
    vector<long long> manyNumbers(size);
    fill_n(manyNumbers.begin(), size, 1000L);

    auto result = transformAll<vector<long long>>(manyNumbers, increment);

    CHECK_EQ(result[0], 1001);
}
#endif

#if IN_PLACE
auto increment = [](const auto value){
    return value + 1;
};

template<typename SourceType>
auto transformAllInPlace = [](auto& source, auto lambda) -> SourceType&& {
    transform(source.begin(), source.end(), source.begin(), lambda);
    return move(source);
};

TEST_CASE("Memory"){
    auto size = size_1GB_64Bits;
    vector<long long> manyNumbers(size);
    fill_n(manyNumbers.begin(), size, 1000L);

    auto result = transformAllInPlace<vector<long long>>(manyNumbers, increment);

    CHECK_EQ(result[0], 1001);
}
#endif

#if MOVE_ITERATOR 
auto increment = [](const auto& value){
    return value + 1;
};

template<typename DestinationType>
auto transformAllWithMoveIterator = [](auto& source, auto lambda){
    DestinationType result(source.size());
    transform(make_move_iterator(source.begin()), make_move_iterator(source.end()), result.begin(), lambda);
    source.clear();
    return result;
};

TEST_CASE("Memory"){
    auto size = size_1GB_64Bits;
    vector<long long> manyNumbers(size);
    fill_n(manyNumbers.begin(), size, 1000L);

    auto result = transformAllWithMoveIterator<vector<long long>>(manyNumbers, increment);

    CHECK_EQ(result[0], 1001);
}
#endif

#if FOR
TEST_CASE("Memory"){
    auto size = size_1GB_64Bits;
    vector<long long> manyNumbers(size);
    fill_n(manyNumbers.begin(), size, 1000L);

    for(auto iter = manyNumbers.begin(); iter != manyNumbers.end(); ++iter){
        ++(*iter);
    };

    CHECK_EQ(manyNumbers[0], 1001);
}
#endif
