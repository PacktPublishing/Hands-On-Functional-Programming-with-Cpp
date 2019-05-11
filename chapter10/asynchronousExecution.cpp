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

auto rangeFromTo = [](const int start, const int end){
    vector<int> aVector(end);
    iota(aVector.begin(), aVector.end(), start);
    return aVector;
};

auto rangeFrom1To = bind(rangeFromTo, 1, _1);

auto rangeFrom2To = bind(rangeFromTo, 2, _1);

auto isDivisibleBy = [](auto value, auto factor){
    return value % factor == 0;
};

auto all_of_collection = [](auto aCollection, auto lambda){
    return all_of(aCollection.begin(), aCollection.end(), lambda);
};

auto is_prime = [](int x) {
    return all_of_collection(
            rangeFrom2To(x), 
            bind(isDivisibleBy, x, _1)
        );
};

auto are_primes = [](auto aVector){
    return transformAll<vector<bool>>(aVector, is_prime);
};

auto isPrimeSequential = [](auto aVector){
    auto sequentialDuration = measureExecutionTimeForF(bind(are_primes, aVector));
    cout << "is prime sequential execution time:" << sequentialDuration.count() << " ns" << endl;
};

auto arePrimesAsync = [](auto aVector){
    auto naiveAsyncDuration = measureExecutionTimeForF([&](){
            return async(are_primes, aVector).get();
    });
    cout << "Async execution time naive:" << naiveAsyncDuration.count() << " ns" << endl;
};

auto runAsync = [](auto aVector){
    vector<future<bool>> futures(aVector.size()); 
    for(const int& value : aVector){
        futures.emplace_back(async(launch::async, is_prime, value));
    }

    vector<bool> results(aVector.size());
    for(future<bool>& aFuture : futures){
        if(aFuture.valid()){ 
            auto value = aFuture.get();
            results.push_back(value);
        }
        else {
            results.push_back(false);
            cout << "Invalid future!" << endl;
        }
    }

    for(auto result : results){
        cout << result << ", ";
    }

    cout << endl;
    return results;
};

auto measureRunAsync = [](auto aVector){
    auto asyncDuration = measureExecutionTimeForF(bind(runAsync, aVector));
    cout << "is prime async execution time:" << asyncDuration.count() << " ns" << endl;
};


TEST_CASE("is prime"){
    auto aVector = rangeFrom1To(10);

    isPrimeSequential(aVector);
    arePrimesAsync(aVector);
    measureRunAsync(aVector);
}

TEST_CASE("all_of with sequential execution policy"){
    vector<int> aVector(80);
    iota(aVector.begin(), aVector.end(), 1);

    auto all_factorials = [&](auto aVector){
        return transformAll<vector<long>>(aVector, factorial);
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
                    });
            return results;
            });
    cout << "Async execution time:" << asyncDuration.count() << " ns" << endl;
}
