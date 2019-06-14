#include <iostream>

using namespace std;

int main(){
    auto add = [](int first, int second){ return first + second;};
    cout << add(1,2) << endl; // writes 3

    int first = 5;
    auto addToFirst = [first](int second){return first + second;};

    cout << addToFirst(10) << endl; // writes 15
    
    auto addToFirstByReference = [&first](int second){return first + second;};

    cout << addToFirstByReference(10) << endl; // writes 15

    int second = 6;
    int third = 7;
    int fourth = 8;
    int fifth = 9;

    auto addTheFive = [&first, &second, &third, &fourth, &fifth](){return first + second + third + fourth + fifth;};
    cout << addTheFive() << endl; // writes 35

    auto addTheFiveWithDefaultReferenceCapture = [&](){return first + second + third + fourth + fifth;};
    cout << addTheFiveWithDefaultReferenceCapture() << endl; // writes 35

    auto addTheFiveWithDefaultValueCapture = [=](){return first + second + third + fourth + fifth;};
    cout << addTheFiveWithDefaultValueCapture() << endl; // writes 35

    auto addTheFiveWithDefaultValueCaptureForAllButFirst = [=, &first](){return first + second + third + fourth + fifth;};
    cout << addTheFiveWithDefaultValueCaptureForAllButFirst() << endl; // writes 35

    int* pFirst = new int(5);
    auto addToThePointerValue = [&pFirst](int second){return *pFirst + second;};
    cout << addToThePointerValue(10) << endl; // writes 15
    delete pFirst;
}
