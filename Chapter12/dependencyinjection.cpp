#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto readFromFileAndAddTwoNumbers = [](){
    int first;
    int second;
    ifstream numbersFile("numbers.txt");
    numbersFile >> first;
    numbersFile >> second;
    numbersFile.close();
    return first + second;
};

TEST_CASE("Reads from file"){
    CHECK_EQ(30, readFromFileAndAddTwoNumbers());
}

auto readFromConsoleAndAddTwoNumbers = [](){
    int first;
    int second;
    cout << "Input first number: ";
    cin >> first;
    cout << "Input second number: ";
    cin >> second;
    return first + second;
};

TEST_CASE("Reads from console"){
//    CHECK_EQ(30, readFromConsoleAndAddTwoNumbers());
}

auto readAndAddTwoNumbers = [](auto firstNumberReader, auto secondNumberReader){
    int first = firstNumberReader();
    int second = secondNumberReader();
    return first + second;
};

auto readFirstFromFile = [](){
    int number;
    ifstream numbersFile("numbers.txt");
    numbersFile >> number;
    numbersFile.close();
    return number;
};

auto readSecondFromFile = [](){
    int number;
    ifstream numbersFile("numbers.txt");
    numbersFile >> number;
    numbersFile >> number;
    numbersFile.close();
    return number;
};

auto readFirstFromConsole = [](){
    int number;
    cout << "Input first number: ";
    cin >> number;
    return number;
};
 
auto readSecondFromConsole = [](){
    int number;
    cout << "Input second number: ";
    cin >> number;
    return number;
};
 
TEST_CASE("Reads using dependency injection and adds two numbers"){
    CHECK_EQ(30, readAndAddTwoNumbers(readFirstFromFile, readSecondFromFile));
//    CHECK_EQ(30, readAndAddTwoNumbers(readFirstFromConsole, readSecondFromConsole));
//    CHECK_EQ(30, readAndAddTwoNumbers(readFirstFromFile, readSecondFromConsole));
}
