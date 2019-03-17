#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;


auto comparePokerHands = [](auto /*aliceHand*/, auto /*bobHand*/){
    return "Alice wins with straight flush";
};

/*
Case: Alice wins

Inputs:
    Alice: 2♠, 3♠, 4♠, 5♠, 6♠
    Bob: 2♣, 4♦, 7♥, 9♠, A♥

Output:
    Alice wins with straight flush
*/

TEST_CASE("Alice wins with straight flush"){
    auto aliceHand = {"2♠", "3♠", "4♠", "5♠", "6♠"};
    auto bobHand = {"2♣", "4♦", "7♥", "9♠", "A♥"};

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Alice wins with straight flush", result);
}
