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

auto power = [](int first, int second){
    return pow(first, second);
};

auto prop_anyIntToPower0Is1 = [](int base){
    return power(base, 0) == 1;
};

auto property_0_to_power_0_is_1 = [](){
    return power(0, 0) == 1;
};

auto generate_ints = [](int min, int max){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(min, max);
    vector<int> values(100);
    values.push_back(min);
    values.push_back(max);
    for(int i = 0; i < 98; ++i){
        int value = distribution(generator);
        values.push_back(value);
    };
    return values;
};

auto generate_ints_greater_than_1 = bind(generate_ints, 1, numeric_limits<int>::max());
    
auto all_of_collection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

auto check_property = [](auto generator, auto property, string generatorName){
    cout << "Check generator " << generatorName << endl;
    auto values = generator();
    for_each(values.begin(), values.end(), [](auto value) { cout << value << ", ";});
    cout << endl;
    CHECK(all_of_collection(values, property));
};

TEST_CASE("Properties"){
    CHECK(property_0_to_power_0_is_1);
    check_property(generate_ints_greater_than_1, prop_anyIntToPower0Is1, "generate ints");
}
