#include <iostream>
using namespace std;

class Number{
    private:
        int initialValue;

    public:
        Number(int initialValue) : initialValue(initialValue){}
        int initial() const{ return initialValue; }
        int addToInitial(const int& first) const{ return first + initialValue; }
};

int main(){
    Number number(10);
    cout << number.addToInitial(20) << endl;
}
