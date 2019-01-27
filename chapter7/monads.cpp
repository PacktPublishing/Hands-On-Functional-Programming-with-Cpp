#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

template<typename F, typename G>
auto compose(F f, G g){
    return [&](auto value){
        return f(g(value));
    };
}

auto half = [](auto value) { return value / 2; };

struct ValueAndLog{
    int value;
    string log;

    bool operator==(const ValueAndLog& other) const {
        return other.log == log && other.value == value;
    };
};

auto halfWithLogging = [](const ValueAndLog& valueAndLog){ 
    ValueAndLog resultValueAndLog;
    resultValueAndLog.value = half(valueAndLog.value);
    resultValueAndLog.log = valueAndLog.log + "Halved: " + to_string(valueAndLog.value);
    return resultValueAndLog;
};

auto doubleValue = [](auto value){ return value * 2;};

auto doubleWithLogging = [](const ValueAndLog& valueAndLog){
    ValueAndLog resultValueAndLog;
    resultValueAndLog.value = doubleValue(valueAndLog.value);
    resultValueAndLog.log = valueAndLog.log + "Doubled: " + to_string(valueAndLog.value);
    return resultValueAndLog;
};

auto logDouble = [](auto previous, auto value){
    return previous + "Doubled: " + to_string(value);
};

// Type initializer
// Monad composition operator = bind

auto returnValue = [](auto value){
    return [value](auto log){
        return ValueAndLog{value, log};
    };
};

//auto composeMonads = [](){};

/*
auto computeAndWrite = [](ValueAndLog valueAndLog, auto computeLambda){
    auto newValue = computeLambda(valueAndLog.value);
    auto newLog = tell(valueAndLog, "Doubled: " + to_string(valueAndLog.value));
    returnValue(newValue);
};
*/

auto writerMonad = [](auto computeLambda){
    static string log;
    return [computeLambda](auto value){
        auto newValue = computeLambda(value);
        log += "Doubled: " + to_string(value);
        return newValue;
    };
};

auto doubleWithLoggingAndMonad = writerMonad(doubleValue);

TEST_CASE("half"){
    CHECK_EQ(4, half(8));
    CHECK_EQ(2, half(half(8)));
}

TEST_CASE("half with log"){
    ValueAndLog input{8, ""};
    ValueAndLog expected{4, "Halved: 8"};

    auto actual = halfWithLogging(input);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated half with log"){
    ValueAndLog input{8, ""};
    ValueAndLog expected{2, "Halved: 8Halved: 4"};

    auto actual = halfWithLogging(halfWithLogging(input));

    CHECK_EQ(expected.value, actual.value);
    CHECK_EQ(expected.log, actual.log);
}

TEST_CASE("double"){
    CHECK_EQ(4, doubleValue(2));
    CHECK_EQ(8, doubleValue(doubleValue(2)));
}

TEST_CASE("double with log"){
    ValueAndLog input{2, ""};
    ValueAndLog expected{4, "Doubled: 2"};

    auto actual = doubleWithLogging(input);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated double with log"){
    ValueAndLog input{2, ""};
    ValueAndLog expected{8, "Doubled: 2Doubled: 4"};

    auto actual = doubleWithLogging(doubleWithLogging(input));

    CHECK_EQ(expected.value, actual.value);
    CHECK_EQ(expected.log, actual.log);
}

TEST_CASE("double with log and monad"){
    //ValueAndLog input{2, ""};
    ValueAndLog expected{4, "Doubled: 2"};

//    auto actual = doubleWithLoggingAndMonad(input);
    auto actual = writerMonad(doubleValue)(2);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated double with logging and monad"){
    //ValueAndLog input{2, ""};
    ValueAndLog expected{8, "Doubled: 2Doubled: 4"};

    //auto actual = doubleWithLoggingAndMonad(doubleWithLoggingAndMonad(input));
    auto doubleWithLogging = writerMonad(doubleValue);
    auto actual = doubleWithLogging(doubleWithLogging(2));

    CHECK_EQ(expected, actual);
}
