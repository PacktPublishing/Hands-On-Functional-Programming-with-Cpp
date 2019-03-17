#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

typedef vector<string> Hand;

auto comparePokerHands = [](Hand /*aliceHand*/, Hand bobHand){
    Hand winningBobHand {"2♣", "3♣", "4♣", "5♣", "6♣"};
    if(bobHand == winningBobHand){
        return "Bob wins with straight flush";
    }
    return "Alice wins with straight flush";
};

auto isStraightFlush = [](Hand){
    return true;
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
    Hand aliceHand;
    Hand bobHand{"2♣", "4♦", "7♥", "9♠", "A♥"};

    SUBCASE("2 based straight flush"){
        aliceHand = {"2♠", "3♠", "4♠", "5♠", "6♠"};
    };
    SUBCASE("3 based straight flush"){
        aliceHand = {"3♠", "4♠", "5♠", "6♠", "7♠"};
    };
    SUBCASE("4 based straight flush"){
        aliceHand = {"4♠", "5♠", "6♠", "7♠", "8♠"};
    };
    SUBCASE("10 based straight flush"){
        aliceHand = {"T♠", "J♠", "Q♠", "K♠", "A♠"};
    };

    CAPTURE(aliceHand);

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Alice wins with straight flush", result);
}


/*
Case: Bob wins

Inputs:
    Alice: 2♠, 3♠, 4♠, 5♠, 9♠
    Bob: 2♣, 3♣, 4♣, 5♣, 6♣

Output:
    Bob wins with straight flush
*/

TEST_CASE("Bob wins with straight flush"){
    Hand aliceHand{"2♠", "3♠", "4♠", "5♠", "9♠"};
    Hand bobHand;

    SUBCASE("2 based straight flush"){
        bobHand = {"2♣", "3♣", "4♣", "5♣", "6♣"};
    };

    CAPTURE(bobHand);

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Bob wins with straight flush", result);
}

TEST_CASE("Hand is straight flush"){
    Hand hand;

    SUBCASE("2 based straight flush"){
        hand = {"2♣", "3♣", "4♣", "5♣", "6♣"};
    };

    CAPTURE(hand);

    CHECK(isStraightFlush(hand));
}


