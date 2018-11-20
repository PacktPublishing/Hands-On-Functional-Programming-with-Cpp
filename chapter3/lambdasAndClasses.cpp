#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

class ImaginaryNumber{
    private:
        int real;
        int imaginary;

    public:
        ImaginaryNumber() : real(0), imaginary(0){};
        ImaginaryNumber(int real, int imaginary) : real(real), imaginary(imaginary){};

        string toString(){
            return to_string(real) + " + " + to_string(imaginary) + "i";
        }

        function<string()> toStringLambda = [this](){
            return to_string(real) + " + " + to_string(imaginary) + "i";
        };

        string toStringUsingLambda(){
            auto toStringLambdaLocal = ImaginaryNumber::toStringStatic;
            return toStringLambdaLocal(*this);
        }

    static function<string(const ImaginaryNumber&)> toStringLambdaStatic;

    static string toStringStatic(const ImaginaryNumber& number){
        return to_string(number.real) + " + " + to_string(number.imaginary) + "i";
    };
};

function<string(const ImaginaryNumber&)> ImaginaryNumber::toStringLambdaStatic = [](const ImaginaryNumber& number){
    return to_string(number.real) + " + " + to_string(number.imaginary) + "i";
};

auto toImaginaryString = [](auto real, auto imaginary){
    return to_string(real) + " + " + to_string(imaginary) + "i";
};

int main(){
    ImaginaryNumber imaginaryI(0, 1);
    cout << imaginaryI.toString() << endl;

    ImaginaryNumber real1(1, 0);
    cout << real1.toStringUsingLambda() << endl;

    ImaginaryNumber imaginary11(1, 1);
    cout << ImaginaryNumber::toStringLambdaStatic(imaginary11) << endl;
}
