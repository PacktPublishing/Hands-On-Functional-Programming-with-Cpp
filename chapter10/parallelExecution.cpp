// At the time when I created this file, only MSVC had implementation for execution policies.
// Since you're seeing this in the future, you can enable the parallel execution code by uncommenting the following line 
//#define PARALLEL_ENABLED

#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#ifdef PARALLEL_ENABLED
#include <execution>
#endif

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

TEST_CASE("Baseline"){
    auto duration = measureExecutionTimeForF([](){return 1 + 1;});
    cout << duration.count() << " ns" << endl;
}

#ifdef PARALLEL_ENABLED
TEST_CASE("all_of with sequential execution policy"){
    auto aVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto all_of_sequential = [&aVector](){
        return all_of(execution::seq, aVector.begin(), aVector.end(), [](auto value){return value > 5;});
    };

    auto sequentialDuration = measureExecutionTimeForF(all_of_sequential);
    cout << "Execution time for sequential policy:" << sequentialDuration.count() << " ns" << endl;

    auto all_of_parallel = [&aVector](){
        return all_of(execution::par, aVector.begin(), aVector.end(), [](auto value){return value > 5;});
    };

    auto parallelDuration = measureExecutionTimeForF(all_of_parallel);
    cout << "Execution time for parallel policy:" << parallelDuration.count() << " ns" << endl;
}
#endif
