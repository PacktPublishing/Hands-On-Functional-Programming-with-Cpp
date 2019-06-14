#include <iostream>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

template<typename DestinationType>
auto transformAll = [](const auto& source, const auto& fn){
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto all_of_collection = [](const auto& collection, const auto& fn){
    return all_of(collection.begin(), collection.end(), fn);
};


/*

   D = ♦
   C = ♣
   H = ♥
   S = ♠
*/

using Card = string;
using Hand = vector<Card>;

auto endsWith = [](const std::string& str, const std::string& suffix){
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
};

auto suitOf = [](const Card& card){
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

auto valueOf = [](const Card& card){
    return charsToCardValues.at(card.front());
};

auto toRange = [](const auto& collection, const int startValue){
    vector<int> range(collection.size());
    iota(begin(range), end(range), startValue);
    return range;
};

auto areValuesConsecutive = [](const vector<int>& allValuesInOrder){
    const vector<int> consecutiveValues = toRange(allValuesInOrder, allValuesInOrder.front());

    return consecutiveValues == allValuesInOrder;
};

auto isSameSuit = [](const vector<string>& allSuits){
    return std::equal(allSuits.begin() + 1, allSuits.end(), allSuits.begin());
};

auto has5Cards = [](const Hand& hand){
    return hand.size() == 5;
};

auto allValuesInOrder = [](const Hand& hand){
    auto theValues = transformAll<vector<int>>(hand, valueOf);
    sort(theValues.begin(), theValues.end());
    return theValues;
};

auto allSuits = [](const Hand& hand){
    return transformAll<vector<string>>(hand, suitOf);
};

auto isStraightFlush = [](const Hand& hand){
    return has5Cards(hand) && 
        isSameSuit(allSuits(hand)) && 
        areValuesConsecutive(allValuesInOrder(hand));
};

auto compareStraightFlushes = [](const Hand& first, const Hand& second){
    const int firstHandValue = allValuesInOrder(first).front();
    const int secondHandValue = allValuesInOrder(second).front();
    if(firstHandValue > secondHandValue) return 1;
    if(secondHandValue > firstHandValue) return -1;
    return 0;
};

auto comparePokerHands = [](const Hand& aliceHand, const Hand& bobHand){
    if(isStraightFlush(bobHand) && isStraightFlush(aliceHand)){
        const int whichIsHigher = compareStraightFlushes(aliceHand, bobHand);
        if(whichIsHigher == 1) return "Alice wins with straight flush";
        if(whichIsHigher == -1) return "Bob wins with straight flush";
        return "Draw";
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
    const Hand aliceHand{"2♠", "3♠", "4♠", "5♠", "9♠"};
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

    const auto result = comparePokerHands(aliceHand, bobHand);

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
    const Hand bobHand{"2♣", "3♣", "4♣", "5♣", "6♣"};

    SUBCASE("3 based straight flush"){
        aliceHand = {"3♠", "4♠", "5♠", "6♠", "7♠"};
    };

    CAPTURE(aliceHand);

    const auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Alice wins with straight flush", result);
}

/*
Case: Bob wins with higher straight flush

Inputs:
 Alice: 3♠, 4♠, 5♠, 6♠, 7♠
 Bob: 4♣, 5♣, 6♣, 7♣, 8♣

Output:
 Bob wins with straight flush
*/

TEST_CASE("Alice and Bob have straight flushes but Bob wins with higher straight flush"){
    Hand aliceHand{"3♠", "4♠", "5♠", "6♠", "7♠"};
    Hand bobHand;

    SUBCASE("3 based straight flush"){
        bobHand = {"4♣", "5♣", "6♣", "7♣", "8♣"};
    };

    CAPTURE(bobHand);

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Bob wins with straight flush", result);
}

/*
Case: Draw because equal straight flushes

Inputs:
 Alice: 3♠, 4♠, 5♠, 6♠, 7♠
 Bob: 3♠, 4♠, 5♠, 6♠, 7♠

Output:
 Draw
*/

TEST_CASE("Draw due to equal straight flushes"){
    Hand aliceHand;
    Hand bobHand;

    SUBCASE("3 based straight flush"){
        aliceHand= {"3♠", "4♠", "5♠", "6♠", "7♠"};
    };

    CAPTURE(aliceHand);
    bobHand = aliceHand;

    auto result = comparePokerHands(aliceHand, bobHand);

    CHECK_EQ("Draw", result);
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

    SUBCASE("10 based straight flush on hearts"){
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
