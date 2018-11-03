#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


int sumWithUsualLoop(const vector<int>& numbers){
    int sum = 0;
    for(auto iterator = numbers.begin(); iterator < numbers.end(); ++iterator){
        sum += *iterator;
    }
    return sum;
}

struct Sums{
    Sums(): evenSum(0),  oddSum(0), total(0){}
    Sums(const int& even, const int& odd, const int& total): evenSum(even), oddSum(odd), total(total){}

    int evenSum;
    int oddSum;
    int total;
};

const Sums sums(const vector<int>& numbers){
    Sums theTotals;
    for(auto iterator = numbers.begin(); iterator<numbers.end(); ++iterator){
        int number = *iterator;
        if(number % 2 == 0) theTotals.evenSum += number;
        if(number %2 != 0) theTotals.oddSum += number;
        theTotals.total += number;
    }
    return theTotals;
}

const bool isEven(const int& value){
    return value %2 == 0;
}

const bool isOdd(const int& value){
    return value %2 != 0;
}

template<class UnaryPredicate>
const vector<int> filter(const vector<int>& input, UnaryPredicate filterFunction){
    vector<int> filtered;
    copy_if(input.begin(), input.end(), back_inserter(filtered), filterFunction);
    return filtered;
}

const int sum(const vector<int>& input){
    return accumulate(input.begin(), input.end(), 0);
}

const Sums sumsWithFunctionalLoopsSimplified(const vector<int>& numbers){
    Sums theTotals(
        sum(filter(numbers, isEven)),
        sum(filter(numbers, isOdd)),
        sum(numbers)
        );

    return theTotals;
}

const Sums sumsWithFunctionalLoops(const vector<int>& numbers){
    Sums theTotals;
    vector<int> evenNumbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evenNumbers), isEven);
    theTotals.evenSum = accumulate(evenNumbers.begin(), evenNumbers.end(), 0);

    vector<int> oddNumbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(oddNumbers), isOdd);
    theTotals.oddSum= accumulate(oddNumbers.begin(), oddNumbers.end(), 0);

    theTotals.total = accumulate(numbers.begin(), numbers.end(), 0);

    return theTotals;
}

int sumOfEvenNumbersWithUsualLoop(const vector<int>& numbers){
    int sum = 0;
    for(auto iterator = numbers.begin(); iterator<numbers.end(); ++iterator){
        int number = *iterator;
        if (number % 2 == 0) sum+= number;
    }
    return sum;
}

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    cout << sumWithUsualLoop(numbers) << endl;

    cout << sumOfEvenNumbersWithUsualLoop(numbers) << endl;

    Sums theTotals = sums(numbers);

    cout << theTotals.oddSum << ", " << theTotals.evenSum << ", " << theTotals.total << endl;

    Sums totals = sumsWithFunctionalLoops(numbers);
    cout << totals.oddSum << ", " << totals.evenSum << ", " << totals.total << endl;

    totals = sumsWithFunctionalLoopsSimplified(numbers);
    cout << totals.oddSum << ", " << totals.evenSum << ", " << totals.total << endl;
}

