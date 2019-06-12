#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Lines = vector<Line>;

template<typename DestinationType>
auto transformAll = [](const auto& source, const auto fn){
    DestinationType result;
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto toRange = [](const auto& collection){
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto concatenate = [](const auto& first, const auto& second){
    auto result(first);
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto concatenate3 = [](const auto& first, const auto& second, const auto& third){
    return concatenate(concatenate(first, second), third);
};

using Coordinate = pair<int, int>;

auto accessAtCoordinates = [](const auto& board, const Coordinate& coordinate){
    return board[coordinate.first][coordinate.second];
};

auto mainDiagonalCoordinates = [](const auto& board){
    auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [](const auto index){return make_pair(index, index);});
};

auto secondaryDiagonalCoordinates = [](const auto& board){
    auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [board](const auto index){return make_pair(index, board.size() - index - 1);});
};

auto columnCoordinates = [](const auto& board, const auto& columnIndex){
    auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [columnIndex](const auto index){return make_pair(index, columnIndex);});
};

auto lineCoordinates = [](const auto board, auto lineIndex){
    auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [lineIndex](const auto index){return make_pair(lineIndex, index);});
};

auto projectCoordinates = [](const auto& board, const auto& coordinates){
    auto boardElementFromCoordinates = bind(accessAtCoordinates, board, _1);
    return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

class BoardResult{
    private:
        const vector<Line> board;

    public:
        BoardResult(vector<Line> board) : board{board}{
        };

        Lines allLinesColumnsAndDiagonals() const {
            return concatenate3(allLines(), allColumns(), allDiagonals());
        }

        Line mainDiagonal() const {
            return projectCoordinates(board, mainDiagonalCoordinates(board));
        }

        Line secondaryDiagonal() const{
            return projectCoordinates(board, secondaryDiagonalCoordinates(board));
        }

        Line column(const int columnIndex) const {
            return projectCoordinates(board, columnCoordinates(board, columnIndex));
        }

        Line line(const int lineIndex) const {
            return projectCoordinates(board, lineCoordinates(board, lineIndex));
        }

        Lines allLines() const {
            auto range = toRange(board);
            return transformAll<Lines>(range, [this](auto index) { 
                    return line(index);
                    });
        }

        Lines allColumns() const {
            auto range = toRange(board);
            return transformAll<Lines>(range, [this](auto index) { 
                    return column(index);
                    });
        }

        Lines allDiagonals() const{
            return {mainDiagonal(), secondaryDiagonal()};
        }
};

auto all_of_collection = [](const auto& collection, const auto& fn){
    return all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto& collection, const auto& fn){
    return any_of(collection.begin(), collection.end(), fn);
};

template<typename SourceType, typename DestinationType>
auto applyAllLambdasToValue = [](const auto& fns, const auto& value){
    return transformAll<DestinationType>(fns, [value](const auto& fn){ return fn(value); } );
};

auto lineFilledWith = [](const auto& line, const auto& tokenToCheck){
    return all_of_collection(line, [&tokenToCheck](const auto& token){ return token == tokenToCheck;});
};

template <typename CollectionBooleanOperation, typename CollectionProvider, typename Predicate>
auto booleanOperationOnProvidedCollection(CollectionBooleanOperation collectionBooleanOperation, CollectionProvider collectionProvider, Predicate predicate){
    return [=](const auto& collectionProviderSeed, const auto& predicateFirstParameter){
        return collectionBooleanOperation(collectionProvider(collectionProviderSeed), 
                bind(predicate, _1, predicateFirstParameter));
    };
}

//auto tokenWins = booleanOperationOnProvidedCollection(any_of_collection, allLinesColumnsAndDiagonals, lineFilledWith);
//auto xWins = bind(tokenWins, _1, 'X');
//auto oWins = bind(tokenWins, _1, 'O');

auto noneOf = [](const auto& collection, const auto& fn){
    return none_of(collection.begin(), collection.end(), fn);
};

auto isEmpty = [](const auto& token){return token == ' ';};

auto isNotEmpty= [](const auto& token){return token != ' ';};

auto fullLine = bind(all_of_collection, _1, isNotEmpty);

auto full = [](const auto& board){
    return all_of_collection(board, fullLine);
};

//auto draw = [](auto const board){
//    return full(board) && !xWins(board) && !oWins(board); 
//};

//auto inProgress = [](auto const board){
//    return !full(board) && !xWins(board) && !oWins(board); 
//};

auto findInCollection = [](const auto& collection, const auto& fn){
    auto result = find_if(collection.begin(), collection.end(), fn);
    return (result == collection.end()) ? nullopt : optional(*result);
};

auto findInCollectionWithDefault = [](const auto& collection, const auto& defaultResult, const auto& fn){
    auto result = findInCollection(collection, fn);
    return result.has_value() ? (*result) : defaultResult;
}; 

TEST_CASE("lines"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Line expectedLine0 = {'X', 'X', 'X'};
    CHECK_EQ(expectedLine0, boardResult.line(0));
    Line expectedLine1 = {' ', 'O', ' '};
    CHECK_EQ(expectedLine1, boardResult.line(1));
    Line expectedLine2 = {' ', ' ', 'O'};
    CHECK_EQ(expectedLine2, boardResult.line(2));
}

TEST_CASE("all columns"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Line expectedColumn0{'X', ' ', ' '};
    CHECK_EQ(expectedColumn0, boardResult.column(0));
    Line expectedColumn1{'X', 'O', ' '};
    CHECK_EQ(expectedColumn1, boardResult.column(1));
    Line expectedColumn2{'X', ' ', 'O'};
    CHECK_EQ(expectedColumn2, boardResult.column(2));
}

TEST_CASE("main diagonal"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Line expectedDiagonal{'X', 'O', 'O'};

    CHECK_EQ(expectedDiagonal, boardResult.mainDiagonal());
}

TEST_CASE("secondary diagonal"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Line expectedDiagonal{'X', 'O', ' '};

    CHECK_EQ(expectedDiagonal, boardResult.secondaryDiagonal());
}


TEST_CASE("all lines, columns and diagonals"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Lines expected{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
        {'X', 'O', 'O'},
        {'X', 'O', ' '}
    };

    auto all = boardResult.allLinesColumnsAndDiagonals();
    CHECK_EQ(expected, all);
}

/*
TEST_CASE("X wins"){
    Board board {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK(xWins(board));
}

TEST_CASE("O wins"){
    Board board {
        {'X', 'O', 'X'},
        {' ', 'O', ' '},
        {' ', 'O', 'X'}
    };

    CHECK(oWins(board));
}

TEST_CASE("draw"){
    Board board {
        {'X', 'O', 'X'},
        {'O', 'O', 'X'},
        {'X', 'X', 'O'}
    };

    CHECK(draw(board));
}

TEST_CASE("in progress"){
    Board board {
        {'X', 'O', 'X'},
        {'O', ' ', 'X'},
        {'X', 'X', 'O'}
    };

    CHECK(inProgress(board));
}
*/

TEST_CASE("Project column"){
    BoardResult boardResult{{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    }};

    Line expected0 {'X', ' ', ' '};
    CHECK_EQ(expected0, boardResult.column(0));
    Line expected1 {'X', 'O', ' '};
    CHECK_EQ(expected1, boardResult.column(1));
    Line expected2 {'X', ' ', 'O'};
    CHECK_EQ(expected2, boardResult.column(2));
}

TEST_CASE("Range"){
    vector<vector<char>> collection{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<int> expected {0, 1, 2};
    CHECK_EQ(expected, toRange(collection));
    CHECK_EQ(expected, toRange(collection[0]));
}
