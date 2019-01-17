#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

typedef vector<char> Line;
typedef vector<Line> Board;

template<typename DestinationType>
auto transformAll = [](auto source,  auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto accumulateAll = [](auto source, auto lambda){
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), lambda);
};

auto allOfCollection = [](auto collection, auto lambda){
    return all_of(collection.begin(), collection.end(), lambda);
};

auto lineToString = [](const auto line){
    return transformAll<string>(line, [](auto const token) -> char { return token;});
};

auto boardToLinesString = [](const auto board){
    return transformAll<vector<string>>(board, [](Line line) { return lineToString(line); });
};

auto boardToString = [](const auto board){
    auto linesAsString = boardToLinesString(board);
    return accumulateAll(linesAsString, 
            [](string current, string lineAsString) { return current + lineAsString + "\n"; }
    );
};

auto concatenate = [](auto first, const auto second){
    auto result(first);
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto concatenate3 = [](auto first, auto const second, auto const third){
    return concatenate(concatenate(first, second), third);
};

auto toRange = [](auto const collection){
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto identical = [](const auto value){return value;};

auto all_lines = [](const auto board) {
    return transformAll<Board>(board, identical); 
};

auto column = [](const auto board, const int index){
    auto range = toRange(board);
    return transformAll<Line>(range, [&](auto i) { return board[i][index]; });
};

auto mainDiagonal = [](const auto board){
    auto range = toRange(board);
    return transformAll<Line>(range, [&](auto index){ return board[index][index];});
};

auto secondaryDiagonal = [](const auto board){
    auto range = toRange(board);
    return transformAll<Line>(range, [board](auto index){ return board[index][board.size() - index - 1];});
};

auto all_columns = [](const Board& board) {
    auto range = toRange(board); 
    auto columnForBoardAndIndex = bind(column, board, _1);
    return transformAll<Board>(range, columnForBoardAndIndex);
};

auto all_diagonals = [] (const auto board){
    return vector<Line>( {mainDiagonal(board), secondaryDiagonal(board)});
};

template<typename SourceType, typename DestinationType>
auto applyAllLambdasToValue = [](auto lambdas, auto value){
    return transformAll<DestinationType>(lambdas, [value](auto lambda){ return lambda(value); } );
};

auto allLinesColumnsAndDiagonals = [](const auto board){
    typedef vector<Line> Lines;
    typedef function<Lines(Board)> BoardProjection;
    typedef vector<BoardProjection> BoardProjections;

    BoardProjections boardProjections = {all_lines, all_columns, all_diagonals};

    auto boardProjectionsResult = applyAllLambdasToValue<BoardProjections, vector<Lines>>(boardProjections, board);
    return accumulateAll(boardProjectionsResult, concatenate);
};

auto lineFilledWith = [](auto const line, auto const tokenToCheck){
    return allOfCollection(line, [&tokenToCheck](auto const token){ return token == tokenToCheck;});
};

auto lineFilledWithX = bind(lineFilledWith, _1, 'X'); 
auto lineFilledWithO = bind(lineFilledWith, _1, 'O');

auto xWins = [](auto const board){
    auto all = allLinesColumnsAndDiagonals(board);
    return any_of(all.begin(), all.end(), [](auto line){ return lineFilledWithX(line);});
};

TEST_CASE("all lines"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK_EQ(board, all_lines(board));
}

TEST_CASE("all columns"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Board expectedColumns = {
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
    };

    CHECK_EQ(expectedColumns, all_columns(board));
}

TEST_CASE("all diagonals"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Board expectedDiagonals = {
        {'X', 'O', 'O'},
        {'X', 'O', ' '}
    };

    CHECK_EQ(expectedDiagonals, all_diagonals(board));
}

TEST_CASE("all lines, columns and diagonals"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Board expected = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
        {'X', 'O', 'O'},
        {'X', 'O', ' '}
    };

    auto all = allLinesColumnsAndDiagonals(board);
    CHECK_EQ(expected, all);
}

TEST_CASE("line to string"){
    Line line = {
        ' ', 'X', 'O'
    };

    CHECK_EQ(" XO", lineToString(line));
}

TEST_CASE("board to lines string"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };
    vector<string> expected = {
        "XXX",
        " O ",
        "  O"
    };

    CHECK_EQ(expected, boardToLinesString(board));
}

TEST_CASE("board to string"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };
    string expected = "XXX\n O \n  O\n";

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Line filled with X"){
    Line line = {'X', 'X', 'X'};

    CHECK(lineFilledWithX(line));
}

TEST_CASE("Line not filled with X"){
    CHECK(!lineFilledWithX(Line({'X', 'O', 'X'})));
    CHECK(!lineFilledWithX(Line({'X', ' ', 'X'})));
}

TEST_CASE("X wins"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK(xWins(board));
}

TEST_CASE("Project column"){
    Board board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expected0 = {'X', ' ', ' '};
    CHECK_EQ(expected0, column(board, 0));
    Line expected1 = {'X', 'O', ' '};
    CHECK_EQ(expected1, column(board, 1));
    Line expected2 = {'X', ' ', 'O'};
    CHECK_EQ(expected2, column(board, 2));
}
