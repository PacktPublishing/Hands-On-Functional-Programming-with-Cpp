#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Name{
    Name(){}
    Name(const string& providedFirstName, const string& providedLastName): firstName(providedFirstName), lastName(providedLastName){
    }
    string firstName;
    string lastName;
};

bool compareByFirstName(const Name& first, const Name& second){
    return first.firstName < second.firstName;
}

int main(){
    vector<Name> names = {Name("John", "Smith"), Name("Alex", "Bolboaca")};

    sort(names.begin(), names.end(), compareByFirstName);

    for(auto iterator = names.begin(); iterator != names.end(); ++iterator){
        cout << iterator->firstName
            << " " << iterator->lastName << ", ";
    }
}

