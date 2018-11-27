#include <iostream>
#include <vector>

using namespace std;

class Product{
    private:
        string name;
        long double price;

    public:
        Product(const string& name, const long double price) : name(name), price(price){};
};

class ShoppingCart{
    private: 
        vector<Product> products;

    public:
        long double totalWithTax(){return 0L;};
        long double totalWithoutTax(){return 0L;};
};


int main(){
    auto addTax = [](const long double price){return price * 1.18; };
    vector<Product> products = {Product("book", 12.35), Product("ebook", 5.00)};
}
