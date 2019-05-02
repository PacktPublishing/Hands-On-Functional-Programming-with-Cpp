#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

auto measureExecutionTimeForF = [](auto f){
    auto t1 = high_resolution_clock::now();
    f();
    auto t2 = high_resolution_clock::now();
    chrono::nanoseconds duration = t2 - t1;
    return duration;
};

template<typename ReturnType, typename... Args>
function<ReturnType(Args...)> memoize(function<ReturnType(Args...)> f){
    map<tuple<Args...>, ReturnType> cache;
    return ([=](Args... args) mutable  {
            tuple<Args...> theArguments(args...);
            auto cached = cache.find(theArguments);
            if(cached != cache.end()) return cached -> second;
            auto result = f(args...);
            cache[theArguments] = result;
            return result;
    });
};

auto printDuration = [](string message, auto f){
    auto duration = measureExecutionTimeForF(f);
    cout << message  << duration.count() << " ns" << endl;
};

TEST_CASE("Pow vs memoized pow"){
    function<int(int, int)> power = [](auto first, auto second){
        return first ^ second;
    };

    cout << "Computing pow" << endl;
    printDuration("First call no memoization: ",  [&](){ return power(5, 24);});
    printDuration("Second call no memoization: ", [&](){return power(3, 1024);});
    printDuration("Third call no memoization: ", [&](){return power(9, 176);});
    printDuration("Fourth call no memoization (same as first call): ", [&](){return power(5, 24);});

    auto powerWithMemoization = memoize(power);
    printDuration("First call with memoization: ",  [&](){ return powerWithMemoization(5, 24);});
    printDuration("Second call with memoization: ", [&](){return powerWithMemoization(3, 1024);});
    printDuration("Third call with memoization: ", [&](){return powerWithMemoization(9, 176);});
    printDuration("Fourth call with memoization (same as first call): ", [&](){return powerWithMemoization(5, 24);});
    cout << "DONE computing pow" << endl;

    CHECK_EQ(power(5, 24),  powerWithMemoization(5, 24));
    CHECK_EQ(power(3, 1024),  powerWithMemoization(3, 1024));
    CHECK_EQ(power(9, 176),  powerWithMemoization(9, 176));
}

TEST_CASE("Complex expression vs memoized"){
    function<int(int, int)> expression = [](auto first, auto second){
        return (first * (25^7)) + (39^second);
    };

    cout << "Computing expression" << endl;
    printDuration("First call no memoization: ",  [&](){ return expression(5, 24);});
    printDuration("Second call no memoization: ", [&](){return expression(3, 1024);});
    printDuration("Third call no memoization: ", [&](){return expression(9, 176);});
    printDuration("Fourth call no memoization (same as first call): ", [&](){return expression(5, 24);});

    auto expressionWithMemoization = memoize(expression);
    printDuration("First call with memoization: ",  [&](){ return expressionWithMemoization(5, 24);});
    printDuration("Second call with memoization: ", [&](){return expressionWithMemoization(3, 1024);});
    printDuration("Third call with memoization: ", [&](){return expressionWithMemoization(9, 176);});
    printDuration("Fourth call with memoization (same as first call): ", [&](){return expressionWithMemoization(5, 24);});
    cout << "DONE computing expression" << endl;

    CHECK_EQ(expression(5, 24),  expressionWithMemoization(5, 24));
    CHECK_EQ(expression(3, 1024),  expressionWithMemoization(3, 1024));
    CHECK_EQ(expression(9, 176),  expressionWithMemoization(9, 176));
}

TEST_CASE("Factorial difference vs memoized"){
    function<int(int)> fact = [&fact](int n){
        if(n == 0) return 1;
        return n * fact(n-1);
    };

    function<int(int, int)> factorialDifference = [&fact](auto first, auto second){
        return fact(second) - fact(first);
    };

    cout << "Computing factorial difference" << endl;
    printDuration("First call no memoization: ",  [&](){ return factorialDifference(5, 24);});
    printDuration("Second call no memoization: ", [&](){return factorialDifference(3, 1024);});
    printDuration("Third call no memoization: ", [&](){return factorialDifference(9, 176);});
    printDuration("Fourth call no memoization (same as first call): ", [&](){return factorialDifference(5, 24);});

    auto factWithMemoization = memoize(fact);
    function<int(int, int)> factorialMemoizedDifference = [&factWithMemoization](auto first, auto second){
        return factWithMemoization(second) - factWithMemoization(first);
    };
    printDuration("First call with memoized factorial: ",  [&](){ return factorialMemoizedDifference(5, 24);});
    printDuration("Second call with memoized factorial: ", [&](){return factorialMemoizedDifference(3, 1024);});
    printDuration("Third call with memoized factorial: ", [&](){return factorialMemoizedDifference(9, 176);});
    printDuration("Fourth call with memoized factorial (same as first call): ", [&](){return factorialMemoizedDifference(5, 24);});
 
    auto factorialDifferenceWithMemoization = memoize(factorialDifference);
    printDuration("First call with memoization: ",  [&](){ return factorialDifferenceWithMemoization(5, 24);});
    printDuration("Second call with memoization: ", [&](){return factorialDifferenceWithMemoization(3, 1024);});
    printDuration("Third call with memoization: ", [&](){return factorialDifferenceWithMemoization(9, 176);});
    printDuration("Fourth call with memoization (same as first call): ", [&](){return factorialDifferenceWithMemoization(5, 24);});

    cout << "DONE computing factorial difference" << endl;

    CHECK_EQ(factorialDifference(5, 24),  factorialMemoizedDifference(5, 24));
    CHECK_EQ(factorialDifference(3, 1024),  factorialMemoizedDifference(3, 1024));
    CHECK_EQ(factorialDifference(9, 176),  factorialMemoizedDifference(9, 176));

    CHECK_EQ(factorialDifference(5, 24),  factorialDifferenceWithMemoization(5, 24));
    CHECK_EQ(factorialDifference(3, 1024),  factorialDifferenceWithMemoization(3, 1024));
    CHECK_EQ(factorialDifference(9, 176),  factorialDifferenceWithMemoization(9, 176));
}

TEST_CASE("Factorial difference vs recursively memoized factorial"){
    map<int, int> cache;
    function<int(int)> recursiveMemoizedFactorial = [&recursiveMemoizedFactorial, &cache](int n) mutable{
        auto value = cache.find(n); 
        if(value != cache.end()) return value->second;
        int result;

        if(n == 0) 
            result = 1;
        else 
            result = n * recursiveMemoizedFactorial(n-1);

        cache[n] = result;
        return result;
    };

    function<int(int, int)> factorialMemoizedDifference = [&recursiveMemoizedFactorial](auto first, auto second){
        return recursiveMemoizedFactorial(second) - recursiveMemoizedFactorial(first);
    };

    function<int(int)> fact = [&fact](int n){
        if(n == 0) return 1;
        return n * fact(n-1);
    };

    function<int(int, int)> factorialDifference = [&fact](auto first, auto second){
        return fact(second) - fact(first);
    };

    cout << "Computing factorial difference" << endl;
    printDuration("First call no memoization: ",  [&](){ return factorialDifference(5, 24);});
    printDuration("Second call no memoization: ", [&](){return factorialDifference(3, 1024);});
    printDuration("Third call no memoization: ", [&](){return factorialDifference(9, 176);});
    printDuration("Fourth call no memoization (same as first call): ", [&](){return factorialDifference(5, 24);});

    printDuration("First call with recursive memoized factorial: ",  [&](){ return factorialMemoizedDifference(5, 24);});
    printDuration("Second call with recursive memoized factorial: ", [&](){return factorialMemoizedDifference(3, 1024);});
    printDuration("Third call with recursive memoized factorial: ", [&](){return factorialMemoizedDifference(9, 176);});
    printDuration("Fourth call with recursive memoized factorial (same as first call): ", [&](){return factorialMemoizedDifference(5, 24);});

    CHECK_EQ(factorialDifference(5, 24),  factorialMemoizedDifference(5, 24));
    CHECK_EQ(factorialDifference(3, 1024),  factorialMemoizedDifference(3, 1024));
    CHECK_EQ(factorialDifference(9, 176),  factorialMemoizedDifference(9, 176));
} 
