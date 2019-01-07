#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

typedef vector<vector<char>> Board;

auto all_lines = [](auto const board) {
    return board;
};

auto all_columns = [](auto const board) {
    vector<vector<char>> result(board[0].size(), vector<char>(board.size()));
    for (vector<char>::size_type i = 0; i < board[0].size(); i++) 
        for (vector<char>::size_type j = 0; j < board.size(); j++) {
            result[i][j] = board[j][i];
        }
    return result;
};

auto all_diagonals = [] (auto const board){
    vector<vector<char>> result(2, vector<char>(board.size()));

    for(int i = 0; i < board.size(); ++i){
        result[0][i] = board[i][i];
    }

    for(int i = 0; i < board.size(); ++i){
        result[1][i] = board[i][board.size() - i - 1];
    }

    return result;
};

TEST_CASE("all lines"){
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK_EQ(board, all_lines(board));
}

TEST_CASE("all columns"){
    vector<vector<char>> board = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<vector<char>> expectedColumns = {
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
