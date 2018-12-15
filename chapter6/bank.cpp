#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto createAccount = [](string accountOwnerName,  int lastCount){
    return lastCount + 1;
};

auto createFirstAccount = bind(createAccount, _1, 0);

TEST_CASE("Adds values"){
    string accountOwnerName = "Alex";

    int accountId = createFirstAccount(accountOwnerName);

    CHECK_EQ(1, accountId);
}

TEST_CASE("Adds values"){
    string accountOwnerName = "Alex";

    int firstAccountId = createFirstAccount(accountOwnerName);
    int accountId = createAccount(accountOwnerName, firstAccountId);

    CHECK_EQ(2, accountId);
}
