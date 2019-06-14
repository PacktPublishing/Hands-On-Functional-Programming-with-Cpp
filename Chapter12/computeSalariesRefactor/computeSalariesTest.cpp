#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "computeSalaries.h"

using namespace std;

TEST_CASE("Base salary"){
    CHECK_EQ(1500, baseSalaryForPosition("Tester"));
    CHECK_EQ(1600, baseSalaryForPosition("Analyst"));
    CHECK_EQ(2000, baseSalaryForPosition("Developer"));
    CHECK_EQ(3000, baseSalaryForPosition("Team Leader"));
    CHECK_EQ(4000, baseSalaryForPosition("Manager"));
    CHECK_EQ(0, baseSalaryForPosition("asdfasdfs"));
}


