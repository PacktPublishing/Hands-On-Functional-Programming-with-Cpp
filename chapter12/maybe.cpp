#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#include <optional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto to_string(optional<int> value){
    return (value.has_value()) ? to_string(value.value()) : "None";
}

TEST_CASE("Compute with optional"){
    auto plusOptional = [](optional<int> first, optional<int> second) -> optional<int>{
        return (first == nullopt || second == nullopt) ? 
            nullopt :
            make_optional(first.value() + second.value());
    };

    auto divideOptional = [](optional<int> first, optional<int> second) -> optional<int>{
        if (first == nullopt || second == nullopt) return nullopt; 
        if (second == 0) return nullopt;
        return make_optional(first.value() / second.value());
    };

    CHECK_EQ(optional{3}, plusOptional(optional{1}, optional{2}));
    CHECK_EQ(nullopt, plusOptional(nullopt, optional{2}));

    CHECK_EQ(optional{2}, divideOptional(optional{2}, optional{1}));
    CHECK_EQ(nullopt, divideOptional(nullopt, optional{1}));
    CHECK_EQ(nullopt, divideOptional(optional{2}, optional{0}));
    cout << "Result of 2 / 0 = " << to_string(divideOptional(optional{2}, optional{0})) << endl;
}

TEST_CASE("Compute with optional"){
    auto propagate_none = [](const function<int(int, int)> operation){
        return [operation](const optional<int> first, const optional<int> second) -> optional<int>{
            if(first == nullopt || second == nullopt) return nullopt;
            return make_optional(operation(first.value(), second.value()));
        };
    };

    auto plusOptional = propagate_none(plus<int>());
    auto divideOptional = propagate_none(divides<int>());

    CHECK_EQ(optional{3}, plusOptional(optional{1}, optional{2}));
    CHECK_EQ(nullopt, plusOptional(nullopt, optional{2}));

    CHECK_EQ(optional{2}, divideOptional(optional{2}, optional{1}));
    CHECK_EQ(nullopt, divideOptional(nullopt, optional{1}));
//    CHECK_EQ(nullopt, divideOptional(optional{2}, optional{0}));
//    cout << "Result of 2 / 0 = " << to_string(divideOptional(optional{2}, optional{0})) << endl;
}

TEST_CASE("Compute with optional"){
    function<optional<int>(const int, const int)> divideEvenWith0 = [](const int first, const int second) -> optional<int>{
        return (second == 0) ? nullopt : make_optional(first / second);
    };

    auto propagate_none = [](const function<optional<int>(const int, const int)> operation){
        return [operation](const optional<int> first, const optional<int> second) -> optional<int>{
            if(first == nullopt || second == nullopt) return nullopt;
            return operation(first.value(), second.value());
        };
    };

    auto plusOptional = propagate_none(plus<int>());
    auto divideOptional = propagate_none(divideEvenWith0);

    CHECK_EQ(optional{3}, plusOptional(optional{1}, optional{2}));
    CHECK_EQ(nullopt, plusOptional(nullopt, optional{2}));

    CHECK_EQ(optional{2}, divideOptional(optional{2}, optional{1}));
    CHECK_EQ(nullopt, divideOptional(nullopt, optional{1}));
    CHECK_EQ(nullopt, divideOptional(optional{2}, optional{0}));
    cout << "Result of 2 / 0 = " << to_string(divideOptional(optional{2}, optional{0})) << endl;
}


template<typename ValueType>
struct Maybe{
    typedef function<optional<ValueType>(const ValueType, const ValueType)> OperationType;
    optional<ValueType> value;
    
    optional<ValueType> apply(const OperationType operation, const optional<ValueType> second){
        if(value == nullopt || second == nullopt) return nullopt;
        return operation(value.value(), second.value());
    }
};

TEST_CASE("Compute with optional"){
    function<optional<int>(const int, const int)> divideEvenWith0 = [](const int first, const int second) -> optional<int>{
        return (second == 0) ? nullopt : make_optional(first / second);
    };

    CHECK_EQ(3, Maybe<int>{1}.apply(plus<int>(), 2));
    CHECK_EQ(nullopt, Maybe<int>{nullopt}.apply(plus<int>(), 2));
    CHECK_EQ(nullopt, Maybe<int>{1}.apply(plus<int>(), nullopt));

    CHECK_EQ(2, Maybe<int>{2}.apply(divideEvenWith0, 1));
    CHECK_EQ(nullopt, Maybe<int>{nullopt}.apply(divideEvenWith0, 1));
    CHECK_EQ(nullopt, Maybe<int>{2}.apply(divideEvenWith0, nullopt));
    CHECK_EQ(nullopt, Maybe<int>{2}.apply(divideEvenWith0, 0));
    cout << "Result of 2 / 0 = " << to_string(Maybe<int>{2}.apply(divideEvenWith0, 0)) << endl;
}

