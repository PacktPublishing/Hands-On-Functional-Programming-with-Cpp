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

auto printDuration = [](string message, auto f){
    auto duration = measureExecutionTimeForF(f);
    cout << message  << duration.count() << " ns" << endl;
};

TEST_CASE("Factorial"){
    function<int(int)> fact = [&fact](int n){
        return (n == 0) ? 1 : (n * fact(n-1));
    };

    printDuration("Duration for 0!: ", [&](){return fact(0);});
    printDuration("Duration for 1!: ", [&](){return fact(1);});
    printDuration("Duration for 10!: ", [&](){return fact(10);});
    printDuration("Duration for 100!: ", [&](){return fact(100);});
    printDuration("Duration for 1024!: ", [&](){return fact(1024);});
}

TEST_CASE("Double recursion"){
    function<int(int)> f2;
    function<int(int)> f1 = [&f2](int n){
        return (n == 0) ? 1 : (n * f2(n-1));
    };

    f2 = [&f1](int n){
        return (n == 0) ? 2 : (f1(n) + f1(n-1));
    };

    printDuration("Duration for f1(0): ", [&](){return f1(0);});
    printDuration("Duration for f1(1): ", [&](){return f1(1);});
    printDuration("Duration for f1(2): ", [&](){return f1(2);});
    printDuration("Duration for f1(3): ", [&](){return f1(3);});
    printDuration("Duration for f1(4): ", [&](){return f1(4);});
    printDuration("Duration for f1(5): ", [&](){return f1(5);});
    printDuration("Duration for f1(6): ", [&](){return f1(6);});
    printDuration("Duration for f1(7): ", [&](){return f1(7);});
    printDuration("Duration for f1(8): ", [&](){return f1(8);});
}
