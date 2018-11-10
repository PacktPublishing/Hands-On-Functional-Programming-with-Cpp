#include <iostream>
#include <tuple>

using namespace std;

void incrementAll(int& first, int& second){
    ++first;
    ++second;
}

const tuple<int, int> incrementAllPure(const int& first, const int& second){
    return make_tuple(first + 1, second + 1);
}

int main(){
    int first = 1;
    int second = 2;

    incrementAll(first, second);

    cout << "First: " << first << endl;
    cout << "Second: " << second << endl;
    

    auto results = incrementAllPure(1, 2);
    cout << "Incremented pure: " << get<0>(results) << endl;
    cout << "Incremented pure: " << get<1>(results) << endl;
}
