#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> values = {324, 454, 12, 45, 54564, 32};
    sort(values.begin(), values.end());
    
    for(auto it = values.begin();  it<values.end(); ++it){
        cout << *it << ", ";
    }
}
