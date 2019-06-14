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

TEST_CASE("Identity function"){
    function<int(int)> identity = [](int value) { return value;};

    CHECK_EQ(1, identity(1));
}

int freeFunctionReturns2(){ return 2; };

TEST_CASE("Free function"){
    function<int()> f = freeFunctionReturns2;

    CHECK_EQ(2, f());
}

class JustAClass{
    public:
        int functionReturns2() const { return 2; };
};

TEST_CASE("Class method"){
    function<int(const JustAClass&)> f = &JustAClass::functionReturns2;
    JustAClass justAClass;

    CHECK_EQ(2, f(justAClass));
}

TEST_CASE("Sort with predefined function"){
    vector<int> values{3, 1, 2, 20, 7, 5, 14};
    vector<int> expectedDescendingOrder{20, 14, 7, 5, 3,  2, 1};

    sort(values.begin(), values.end(), greater<int>());

    CHECK_EQ(expectedDescendingOrder, values);
}

TEST_CASE("Partial application using bind"){
    auto add = [](int first, int second){
        return first + second;
    };

    auto increment = bind(add, _1, 1);

    CHECK_EQ(3, add(1, 2));
    CHECK_EQ(3, increment(2));
}
