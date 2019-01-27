#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

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
    resultValueAndLog.log = valueAndLog.log + "Half: " + to_string(resultValueAndLog.value);
    return resultValueAndLog;
};

auto doubleValue = [](auto value){ return value * 2;};

auto doubleWithLogging = [](const ValueAndLog& valueAndLog){
    ValueAndLog resultValueAndLog;
    resultValueAndLog.value = doubleValue(valueAndLog.value);
    resultValueAndLog.log = valueAndLog.log + "Double: " + to_string(resultValueAndLog.value);
    return resultValueAndLog;
};

auto logDouble = [](auto previous, auto value){
    return previous + "Double: " + to_string(value);
};

auto something = [](auto valueAndLog, auto computeLambda, auto logLambda){
    auto newValue = computeLambda(valueAndLog.value);
    auto newLog = logLambda(valueAndLog.log, newValue);
    return ValueAndLog{newValue, newLog};
};

auto doubleWithLoggingAndMonad = bind(something, _1, doubleValue, logDouble);

TEST_CASE("half"){
    CHECK_EQ(4, half(8));
    CHECK_EQ(2, half(half(8)));
}

TEST_CASE("half with log"){
    ValueAndLog input{8, ""};
    ValueAndLog expected{4, "Half: 4"};

    auto actual = halfWithLogging(input);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated half with log"){
    ValueAndLog input{8, ""};
    ValueAndLog expected{2, "Half: 4Half: 2"};

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
    ValueAndLog expected{4, "Double: 4"};

    auto actual = doubleWithLogging(input);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated double with log"){
    ValueAndLog input{2, ""};
    ValueAndLog expected{8, "Double: 4Double: 8"};

    auto actual = doubleWithLogging(doubleWithLogging(input));

    CHECK_EQ(expected.value, actual.value);
    CHECK_EQ(expected.log, actual.log);
}

TEST_CASE("double with log and monad"){
    ValueAndLog input{2, ""};
    ValueAndLog expected{4, "Double: 4"};

    auto actual = doubleWithLoggingAndMonad(input);

    CHECK_EQ(expected, actual);
}

TEST_CASE("repeated double with logging and monad"){
    ValueAndLog input{2, ""};
    ValueAndLog expected{8, "Double: 4Double: 8"};

    auto actual = doubleWithLoggingAndMonad(doubleWithLoggingAndMonad(input));

    CHECK_EQ(expected.value, actual.value);
    CHECK_EQ(expected.log, actual.log);
}
