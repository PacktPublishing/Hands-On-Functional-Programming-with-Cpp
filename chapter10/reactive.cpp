#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <functional>
#include <numeric>
#include <future>

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

template<typename DestinationType>
auto transformAll = [](const auto& source, auto lambda){
    DestinationType result(source.size());
    transform(source.begin(), source.end(), result.begin(), lambda);
    return result;
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

auto printIsPrime = [](int value){
    cout << value << (is_prime(value) ? " is prime" : " is not prime") << endl;
};

int main(){
    int number;

    while(true){
        cin >> number;
        async(printIsPrime, number);
    }
}
