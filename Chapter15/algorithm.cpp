#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <range/v3/all.hpp>

using namespace std;
using namespace std::placeholders;

struct Person{
    string name;
    int age;

    Person(string name, int age) : name(name), age(age){};
};

bool operator==(const Person& first, const Person& second){
    return first.name == second.name && first.age == second.age;
};

template<typename DestinationType>
auto transformAll = [](auto source, auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto accumulateAll = [](auto collection, auto initialValue,  auto lambda){
    return accumulate(collection.begin(), collection.end(), initialValue, lambda);
};


TEST_CASE("Project names from a vector of people"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14)
    };

    vector<string> expectedNames{"Alex", "John", "Jane"};
    vector<string> names = transformAll<vector<string>>(
            people, 
            [](Person person) { return person.name; } 
            );

    CHECK_EQ(expectedNames, names);
}

TEST_CASE("Minor or major"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14)
    };

    vector<bool> expectedIsMinor{false, false, true};
    vector<bool> isMinor = transformAll<vector<bool>>(
            people, 
            [](Person person) { return person.age < 18; } 
            );

    CHECK_EQ(expectedIsMinor, isMinor);
}

TEST_CASE("String representation"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14)
    };

    vector<string> expectedJSON{
        "{'person': {'name': 'Alex', 'age': '42'}}",
            "{'person': {'name': 'John', 'age': '21'}}",
            "{'person': {'name': 'Jane', 'age': '14'}}"
    };
    vector<string> peopleAsJson = transformAll<vector<string>>(
            people, 
            [](Person person) { 
            return 
            "{'person': {'name': '" + person.name + "', 'age': '" + to_string(person.age) + "'}}"; } 
            );

    CHECK_EQ(expectedJSON, peopleAsJson);

    string expectedJSONList = "{people: {'person': {'name': 'Alex', 'age': '42'}}, {'person': {'name': 'John', 'age': '21'}}, {'person': {'name': 'Jane', 'age': '14'}}}";

    string peopleAsJSONList = "{people: " + accumulateAll(peopleAsJson, string(),
            [](string first, string second){
            return (first.empty()) ? second: (first + ", " + second);
            }) + "}";

    CHECK_EQ(expectedJSONList, peopleAsJSONList);
}

struct Product{
    string name;
    string category;
    double price;
    Product(string name, string category, double price): name(name), category(category), price(price){}
};

map<string, int> taxLevelByCategory = {
    {"book", 5},
    {"cosmetics", 20},
    {"food", 10},
    {"alcohol", 40}
};

TEST_CASE("Total price with tax"){
    vector<Product> products = {
        Product("Lord of the Rings", "book", 22.50),
        Product("Nivea", "cosmetics", 15.40),
        Product("apple", "food", 0.30),
        Product("Lagavulin", "alcohol", 75.35)
    };

    auto pricesWithTax = transformAll<vector<double>>(products, 
            [](Product product){
            int taxPercentage = taxLevelByCategory[product.category];
            return product.price + product.price * taxPercentage/100;
            });

    auto totalWithoutTax = accumulateAll(transformAll<vector<double>>(products, [](Product product) { return product.price; }), 0.0, plus<double>());
    auto totalWithTax = accumulateAll(pricesWithTax, 0.0, plus<double>());

    CHECK_EQ(113.55, doctest::Approx(totalWithoutTax));
    CHECK_EQ(147.925, doctest::Approx(totalWithTax));
}

TEST_CASE("Find all minors"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14),
        Person("Diana", 9)
    };

    vector<Person> expectedMinors{Person("Jane", 14), Person("Diana", 9)};

    vector<Person> minors;
    copy_if(people.begin(), people.end(), back_inserter(minors), [](Person& person){ return person.age < 18; });

    CHECK_EQ(minors, expectedMinors);
}

struct MajorOrMinorPerson{
    Person person;
    optional<string> majorOrMinor;

    MajorOrMinorPerson(Person person, string majorOrMinor) : person(person), majorOrMinor(optional<string>(majorOrMinor)){};

    MajorOrMinorPerson(Person person) : person(person), majorOrMinor(nullopt){};
};

TEST_CASE("Treat error cases"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14),
        Person("Diana", 0)
    };

    auto majorMinorPersons = transformAll<vector<MajorOrMinorPerson>>(people, [](Person& person){ 
            if(person.age <= 0) return MajorOrMinorPerson(person);
            if(person.age > 0 && person.age < 18) return MajorOrMinorPerson(person, "minor");
            return MajorOrMinorPerson(person, "major");
            });

    auto majorMinorPersonsAsString = transformAll<vector<string>>(majorMinorPersons, [](MajorOrMinorPerson majorOrMinorPerson){
            return majorOrMinorPerson.majorOrMinor ? 
            majorOrMinorPerson.person.name + ", " + majorOrMinorPerson.majorOrMinor.value() :
            "Invalid person";
            });

    auto completeString = accumulateAll(majorMinorPersonsAsString, string(), [](string first, string second){
            return first.empty() ? second : (first + "\n" + second);
            });

    string expectedString("Alex, major\nJohn, major\nJane, minor\nInvalid person");

    CHECK_EQ(expectedString, completeString);
}

auto personToMajorMinor = [](const Person& person){ 
    if(person.age <= 0) return MajorOrMinorPerson(person);
    if(person.age > 0 && person.age < 18) return MajorOrMinorPerson(person, "minor");
    return MajorOrMinorPerson(person, "major");
};

auto majorMinor = [](const MajorOrMinorPerson& majorOrMinorPerson){
    return majorOrMinorPerson.majorOrMinor ? 
        (majorOrMinorPerson.person.name + ", " + majorOrMinorPerson.majorOrMinor.value()) : 
        "Invalid person";
};

auto combineWithNewline = [](const string& first, const string& second){
    return first.empty() ? second : (first + "\n" + second);
};


TEST_CASE("Ranges"){
    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14),
        Person("Diana", 0)
    };
    using namespace ranges;


    string completeString = ranges::accumulate(
            people |
            view::transform(personToMajorMinor) | 
            view::transform(majorMinor),
            string(),
            combineWithNewline
           ); 
    string expectedString("Alex, major\nJohn, major\nJane, minor\nInvalid person");

    CHECK_EQ(expectedString, completeString);
}

auto isMinor = [](Person& person){ return person.age < 18; };

TEST_CASE("Find all minors with ranges"){
    using namespace ranges;

    vector<Person> people = {
        Person("Alex", 42),
        Person("John", 21),
        Person("Jane", 14),
        Person("Diana", 9)
    };
    vector<Person> expectedMinors{Person("Jane", 14), Person("Diana", 9)};

    vector<Person> minors = people | view::filter(isMinor);

    CHECK_EQ(minors, expectedMinors);
}


