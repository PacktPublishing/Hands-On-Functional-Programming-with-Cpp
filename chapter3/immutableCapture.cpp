#include <iostream>
#include <utility>

using namespace std;

void captureByReference(){
    cout << "Capture value by reference" << endl;
    int value = 1;
    auto increment = [&](){return ++value;};

    cout << "Value before: " << value << endl;
    cout << "Result of increment:" << increment() << endl;
    cout << "Value after: " << value << endl;
    cout << endl;
}

void captureByReferenceImmutable(){
    cout << "Capture value by reference immutable" << endl;
    int value = 1;
    auto increment = [&immutableValue = as_const(value)](){return immutableValue + 1;};

    cout << "Value before: " << value << endl;
    cout << "Result of increment:" << increment() << endl;
    cout << "Value after: " << value << endl;
    cout << endl;
}

void capturePointerAddressByValue(){
    cout << "Capture pointer address by value" << endl;
    int* pValue = new int(1);
    auto incrementAddress = [=](){return pValue + 1;};

    cout << "Address before: " << pValue << endl;
    cout << "Result of increment:" << incrementAddress() << endl;
    cout << "Address after: " << pValue << endl;

    delete pValue;
    cout << endl;
}

void capturePointerAddressByReference(){
    cout << "Capture pointer address by reference" << endl;
    int* pValue = new int(1);
    int* initial = pValue;
    auto increment = [&](){return ++pValue;};

    cout << "Address before: " << pValue << endl;
    cout << "Result of increment:" << increment() << endl;
    cout << "Address after: " << pValue << endl;

    delete initial;
    cout << endl;
}

void capturePointerByValue(){
    cout << "Capture pointer by value" << endl;
    int* pValue = new int(1);
    auto increment= [=](){return ++(*pValue);};

    cout << "Value before: " << *pValue << endl;
    cout << "Result of increment:" << increment() << endl;
    cout << "Value after: " << *pValue << endl;

    delete pValue;
    cout << endl;
}

void capturePointerByReference(){
    cout << "Capture pointer by reference" << endl;
    int* pValue = new int(1);
    auto increment= [&](){return (*pValue) ++;};

    cout << "Value before: " << *pValue << endl;
    cout << "Result of increment:" << increment() << endl;
    cout << "Value after: " << *pValue << endl;

    delete pValue;
    cout << endl;
}


int main(){
    captureByReference();
    captureByReferenceImmutable();
    capturePointerAddressByValue();
    capturePointerAddressByReference();
    capturePointerByValue();
    capturePointerByReference();
}


