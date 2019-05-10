#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#include <future>
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

template<typename DestinationType>
auto transformAll = [](auto source, auto lambda){
    DestinationType result(source.size());
    transform(source.begin(), source.end(), result.begin(), lambda);
    return result;
};

function<long long(int)> factorial = [](int value){
    return (value == 0) ? 1 : (value * factorial(value - 1));
};

TEST_CASE("Factorial"){
    CHECK_EQ(1, factorial(0));
    CHECK_EQ(1, factorial(1));
    CHECK_EQ(2, factorial(2));
    CHECK_EQ(6, factorial(3));
}

TEST_CASE("is prime"){

    vector<int> aVector(10000);
    iota(aVector.begin(), aVector.end(), 1);

    auto is_prime = [](int x) {
      for (int i=2; i<x; ++i) if (x%i==0) return false;
      return true;
    };

    auto are_primes = [&](auto aVector){
        return transformAll<vector<bool>>(aVector, is_prime);
    };

    auto all_primes_for_aVector = bind(are_primes, aVector);

    auto sequentialDuration = measureExecutionTimeForF(all_primes_for_aVector);
    cout << "is prime sequential execution time:" << sequentialDuration.count() << " ns" << endl;

    /*auto naiveAsyncDuration = measureExecutionTimeForF(
            [&](){
                future<vector<long long>> result(async(all_factorials, aVector));
                return result.get();
    });

    cout << "Async execution time naive:" << naiveAsyncDuration.count() << " ns" << endl;
   */ 
    auto asyncDuration = measureExecutionTimeForF(
            [&](){
                    vector<future<bool>> futures(aVector.size()); 
                    for(const int& value : aVector){
                        futures.push_back(future<bool>(async(is_prime, value)));
                    }

                    vector<bool> results(aVector.size());
                    for(auto& aFuture : futures){
                        results.push_back(aFuture.get());
                    }

                    for(auto result : results){
                        cout << result << endl;
                    }
                    return results;
            });
    cout << "is prime async execution time:" << asyncDuration.count() << " ns" << endl;
}

TEST_CASE("all_of with sequential execution policy"){
    vector<int> aVector(80);
    iota(aVector.begin(), aVector.end(), 1);

    auto all_factorials = [&](auto aVector){
        return transformAll<vector<long long>>(aVector, factorial);
    };

    auto all_factorials_for_aVector = bind(all_factorials, aVector);

    auto sequentialDuration = measureExecutionTimeForF(all_factorials_for_aVector);
    cout << "Sequential execution time:" << sequentialDuration.count() << " ns" << endl;

    /*auto naiveAsyncDuration = measureExecutionTimeForF(
            [&](){
                future<vector<long long>> result(async(all_factorials, aVector));
                return result.get();
    });

    cout << "Async execution time naive:" << naiveAsyncDuration.count() << " ns" << endl;
   */ 
    auto asyncDuration = measureExecutionTimeForF(
            [&](){
                    auto futures = transformAll<vector<future<long long>>>(aVector,
                        [&](auto value){
                            return future<long long>(async(factorial, value));
                        });

                    vector<long long> results(futures.size());
                    transform(futures.begin(), futures.end(), results.begin(), 
                            [](future<long long>& aFuture){ 
                                return aFuture.get();
                            }
                    );
                    return results;
            });
    cout << "Async execution time:" << asyncDuration.count() << " ns" << endl;
}
