#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

typedef vector<char> Line;
typedef vector<Line> Board;

template<typename SourceType, typename DestinationType = SourceType>
auto transformAll = [](SourceType source,  auto lambda){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), lambda);
    return result;
};

auto lineToString = [](const auto line){
    return transformAll<Line, string>(line, [](auto token) -> char { return token;});
};

auto boardToLinesString = [](const auto board){
    return transformAll<Board, vector<string>>(board, [](Line line) { return lineToString(line); });
};

auto boardToString = [](auto const board){
    auto linesAsString = boardToLinesString(board);
    return accumulate(linesAsString.begin(), linesAsString.end(), string(), 
            [](string current, string lineAsString) { return current + lineAsString + "\n"; }
    );
};

auto concatenate = [](auto first, auto const second){
    first.insert(first.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return first;
};

auto toRange = [](auto const board){
    vector<int> range(board.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto identical = [](auto const value){return value;};

auto all_lines = [](const auto board) {
    return transformAll<Board>(board, identical); 
};

auto column = [](const auto board, int index){
    auto range = toRange(board);
    return transformAll<vector<int>, Line>(range, [&](auto i) { return board[i][index]; });
};

auto mainDiagonal = [](const auto board){
    Line diagonal;
    auto range = toRange(board);
    return transformAll<vector<int>, Line>(range, [&](auto index){ return board[index][index];});
};

auto secondaryDiagonal = [](const auto board){
    Line diagonal;
    auto range = toRange(board);
    return transformAll<vector<int>, Line>(range, [&](auto index){ return board[index][board.size() - index - 1];});
};

auto all_columns = [](const Board& board) {
    Board result;
    auto range = toRange(board); 
    auto columnForBoardAndIndex = bind(column, board, _1);
    return transformAll<vector<int>, Board>(range, columnForBoardAndIndex);
};

auto all_diagonals = [] (auto const board){
    return vector<Line>( {mainDiagonal(board), secondaryDiagonal(board)});
};

auto allLinesColumnsAndDiagonals = [](auto const board){
    Board all;
    all = concatenate(all, all_lines(board));
    all = concatenate(all, all_columns(board));
    all = concatenate(all, all_diagonals(board));
    return all;
};

auto lineFilledWithX = [](auto const line){
    return all_of(line.begin(), line.end(), [](auto token){ return token == 'X';});
};

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
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<vector<char>> expectedDiagonals = {
        {'X', 'O', 'O'},
        {'X', 'O', ' '}
    };

    CHECK_EQ(expectedDiagonals, all_diagonals(board));
}

TEST_CASE("all lines, columns and diagonals"){
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<vector<char>> expected = {
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
    vector<char> line = {
        ' ', 'X', 'O'
    };

    CHECK_EQ(" XO", lineToString(line));
}

TEST_CASE("board to lines string"){
    vector<vector<char>> board = {
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
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };
    string expected = "XXX\n O \n  O\n";

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Line filled with X"){
    vector<char> line = {'X', 'X', 'X'};

    CHECK(lineFilledWithX(line));
}

TEST_CASE("X wins"){
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK(xWins(board));
}

TEST_CASE("Project column"){
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<char> expected0 = {'X', ' ', ' '};
    CHECK_EQ(expected0, column(board, 0));
    vector<char> expected1 = {'X', 'O', ' '};
    CHECK_EQ(expected1, column(board, 1));
    vector<char> expected2 = {'X', ' ', 'O'};
    CHECK_EQ(expected2, column(board, 2));
}
