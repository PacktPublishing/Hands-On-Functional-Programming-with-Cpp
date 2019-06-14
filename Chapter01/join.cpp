#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<int> range(const int count){
    vector<int> aVector(count);
    iota(aVector.begin(), aVector.end(), 1);
    return aVector;
}
string concatenate(const int element) { 
    return to_string(element) + ", ";
}


int main() {
    auto myRange = range(10);
    std::stringstream output;
    std::transform( 
            myRange.begin(), 
            myRange.end(),
            ostream_iterator<string>(output),
            concatenate
        );
    cout << output.str() << endl;

    for(auto iter = myRange.begin(); iter != myRange.end(); ++iter){
        cout << *iter << ", ";
    }
}

