
#include "calculator.h"
#include "iostream"

using namespace std;

int test(const string &expression, double expectedResult) {
    CalculatorLA calculatorLa = CalculatorLA();
    calculatorLa.nextString(expression);
    double result = calculatorLa.calculate();
    cout << ((result == expectedResult) ? "success" : "fail")
         << " to calc [" << expression << " = " << expectedResult << "].\t";
    if (result != expectedResult) {
        cout << "actual result is: [" << result << "]";
    }
    cout << endl;

    return 0;
}


int main() {
    cout << "tests start: \n";
    test("1+2*3", 7);
    test("1+2*3+1", 8);
    test("1+2*(3+1)", 9);
    test("2^3", 8);
}
