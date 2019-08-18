
#include "calculator.h"
#include "iostream"
#include "utils.h"

using namespace std;

int test(const string &expression, double expectedResult) {
    CalculatorLA calculatorLa = CalculatorLA();
    calculatorLa.nextString(expression);
    double result = calculatorLa.calculate();
    cout << ((result == expectedResult) ? "success" : "fail")
         << " to calc [" << expression << " = " << expectedResult
         << "].\t";
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
    test("2^3", 8);
    test("4%2", 0);
    test("5%2", 1);
    test("1+10/2", 6);
    test("1+10/2*5+3", 29);
    test("1+10/2*5+3%2", 27);
    test("1+2*(3+1)", 9);
    test("1+2*(3+4)", 15);
    test("1+(3+1)*2+1", 10);
    test("1+2*(3+(2+1)))", 13);
    test("1+2*(3+(2+1)+1))", 15);
    test("1+2*(3+(2+1)))+1", 14);
    test("1+2*(3+(2+1)))+11", 24);
}
