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

auto increment = [](const int value) {
    return value + 1;
};

auto decrement = [](const int value) {
    return value - 1;
};


auto logCall = [](const string name, const int value){
    return "Called " + name + " with value " + to_string(value);
};

// log = makeLoggable
// loggable = composeLoggable
//
//let log (name : string) (f : int -> int) : int -> int * string = 
//  fun x -> (f x, Printf.sprintf "Called %s on %i; " name x)
auto makeLoggable = [](const string name, const function<int(int)> f) -> function<pair<string, int>(const int)> {
    return [&name, &f](int value){
        string log = logCall(name, value);
        int result = f(value);
        return make_pair(log, result);
    };
};

//
//let loggable (name : string) (f : int -> int) : int * string -> int * string =
//  fun (x, s1) ->
//    let (y, s2) = log name f x in
//    (y, s1 ^ s2)

auto composeLoggable = [](const string name, const function<int(int)> f) -> function<pair<string, int>(pair<string, int>)>{
    return [name, f](const pair<string, int> logAndValue){
        pair<string, int> resultLogAndValue = makeLoggable(name, f)(logAndValue.second);
        return make_pair(logAndValue.first + resultLogAndValue.first, resultLogAndValue.second);
    };
};

auto bindLoggable = [](pair<string, int> m, function<pair<string, int>(int)> f) -> pair<string, int>{
    pair<string, int> result  = f(m.second);
    return make_pair(m.first + result.first, result.second);
};

TEST_CASE("Loggable"){
    CHECK_EQ(5, increment(decrement(5)));

    auto loggableDecrement = makeLoggable("decrement", decrement);
    auto decrementResult = loggableDecrement(5);
    CHECK_EQ("Called decrement with value 5", decrementResult.first);
    CHECK_EQ(4, decrementResult.second);

    auto loggableIncrement = makeLoggable("increment", increment);
    auto incrementResult = loggableIncrement(5);
    CHECK_EQ("Called increment with value 5", incrementResult.first);
    CHECK_EQ(6, incrementResult.second);

//    CHECK_EQ(5, makeLoggable(decrement(makeLoggable(increment(5)))));
}

template<typename ValueType>
struct Writer{
    Writer(const ValueType value) : value{value}, log{}{}
    Writer(const ValueType value, const string log) : value{value}, log{log}{}
    typedef pair<string, ValueType> LogAndValue;
    
    const ValueType value;
    const string log;

    Writer<ValueType> apply(const string name, function<ValueType(ValueType)> operation) { 
        const ValueType result = operation(value);
        const string newLog = log + name + " called with " + to_string(value) + "\n";
        return Writer{result, newLog};
    }
};


TEST_CASE("Compute with Writer monad"){
    auto incrementResult = Writer{1}.apply("increment", increment);
    CHECK_EQ(incrementResult.value, 2);
    CHECK_EQ(incrementResult.log, "increment called with 1\n");

    auto decrementResult = Writer{2}.apply("decrement", decrement);
    CHECK_EQ(decrementResult.value, 1);
    CHECK_EQ(decrementResult.log, "decrement called with 2\n");

    auto sameResult = Writer{1}.apply("increment", increment).apply("decrement", decrement);
    CHECK_EQ(sameResult.value, 1);
    CHECK_EQ(sameResult.log, "increment called with 1\ndecrement called with 2\n");
}
