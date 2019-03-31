#include <iostream>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

class Person{
    public:
        Person(string firstName, string lastName) : firstName(firstName), lastName(lastName){};
        string firstName;
        string lastName;
};

auto readPersonFromJSONFile = [](){ return Person("Alex", "Bolboaca");};

auto readPersonFromXMLFile = [](){ return Person("Alex", "Bolboaca");};

auto readPersonFromCSVFile = [](){ return Person("Alex", "Bolboaca");};

auto readPerson = [](){return readPersonFromCSVFile();};


TEST_CASE("Adapt call to different name same signature"){
    auto myFunction = readPersonFromXMLFile;
    CHECK_EQ(5, myFunction());
}


auto add = [](int first, int second){
    return first + second;
};


TEST_CASE("Adapt call with multiple parameters to call with fewer parameters"){
    CHECK_EQ(true, false);
}

TEST_CASE("Adapt call with different data formats"){
    CHECK_EQ(true, false);
}

TEST_CASE("Adapt call with completely different signature"){
    CHECK_EQ(true, false);
}

template<typename DestinationType>
auto transformAll = [](auto source, auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto accumulateAll = [](auto source, auto initialValue, auto lambda){
    return accumulate(source.begin(), source.end(), initialValue, lambda);
};
