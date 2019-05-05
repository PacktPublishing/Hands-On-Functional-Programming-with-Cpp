#include <algorithm>
#include <random>
#include <functional>
#include <numeric>
#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

auto range = [](auto minValue, auto maxValue){
    vector<int> range(maxValue - minValue + 1);
    iota(range.begin(), range.end(), minValue);
    return range;
};

template<typename DestinationType>
auto transformAll = [](const auto& source, auto lambda){
    DestinationType result;
    result.resize(source.size());
    transform(source.begin(), source.end(), result.begin(), lambda);
    return result;
};

auto power = [](int first, int second){
    return pow(first, second);
};

auto generate_ints = [](int min, int max){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(min, max);
    auto values = transformAll<vector<int>>(range(0, 98), 
            [&distribution, &generator](auto){
                return distribution(generator);
            });
    values.push_back(min);
    values.push_back(max);
    return values;
};

auto logMaxIntBaseX = [](int x) -> int{
    auto maxInt = numeric_limits<int>::max() ;
    return (int)floor(log(maxInt) / log(x));
};

auto generate_ints_greater_than_1 = bind(generate_ints, 1, numeric_limits<int>::max());
auto generate_ints_greater_than_0 = bind(generate_ints, 0, numeric_limits<int>::max());
auto generate_exponent_less_than_log_maxInt = [](auto x){
    return generate_ints(x, logMaxIntBaseX(x));
};

auto all_of_collection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

auto printGeneratedValues = [](const string& generatorName, const auto& values){
    cout << "Check generator " << generatorName << endl;
    for_each(values.begin(), values.end(), [](auto value) { cout << value << ", ";});
    cout << endl;
 };

auto check_property = [](auto generator, auto property, string generatorName){
    auto values = generator();
    printGeneratedValues(generatorName, values);
    CHECK(all_of_collection(values, property));
};

auto property_0_to_power_0_is_1 = [](){
    return power(0, 0) == 1;
};

auto prop_0_to_any_nonzero_int_is_0= [](int exponent){
    CHECK(exponent > 0);
    return power(0, exponent) == 0;
};

auto prop_anyIntToPower0Is1 = [](int base){
    CHECK(base > 0);
    return power(base, 0) == 1;
};

auto prop_any_int_to_power_1_is_the_value = [](int base){
    return power(base, 1) == base;
};

auto prop_nextPowerOfXIsPreviousPowerOfXMultipliedByX = [](int x){
    auto exponents = bind(generate_exponent_less_than_log_maxInt, x);
    check_property(exponents, [x](auto y){ return power(x, y) == power(x, y - 1) * x;}, "generate exponents");
};


TEST_CASE("Properties"){
    cout << "Property: 0 to power 0 is 1" << endl;
    CHECK(property_0_to_power_0_is_1);

    cout << "Property: 0 to any non-zero power is 0" << endl;
    check_property(generate_ints_greater_than_1, prop_0_to_any_nonzero_int_is_0, "generate ints");

    cout << "Property: any int to power 0 is 1" << endl;
    check_property(generate_ints_greater_than_1, prop_anyIntToPower0Is1, "generate ints");

    cout << "Property: any int to power 1 is the value" << endl;
    check_property(generate_ints_greater_than_0, prop_any_int_to_power_1_is_the_value, "generate ints");

//    cout << "Property: next power of x is previous power of x multiplied by x" << endl;
//    check_property(generate_ints_greater_than_1, prop_nextPowerOfXIsPreviousPowerOfXMultipliedByX, "generate ints");
}
