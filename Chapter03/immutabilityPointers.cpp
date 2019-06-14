#include <iostream>

using namespace std;

auto incrementAddress = [](int* value) { 
    return ++value;
};

void printResultsForIncrementAddressByValue(){
    cout << "#### Increment Address By Value #### " << endl;
    int* pValue = new int(41);
    cout << "Address before:" << pValue << endl;
    cout << "Address returned by increment address:" <<  incrementAddress(pValue) << endl;
    cout << "Address after increment address:" << pValue << endl;
    delete pValue;
    cout << "#### End Increment Address By Value #### " << endl;
}

auto incrementAddressByReference = [](int*& value) { 
    return ++value;
};

void printResultsForIncrementAddressByReference(){
    cout << "#### Increment Address By Reference #### " << endl;
    int* pValue = new int(41);
    int* initialPointer = pValue;
    cout << "Address before:" << pValue << endl;
    cout << "Address returned by increment address:" <<  incrementAddressByReference(pValue) << endl;
    cout << "Address after increment address:" << pValue << endl;
    delete initialPointer;
    cout << "#### End Increment Address By Reference #### " << endl;
}

auto incrementAddressByReferenceImmutable = [](int* const& value) { 
    return value + 1;
};

void printResultsForIncrementAddressByReferenceImmutable(){
    cout << "#### Increment Address By Reference Immutable #### " << endl;
    int* pValue = new int(41);
    cout << "Address before:" << pValue << endl;
    cout << "Address returned by increment address:" <<  incrementAddressByReferenceImmutable(pValue) << endl;
    cout << "Address after increment address:" << pValue << endl;
    delete pValue;
    cout << "#### End Increment Address By Reference Immutable #### " << endl;
}

auto incrementPointedValueImmutable = [](const int* const& value) { 
    return *value + 1;
};

void printResultsForIncrementPointedValueImmutable(){
    cout << "#### Increment Pointed Value Immutable #### " << endl;
    int* pValue = new int(41);
    cout << "Value before:" << *pValue << endl;
    cout << "Value returned by increment:" <<  incrementPointedValueImmutable(pValue) << endl;
    cout << "Value after increment:" << *pValue << endl;
    delete pValue;
    cout << "#### End Increment Pointed Value Immutable #### " << endl;
}



int main(){
    printResultsForIncrementAddressByValue();
    printResultsForIncrementAddressByReference();
    printResultsForIncrementAddressByReferenceImmutable();
    printResultsForIncrementPointedValueImmutable();
}
