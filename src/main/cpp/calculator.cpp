#include <calculator.h>
#include "string"

using namespace std;

CalculatorLA::CalculatorLA() {

}

string CalculatorLA::nextChar(char ch) {
    string result;
    switch (state) {
        case PARSE_NUMBER_SYMBOL:
            if (ch == '-') {

            } else if (ch == '+') {

            }
            break;
        case PARSE_NUMBER_INTEGER:

            break;
        default:
            result = "";
            break;
    }
    return result;
}

double CalculatorLA::parseNumber(string str) {

    return 0;
}

double CalculatorLA::calculate(bool ignoreErrors) {
    return 0;
}

double CalculatorLA::parse(string expression) {
    init();
}

void CalculatorLA::init() {

}
