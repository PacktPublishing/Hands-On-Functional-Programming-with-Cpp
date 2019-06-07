#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto add = [](const int first, const int second) { return first + second; };

TEST_CASE("Adds values"){
    CHECK_EQ(42, add(25, 17));
}

TEST_CASE("Increments using manual partial application"){
    auto increment = [](const int value) { return add(value, 1); };

    CHECK_EQ(43, increment(42));
}

TEST_CASE("Increments using bind"){
    // bind the value 1 to the first parameter of add 
    // _1 is a placeholder for the first parameter of the increment lambda
    auto increment = bind(add, 1, _1); 

    CHECK_EQ(43, increment(42));
}

TEST_CASE("Increments using bind"){
    // bind the value 1 to the second parameter of add
    auto increment = bind(add, _1, 1); 

    CHECK_EQ(43, increment(42));
}

TEST_CASE("Constant using bind"){
    auto number42 = bind(add, 1, 41); 

    CHECK_EQ(42, number42());
}

auto addThree = [](const int first, const int second, const int third){return first + second + third;};

TEST_CASE("Adds three"){
    CHECK_EQ(42, addThree(10, 20, 12));
}

TEST_CASE("Adds two numbers to 10"){
    auto addTwoNumbersTo10 = bind(addThree, 10, _1, _2);

    CHECK_EQ(42, addTwoNumbersTo10(20, 12));
}

TEST_CASE("Adds one number to 10 + 20"){
    auto addTo10Plus20 = bind(addThree, 10, 20, _1);

    CHECK_EQ(42, addTo10Plus20(12));
}

TEST_CASE("Adds 10 to one number, and then to 20"){
    auto addTo10Plus20 = bind(addThree, 10, _1, 20);

    CHECK_EQ(42, addTo10Plus20(12));
}

TEST_CASE("Adds one number to 10, and then to 20"){
    auto addTo10Plus20 = bind(addThree, _1, 10, 20);

    CHECK_EQ(42, addTo10Plus20(12));
}

class AddOperation{
    private:
        int first;
        int second;

    public:
        AddOperation(int first, int second): first(first), second(second){}
        int add() const { return first + second;}
};


TEST_CASE("Bind member method"){
    AddOperation operation(41, 1);
    auto add41And1 = bind(&AddOperation::add, operation); 

    CHECK_EQ(42, add41And1());
}

TEST_CASE("Partial bind member method no arguments"){
    auto add = bind(&AddOperation::add, _1); 

    AddOperation operation(41, 1);
    CHECK_EQ(42, add(operation));
}

class AddToOperation{
    private:
        int first;

    public:
        AddToOperation(int first): first(first) {}
        int addTo(int second){ return first + second;}
};

TEST_CASE("Partial application member method"){
    AddToOperation operation(41);
    auto addTo41 = bind(&AddToOperation::addTo, operation, _1); 

    CHECK_EQ(42, addTo41(1));
}


