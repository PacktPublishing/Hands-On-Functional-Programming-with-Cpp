#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

int createAccount(string accountOwnerName){
    return 1;
}

TEST_CASE("Adds values"){
    string accountOwnerName = "Alex";

    int accountId = createAccount(accountOwnerName);

    CHECK_EQ(1, accountId);
}
