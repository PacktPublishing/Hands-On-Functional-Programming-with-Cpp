#include <iostream>

using namespace std;

auto increment = [](int& value) { 
    return ++value;
};

auto incrementImmutable = [](const int& value){
    return value + 1;
};

int main(){
    int valueToIncrement = 41;
    cout << increment(valueToIncrement) << endl;// prints 42
    cout << valueToIncrement << endl;// prints 42

    valueToIncrement = 41;
    cout << incrementImmutable(valueToIncrement) << endl;// prints 42
    cout << valueToIncrement << endl;// prints 42
}
