#include <iostream>
#include <sstream>
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

        static int* incrementPointerAddressImpure(int* pValue){ return pValue++; }
        static int incrementPointerValueImpure(int* pValue ){ return *pValue++; }

        static int* incrementPointerAddressNoSideEffect(int* const& pValue){ return pValue + 1; }

        static int* incrementPointerAddressAndValue(int* const& pValue){ (*pValue)++; return pValue + 1; }

        static const int* incrementPointerAddressAndValuePure(const int* const& pValue){ return pValue + 1; }
};

int Number::aMember = 34;

int one(){return 1;}

const int* incrementPointerAddressAndValuePure(const int* const& pValue){
    return pValue + 1;
}

void printResults(){
    int* pValue = new int(10);
    cout << "Address: " << pValue << endl;
    cout << "Increment pointer address and value pure:" << incrementPointerAddressAndValuePure(pValue) << endl;
    cout << "Address after increment: " << pValue << endl;
    cout << "Value after increment: " << *pValue << endl;
    delete pValue;
}

string formatResults(){ 
    stringstream output;
    int* pValue = new int(500);
    output << "Address: " << pValue << endl;
    output << "Increment pointer address and value pure:" << incrementPointerAddressAndValuePure(pValue) << endl;
    output << "Address after increment: " << pValue << endl;
    output << "Value after increment: " << *pValue << endl;
    delete pValue;

    return output.str();
}

string formatResultsPure(const int* pValue){ 
    stringstream output;
    output << "Address: " << pValue << endl;
    output << "Increment pointer address and value pure:" << incrementPointerAddressAndValuePure(pValue) << endl;
    output << "Address after increment: " << pValue << endl;
    output << "Value after increment: " << *pValue << endl;

    return output.str();
}


void printSomething(const string& text){
    cout << text;
}


int main(){
    cout << "Value is: " << Number::zero() << endl;
    
    Number number;
    int output = number.impureIncrement(Number::zero());
    cout << "Impure increment result: " << output << endl;

    cout << "Pure increment result: " << Number::increment(Number::zero()) << endl;

    int value = Number::zero();
    cout << "Impure increment with value change: " << Number::impureIncrementWithValueChange(value) << endl;
    cout << value << endl;

    cout << "Sum is: " << Number::add(Number::increment(Number::increment(Number::zero())), Number::increment(Number::zero())) << endl;

    cout << "Pure function outside class: " <<  one() << endl;

    int* pValue = new int(10);

    cout << "Address: " << pValue << endl;
    cout << "Increment pointer address:" << Number::incrementPointerAddressImpure(pValue) << endl;
    cout << "Address after increment: " << pValue << endl;

    cout << "Increment pointer value:" << Number::incrementPointerValueImpure(pValue) << endl;

    delete pValue;

    int* pValue2 = new int(10);
    cout << "Address: " << pValue2 << endl;
    cout << "Increment pointer address no side effect:" << Number::incrementPointerAddressNoSideEffect(pValue2) << endl;
    cout << "Address after increment: " << pValue2 << endl;
    delete pValue2;

    int* pValue3 = new int(10);
    cout << "Address: " << pValue3 << endl;
    cout << "Increment pointer address and value no address change:" << Number::incrementPointerAddressAndValue(pValue3) << endl;
    cout << "Address after increment: " << pValue3 << endl;
    cout << "Value after increment: " << *pValue3 << endl;
    delete pValue3;

    int* pValue4 = new int(10);
    cout << "Address: " << pValue4 << endl;
    cout << "Increment pointer address and value pure:" << Number::incrementPointerAddressAndValuePure(pValue4) << endl;
    cout << "Address after increment: " << pValue4 << endl;
    cout << "Value after increment: " << *pValue4 << endl;
    delete pValue4;

    int* pValue5 = new int(10);
    cout << "Address: " << pValue5 << endl;
    cout << "Increment pointer address and value pure:" << incrementPointerAddressAndValuePure(pValue5) << endl;
    cout << "Address after increment: " << pValue5 << endl;
    cout << "Value after increment: " << *pValue5 << endl;
    delete pValue5;

    printResults();

    printSomething(formatResults());

    int* pValue6 = new int(500);
    printSomething(formatResultsPure(pValue6));
    delete pValue6;
}


