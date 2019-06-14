#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "functional"
#include <list>

using namespace std;
using namespace std::placeholders;

enum Result {
    XWins,
    OWins,
    GameNotOverYet,
    Draw
};

enum Token {
    X,
    O,
    Blank
};

using Line = vector<Token>;

class Board{
    private: 
        const vector<Line> _board;

    public: 
        Board() : _board{Line(3, Token::Blank), Line(3, Token::Blank), Line(3, Token::Blank)}{}
        Board(const vector<Line>& initial) : _board{initial}{}

        bool notFilledYet() const {
            for(int i = 0; i < 3; ++i){
                for(int j = 0; j < 3; ++j){
                    if(_board[i][j] == Token::Blank) return true;
                }
            }
            return false;
        }

        bool anyLineFilledWith(const Token& token) const{
            for(int i = 0; i < 3; ++i){
                if(_board[i][0] == token && _board[i][1] == token && _board[i][2] == token){
                    return true;
                }
            }
            return false;
        };

        bool anyColumnFilledWith(const Token& token) const{
            for(int i = 0; i < 3; ++i){
                if(_board[0][i] == token && _board[1][i] == token && _board[2][i] == token){
                    return true;
                }
            }
            return false;
        };

        bool mainDiagonalFilledWith(const Token& token) const {
            return (_board[0][0] == token && _board[1][1] == token && _board[2][2] == token);
        }

        bool secondaryDiagonalFilledWith(const Token& token) const {
            return (_board[0][2] == token && _board[1][1] == token && _board[2][0] == token);
        }

        bool anyDiagonalFilledWith(const Token& token) const {
            return mainDiagonalFilledWith(token) || secondaryDiagonalFilledWith(token);
        };
};

Result winner_typical(const Board& board){ 
    if(board.anyLineFilledWith(Token::X) || board.anyColumnFilledWith(Token::X) || board.anyDiagonalFilledWith(Token::X)) 
        return XWins; 

    if(board.anyLineFilledWith(Token::O) || board.anyColumnFilledWith(Token::O) || board.anyDiagonalFilledWith(Token::O)) 
        return OWins; 

    if(board.notFilledYet()) 
        return GameNotOverYet; 

    return Draw; 
}

TEST_CASE("Empty board"){
    const Board board;

    CHECK(!board.anyLineFilledWith(Token::X));
    CHECK(!board.anyLineFilledWith(Token::O));
    CHECK(board.anyLineFilledWith(Token::Blank));

    CHECK(!board.anyColumnFilledWith(Token::X));
    CHECK(!board.anyColumnFilledWith(Token::O));
    CHECK(board.anyColumnFilledWith(Token::Blank));

    CHECK(!board.anyDiagonalFilledWith(Token::X));
    CHECK(!board.anyDiagonalFilledWith(Token::O));
    CHECK(board.anyDiagonalFilledWith(Token::Blank));

    CHECK(board.notFilledYet());
}

TEST_CASE("X wins on board"){
    const Board board{{
        Line{Token::X, Token::X, Token::X},
        Line{Token::O, Token::Blank, Token::O},
        Line{Token::Blank, Token::Blank, Token::Blank}
    }};

    CHECK(board.anyLineFilledWith(Token::X));
    CHECK(!board.anyLineFilledWith(Token::O));
    CHECK(board.anyLineFilledWith(Token::Blank));

    CHECK(!board.anyColumnFilledWith(Token::X));
    CHECK(!board.anyColumnFilledWith(Token::O));
    CHECK(!board.anyColumnFilledWith(Token::Blank));

    CHECK(!board.anyDiagonalFilledWith(Token::X));
    CHECK(!board.anyDiagonalFilledWith(Token::O));
    CHECK(!board.anyDiagonalFilledWith(Token::Blank));

    CHECK(board.notFilledYet());

    CHECK(winner_typical(board) == Result::XWins);
}

auto tokenWins = [](const auto board, const auto& token){
    return board.anyLineFilledWith(token) || board.anyColumnFilledWith(token) || board.anyDiagonalFilledWith(token);
};

auto xWins = bind(tokenWins, _1, Token::X);
auto oWins = bind(tokenWins, _1, Token::O);

auto gameNotOverYet = [](const auto& board){
    return board.notFilledYet();
};

Result winner_functionsNoParams(const Board& board){ 
    auto gameNotOverYetOnBoard = bind(gameNotOverYet, board);
    auto xWinsOnBoard = bind(xWins, board);
    auto oWinsOnBoard = bind(oWins, board);

    if(xWinsOnBoard()) 
        return XWins; 

    if(oWinsOnBoard())
        return OWins; 

    if(gameNotOverYetOnBoard()) 
        return GameNotOverYet; 

    return Draw; 
}

auto True = [](){
    return true;
};

using Rule = pair<function<bool()>, Result>;

auto condition = [](const auto& rule){
    return rule.first();
};

auto result = [](const auto& rule){
    return rule.second;
};

// assumes that a rule is always found
auto findTheRule = [](const auto& rules){
    return *find_if(rules.begin(), rules.end(), [](const auto& rule){
            return condition(rule);
            });
};

auto resultForFirstRuleThatApplies = [](const auto& rules){
    return result(findTheRule(rules));
};

Result winner(const Board& board){
    auto gameNotOverYetOnBoard = bind(gameNotOverYet, board);
    auto xWinsOnBoard = bind(xWins, board);
    auto oWinsOnBoard = bind(oWins, board);

    vector<Rule> rules{
        {xWinsOnBoard, XWins},
        {oWinsOnBoard, OWins},
        {gameNotOverYetOnBoard, GameNotOverYet},
        {True, Draw}
    };

    // theRule will always be found, the {True, Draw} by default.
    return resultForFirstRuleThatApplies(rules);
}
