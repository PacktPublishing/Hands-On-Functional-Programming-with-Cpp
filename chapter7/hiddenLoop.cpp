#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "functional"
#include <list>
using namespace std;

enum Result {
    XWins,
    OWins,
    GameNotOverYet,
    Draw
};

class Board{
    public: 
        bool notFilledYet(){
            return true;
        }
};

bool anyLineFilledWith(char token){
    return token != 'x';
};

bool anyColumnFilledWith(char token){
    return token != 'x';
};

bool anyDiagonalFilledWith(char token){
    return token != 'x';
};

Result winner_typical(Board board){ 
    if(anyLineFilledWith('x') || anyColumnFilledWith('x') || anyDiagonalFilledWith('x')) 
        return XWins; 

    if(anyLineFilledWith('0') || anyColumnFilledWith('0') || anyDiagonalFilledWith('0')) 
        return OWins; 

    if(board.notFilledYet()) 
        return GameNotOverYet; 

    return Draw; 
}

auto tokenWins = [](auto token){
    return anyLineFilledWith(token) || anyColumnFilledWith(token) || anyDiagonalFilledWith(token);
};

auto xWins = bind(tokenWins, 'x');
auto oWins = bind(tokenWins, '0');
auto gameNotOverYet = [](auto board){
    return board.notFilledYet();
};

Result winner_functionsNoParams(Board board){ 
    auto gameNotOverYetOnBoard = bind(gameNotOverYet, board);

    if(xWins()) 
        return XWins; 

    if(oWins())
        return OWins; 

    if(gameNotOverYetOnBoard()) 
        return GameNotOverYet; 

    return Draw; 
}

auto True = [](){
    return true;
};

typedef pair<function<bool()>, Result> Rule;

auto condition = [](auto rule){
    return rule.first();
};

auto result = [](auto rule){
    return rule.second;
};

auto findTheRule = [](auto rules){
    return *find_if(rules.begin(), rules.end(), [](auto rule){
            return condition(rule);
            });
};

auto resultForFirstRuleThatApplies = [](auto rules){
    return result(findTheRule(rules));
};

Result winner(Board board){
    auto gameNotOverYetOnBoard = bind(gameNotOverYet, board);
    list<Rule> rules = {
        {xWins, XWins},
        {oWins, OWins},
        {gameNotOverYetOnBoard, GameNotOverYet},
        {True, Draw}
    };

    return resultForFirstRuleThatApplies(rules);
}
