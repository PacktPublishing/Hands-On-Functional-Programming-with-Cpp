#include <iostream>
using namespace std;

class Number{
    private:
        static int aMember;

    public:
        static int zero(){ aMember++; return 0; } 

        static int increment(const int value){ return value + 1; }

        static int incrementPointer(const int* const value ){ return *value + 1; }

        static int add(const int first, const int second){ return first + second; }

        int impureIncrement(int value){ return ++value; } const

        static int impureIncrementWithValueChange(int& value){ return ++value; }

        static int pureIncrementWithReference(const int& value) {return value + 1; }

};

int Number::aMember = 34;

int one(){return 1;}

int main(){
    cout << Number::zero() << endl;
    
    Number number;
    int output = number.impureIncrement(Number::zero());
    cout << output << endl;

    cout << Number::increment(Number::zero()) << endl;

    int value = Number::zero();
    cout << Number::impureIncrementWithValueChange(value) << endl;
    cout << value << endl;

    cout << "Sum is: " << Number::add(Number::increment(Number::increment(Number::zero())), Number::increment(Number::zero())) << endl;

    cout << one() << endl;
}
