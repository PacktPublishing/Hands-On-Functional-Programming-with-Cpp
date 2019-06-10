#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

template<typename ValueType>
struct State{
    const ValueType value;
    const function<ValueType(const ValueType)> computeNext;

    State<ValueType> nextState() const{
        return State<ValueType>{computeNext(value), computeNext};
    };
};

auto increment = [](const int current){
    return current + 1;
};

TEST_CASE("Initialize auto increment"){
    const auto autoIncrementIndex = State<int>{1, increment};

    CHECK_EQ(1, autoIncrementIndex.value); 
}

TEST_CASE("Compute next auto increment index"){
    const auto autoIncrementIndex = State<int>{1, increment};

    const auto nextAutoIncrementIndex = autoIncrementIndex.nextState();

    CHECK_EQ(2, nextAutoIncrementIndex.value); 

    const auto newAutoIncrementIndex = nextAutoIncrementIndex.nextState();
    CHECK_EQ(3, newAutoIncrementIndex.value);
}


template<typename ValueType, typename ...Params>
struct StateWithParams{
    const ValueType value;
    const function<ValueType(const ValueType, Params ...params)> computeNext;

    StateWithParams<ValueType, Params...> nextState(Params ...params) const{
        return StateWithParams<ValueType, Params...>{computeNext(value, params...), computeNext};
    };
};


enum Token {Blank, X, O};
typedef vector<vector<Token>> TicTacToeBoard;

const TicTacToeBoard EmptyBoard{
    {Token::Blank,Token::Blank, Token::Blank},
    {Token::Blank,Token::Blank, Token::Blank},
    {Token::Blank,Token::Blank, Token::Blank}
};

struct Move{
    const Token token;
    const int xCoord;
    const int yCoord;
};

auto makeMove = [](const TicTacToeBoard board, const Move move) -> TicTacToeBoard {
    TicTacToeBoard nextBoard(board);
    nextBoard[move.xCoord][move.yCoord] = move.token;
    return nextBoard;
};

TEST_CASE("TicTacToe compute next board after a move"){
    const Move firstMove{Token::X, 0, 0};
    const function<TicTacToeBoard(const TicTacToeBoard)> makeFirstMove = bind(makeMove, _1, firstMove);
    const auto emptyBoardState = State<TicTacToeBoard>{EmptyBoard, makeFirstMove };
    CHECK_EQ(Token::Blank, emptyBoardState.value[0][0]); 

    const auto boardStateAfterFirstMove = emptyBoardState.nextState();
    CHECK_EQ(Token::X, boardStateAfterFirstMove.value[0][0]); 
}

TEST_CASE("TicTacToe compute next board after a move with StateWithParams"){
    const auto emptyBoardState = StateWithParams<TicTacToeBoard, Move>{EmptyBoard, makeMove };
    CHECK_EQ(Token::Blank, emptyBoardState.value[0][0]); 

    const auto boardStateAfterFirstMove = emptyBoardState.nextState(Move{Token::X, 0, 0});
    CHECK_EQ(Token::X, boardStateAfterFirstMove.value[0][0]); 

    const auto boardStateAfterSecondMove = boardStateAfterFirstMove.nextState(Move{Token::O, 1, 1});
    CHECK_EQ(Token::Blank, boardStateAfterFirstMove.value[1][1]); 
    CHECK_EQ(Token::O, boardStateAfterSecondMove.value[1][1]); 
}
