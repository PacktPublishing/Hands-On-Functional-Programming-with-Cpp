#include <iostream>
using namespace std;

class Add{
    private:
        int aMember;

    public: 
        Add(int initialValue): aMember(initialValue){}

        int getDataMember() const {return aMember;}

        int add(const int& first, const int& second) const{
            return first + second;
        }

        int uglyAdd(int& first, int& second){
            first = first + second;
            aMember = 40;
            return first;
        }
};


int main(){
    Add value(42);
    
    int first = 10;
    int second = 20;
 
    cout << "==== add ===" << endl;
    cout << value.add(10, 20) << endl;
    cout << value.getDataMember() << endl;
    cout << first << endl;
    cout << "------------" << endl;

    cout << "==== uglyAdd ===" << endl;
    cout << value.uglyAdd(first, second) << endl;
    cout << value.getDataMember() << endl;
    cout << first << endl;
    cout << "------------" << endl;
}
