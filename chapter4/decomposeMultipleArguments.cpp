#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <functional>

using namespace std;

auto increment = [](const int value) { return value + 1; };
auto multiply = [](const int first, const int second){ return first * second; };

template <class F1, class G2>
auto compose12(F1 f, G2 g){
    return [=](auto first, auto second){ return f(g(first, second)); };
}

TEST_CASE("Increment result of multiplication"){
    CHECK_EQ(5, compose12(increment, multiply)(2, 2));
}

template <class F2, class G1>
auto compose21(F2 f, G1 g){
    return [=](auto first, auto second){ return f(g(first), g(second)); };
}

TEST_CASE("Multiply two incremented values"){
    CHECK_EQ(9, compose21(multiply, increment)(2, 2));
}

auto multiplyDecomposed = [](const int first) { 
    return [=](const int second){ return first * second; }; 
};

TEST_CASE("using single parameter functions"){
    CHECK_EQ(4, multiplyDecomposed(2)(2));
}

template <class F, class G>
auto compose(F f, G g){
    return [=](auto value){return f(g(value));};
}

TEST_CASE("Increment result of multiplication"){
    auto incrementResultOfMultiplication = compose(increment, multiplyDecomposed(2));
    CHECK_EQ(5, incrementResultOfMultiplication(2));
}

TEST_CASE("Increment result of multiplication final"){
    auto incrementResultOfMultiplication = [](int first, int second) {
        return compose(increment, multiplyDecomposed(first))(second);
    };

    CHECK_EQ(5, incrementResultOfMultiplication(2, 2));
}

TEST_CASE("Multiply incremented values no composition"){
    const int first = 2;
    const int second = 2;
    CHECK_EQ(9, multiplyDecomposed(increment(first))(increment(second)));
}

TEST_CASE("Multiply incremented values some composition"){
    const int first = 2;
    const int second = 2;
    auto partialMultiplyOnIncrementedParameter = compose(multiplyDecomposed, increment);
    CHECK_EQ(9, partialMultiplyOnIncrementedParameter(first)(increment(second)));
}

TEST_CASE("Multiply incremented values some more composition"){
    const int first = 2;
    const int second = 2;
    auto partialMultiplyOnIncrementedParameter = compose(multiplyDecomposed, increment);
    auto multiplyIncrementedValues = compose(partialMultiplyOnIncrementedParameter(first), increment);
    CHECK_EQ(9, multiplyIncrementedValues(second));
}

TEST_CASE("Multiply incremented values two values"){
    auto multiplyIncrementedValues = [](int first) { 
        auto partialMultiplyOnIncrementedParameter = compose(multiplyDecomposed, increment);
        return compose(partialMultiplyOnIncrementedParameter(first), increment); 
    };

    const int first = 2;
    const int second = 2;

    CHECK_EQ(9, multiplyIncrementedValues(first)(second));
}


TEST_CASE("Multiply incremented values two values expanded lambda"){
    auto multiplyIncrementedValues = [](int first) { 
        return compose(
                compose(multiplyDecomposed, increment)(first), 
                increment
                ); 
    };

    const int first = 2;
    const int second = 2;

    CHECK_EQ(9, multiplyIncrementedValues(first)(second));
}


template<class F>
auto combineParameters(F f){
    return [=](auto first, auto second){return f(first)(second);};
}

template<class F>
auto decomposeToOneParameter(F f){
    return [=](auto first){
        return [=](auto second){
            return f(first, second);
        };
    };
}

template<class F, class G>
auto applyToAllParameters(F f, G g){
    return [=](auto first) { 
        return compose(
                compose(f, g)(first), 
                g 
                ); 
    };
};

TEST_CASE("Multiplies using single parameter functions"){
    CHECK_EQ(4, decomposeToOneParameter(multiply)(2)(2));
}

TEST_CASE("Multiplies using recombined parameters"){
    CHECK_EQ(4, combineParameters(decomposeToOneParameter(multiply))(2, 2));
}

TEST_CASE("Increment result of multiplication"){
    auto incrementResultOfMultiplication = [](int first, int second) { 
        return compose(increment, decomposeToOneParameter(multiply)(first))(second);
    };
    int result = incrementResultOfMultiplication(2, 2);
    CHECK_EQ(5, result);
}

TEST_CASE("Multiply incremented values no compose"){
    auto multiplyIncrementedValues = [](int first, int second){
        return multiply(increment(first), increment(second)); 
    };
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}

TEST_CASE("Multiply incremented values decompose"){
    auto multiplyIncrementedValues = [](int first, int second){
        return multiplyDecomposed(increment(first))(increment(second)); 
    };
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}

TEST_CASE("Multiply incremented values compose simple"){
    auto multiplyIncrementedValues = [](int first, int second){
        return compose(multiplyDecomposed, increment)(first)(increment(second)); 
    };

    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}

TEST_CASE("Multiply incremented values decompose first"){
    auto multiplyIncrementedValues = [](int first, int second){
        return compose(
                decomposeToOneParameter(multiply), 
                increment
                )(first)(increment(second)); 
    };
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}

template<class F, class G>
auto composeWithFunctionCallAllParameters(F f, G g){
    return [=](auto first, auto second){
        return compose(
                decomposeToOneParameter(f), 
                g 
                )(first)(g(second)); 
    };
};

TEST_CASE("Multiply incremented values generalized"){
    auto multiplyIncrementedValues = composeWithFunctionCallAllParameters(multiply, increment);
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}


TEST_CASE("Multiply incremented values"){
    auto multiplyIncrementedValues = combineParameters(
            applyToAllParameters(
                decomposeToOneParameter(multiply), 
                increment
                )
            );
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}



template <class F, class G>
auto composeWithTwoParameters(F f, G g){
    return [=](auto first, auto second) { 
        return compose(
                f, 
                decomposeToOneParameter(g)(first)
                )(second);
    };
};


TEST_CASE("Increment result of multiplication"){
    auto incrementResultOfMultiplication = composeWithTwoParameters(increment, multiply);
    int result = incrementResultOfMultiplication(2, 2);
    CHECK_EQ(5, result);
}

template<class F, class G>
auto composeWithBothParameters(F f, G g){
    return combineParameters(
            applyToAllParameters(
                decomposeToOneParameter(f), 
                g 
                )
            );
}


TEST_CASE("Multiply incremented values"){
    auto multiplyIncrementedValues = composeWithBothParameters(multiply, increment);
    int result = multiplyIncrementedValues(2, 2);
    CHECK_EQ(9, result);
}

