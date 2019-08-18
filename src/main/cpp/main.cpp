//
// Created by C9D0B1BC on 2019/8/16.
//

#include <calculator.h>
#include "string"
#include "iostream"

using namespace std;

int main(int argc, char *argv[]) {
    CalculatorLA calculatorLa = CalculatorLA();
    string s;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            s += argv[i];
        }
    } else {
        cout << "please input your expression(e.g: 1+2*(1+9)/5):";
        cin >> s;
    }
    calculatorLa.nextString(s);
    double result = calculatorLa.calculate();
    cout << result << endl;
    return 0;
}
