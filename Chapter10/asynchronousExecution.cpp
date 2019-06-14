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

template<typename DestinationType>
auto transformAll = [](const auto& source, auto lambda){
    DestinationType result(source.size());
    transform(source.begin(), source.end(), result.begin(), lambda);
    return result;
};

function<long long(int)> factorial = [](int value){
    return (value == 0) ? 1 : (value * factorial(value - 1));
};

auto rangeFromTo = [](const int start, const int end){
    vector<int> aVector(end - start + 1);
    iota(aVector.begin(), aVector.end(), start);
    return aVector;
};

auto rangeFrom1To = bind(rangeFromTo, 1, _1);

auto rangeFrom2To = bind(rangeFromTo, 2, _1);

auto isDivisibleBy = [](auto value, auto factor){
    return (value % factor == 0); 
};

auto none_of_collection = [](auto aCollection, auto lambda){
    return none_of(aCollection.begin(), aCollection.end(), lambda);
};

auto is_prime = [](int x) {
    auto xIsDivisibleBy = bind(isDivisibleBy, x, _1);
    return none_of_collection(
            rangeFrom2To(x - 1), 
            xIsDivisibleBy
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


/*
TEST_CASE("is prime"){
    auto aVector = rangeFrom1To(10);

    isPrimeSequential(aVector);
    arePrimesAsync(aVector);
    measureRunAsync(aVector);
}
*/

auto printSecretMessage = [](std::future<string>& secretMessageFuture) {
    string secretMessage = secretMessageFuture.get();
    std::cout << "The secret message: " << secretMessage << '\n';
};

auto futureWithPromise = [](){
    promise<string> secretMessagePromise;
    future<string> secretMessageFuture = secretMessagePromise.get_future();
    thread isPrimeThread(printSecretMessage, ref(secretMessageFuture));

    secretMessagePromise.set_value("It's a secret");
    isPrimeThread.join();
};

TEST_CASE("Future with promise"){
    futureWithPromise();
}

TEST_CASE("is prime"){
    CHECK(is_prime(2));
    CHECK(is_prime(3));
    CHECK(is_prime(7));
    CHECK(!is_prime(4));
    CHECK(is_prime(7757));
}

TEST_CASE("Future with async"){
    future<bool> futureIsPrime(async(is_prime, 7757));
    cout << "doing stuff ..." << endl;
    bool isPrime = futureIsPrime.get();

    CHECK(isPrime);
}

TEST_CASE("Naive async duration"){
    vector<int> aVector(80);
    iota(aVector.begin(), aVector.end(), 1);

    auto all_factorials = [&](auto aVector){
        return transformAll<vector<long>>(aVector, factorial);
    };

    auto naiveAsyncDuration = measureExecutionTimeForF(
      [&](){
          future<vector<long>> result(async(all_factorials, aVector));
          return result.get();
      });

      cout << "Async execution time naive:" << naiveAsyncDuration.count() << " ns" << endl;
}

TEST_CASE("more futures"){
    future<bool> future1(async(is_prime, 2));
    future<bool> future2(async(is_prime, 27));
    future<bool> future3(async(is_prime, 1977));
    future<bool> future4(async(is_prime, 7757));

    CHECK(future1.get());
    CHECK(!future2.get());
    CHECK(!future3.get());
    CHECK(future4.get());
}

TEST_CASE("more futures with loops"){
    vector<int> values{2, 27, 1977, 7757};
    vector<bool> expectedResults{true, false, false, true};

    vector<future<bool>> futures;
    for(auto value : values){
        futures.push_back(async(is_prime, value));
    }

    vector<bool> results;
    for(auto& future : futures){
        results.push_back(future.get());
    }

    CHECK_EQ(results, expectedResults);
}

TEST_CASE("more futures functional"){
    vector<int> values{2, 27, 1977, 7757};

    auto makeFuture = [](auto value){
        return async(is_prime, value);
    };

    vector<future<bool>> futures = transformAll<vector<future<bool>>>(values, makeFuture);
    vector<bool> results(values.size());
    transform(futures.begin(), futures.end(), results.begin(), [](future<bool>& future){ return future.get();});

    vector<bool> expectedResults{true, false, false, true};

    CHECK_EQ(results, expectedResults);
}
