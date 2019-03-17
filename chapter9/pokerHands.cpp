#include <iostream>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

template<typename DestinationType>
auto transformAll = [](auto source, auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto allOfCollection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};


/*

   D = ♦
   C = ♣
   H = ♥
   S = ♠
*/

typedef string Card;
typedef vector<Card> Hand;

auto endsWith = [](const std::string& str, const std::string& suffix){
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
};

auto suitOf = [](Card card){
    return card.substr(1);
};

const std::map<char, int> charsToCardValues = {
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14},
};

auto valueOf = [](Card card){
    return charsToCardValues.at(card.front());
};

auto toRange = [](auto const collection, int startValue){
    vector<int> range(collection.size());
    iota(begin(range), end(range), startValue);
    return range;
};

auto areValuesConsecutive = [](const vector<int> allValuesInOrder){
    vector<int> consecutiveValues = toRange(allValuesInOrder, allValuesInOrder.front());

    return consecutiveValues == allValuesInOrder;
};

auto isSuitEqual = [](auto value, auto suitToCompareTo){
    return value == suitToCompareTo;
};

auto isSameSuit = [](vector<string> allSuits){
    auto sameSuit = bind(isSuitEqual, _1, allSuits.front()); 
    return allOfCollection(allSuits, sameSuit);
};

auto has5Cards = [](Hand hand){
    return hand.size() == 5;
};

auto allValuesInOrder = [](Hand hand){
    auto theValues = transformAll<vector<int>>(hand, valueOf);
    sort(theValues.begin(), theValues.end());
    return theValues;
};

auto allSuits = [](Hand hand){
    return transformAll<vector<string>>(hand, suitOf);
};

auto isStraightFlush = [](Hand hand){
    return has5Cards(hand) && 
        isSameSuit(allSuits(hand)) && 
        areValuesConsecutive(allValuesInOrder(hand));
};

auto comparePokerHands = [](Hand aliceHand, Hand bobHand){
    if(isStraightFlush(bobHand) && isStraightFlush(aliceHand)){
        return "Alice wins with straight flush";
    }

    if(isStraightFlush(bobHand)) {
        return "Bob wins with straight flush";
    }

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

    SUBCASE("3 based straight flush"){
        bobHand = {"3♣", "4♣", "5♣", "6♣", "7♣"};
    };

    SUBCASE("10 based straight flush"){
        bobHand = {"T♣", "J♣", "Q♣", "K♣", "A♣"};
    };

    CAPTURE(bobHand);

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Bob wins with straight flush", result);
}

/*
Case: Alice wins with higher straight flush

Inputs:
    Alice: 3♠, 4♠, 5♠, 6♠, 7♠
    Bob: 2♣, 3♣, 4♣, 5♣, 6♣

Output:
    Alice wins with straight flush
*/

TEST_CASE("Alice and Bob have straight flushes but Alice wins with higher straight flush"){
    Hand aliceHand;
    Hand bobHand{"2♣", "3♣", "4♣", "5♣", "6♣"};

    SUBCASE("3 based straight flush"){
        aliceHand = {"3♠", "4♠", "5♠", "6♠", "7♠"};
    };

    CAPTURE(aliceHand);

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Alice wins with straight flush", result);
}

TEST_CASE("Hand is straight flush"){
    Hand hand;

    SUBCASE("2 based straight flush"){
        hand = {"2♣", "3♣", "4♣", "5♣", "6♣"};
    };

    SUBCASE("3 based straight flush"){
        hand = {"3♣", "4♣", "5♣", "6♣", "7♣"};
    };

    SUBCASE("4 based straight flush"){
        hand = {"4♣", "5♣", "6♣", "7♣", "8♣"};
    };

    SUBCASE("4 based straight flush on hearts"){
        hand = {"4♥", "5♥", "6♥", "7♥", "8♥"};
    };

    SUBCASE("4 based straight flush on hearts"){
        hand = {"T♥", "J♥", "Q♥", "K♥", "A♥"};
    };


    CAPTURE(hand);

    CHECK(isStraightFlush(hand));
}

TEST_CASE("Hand is not straight flush"){
    Hand hand;

    SUBCASE("Would be straight flush except for one card from another suit"){
        hand = {"2♣", "3♣", "4♣", "5♣", "6♠"};
    };

    SUBCASE("Would be straight flush except not enough cards"){
        hand = {"2♣", "3♣", "4♣", "5♣"};
    };

    SUBCASE("Would be straight flush except too many cards"){
        hand = {"2♣", "3♣", "4♣", "5♣", "6♠", "7♠"};
    };

    SUBCASE("Empty hand"){
        hand = {};
    };

    CAPTURE(hand);

    CHECK(!isStraightFlush(hand));
}
