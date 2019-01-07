#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto incrementedAccountId = [](int lastCount){
    return lastCount + 1;
};
auto initialAccountId = bind(incrementedAccountId, 0);

auto createAccount = [](string accountOwnerName, auto uniqueAccountId){
    return uniqueAccountId();
};


TEST_CASE("Create account"){
    string accountOwnerName = "Alex";

    int accountId = createAccount(accountOwnerName, initialAccountId);

    CHECK_EQ(1, accountId);
}

TEST_CASE("Create second account"){
    string accountOwnerName = "Alex";

    int firstAccountId = createAccount(accountOwnerName, initialAccountId);
    auto nextAccountId = bind(incrementedAccountId, firstAccountId);
    int accountId = createAccount(accountOwnerName, nextAccountId);

    CHECK_EQ(2, accountId);
}
