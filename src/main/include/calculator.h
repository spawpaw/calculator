//
// Created by C9D0B1BC on 2019/8/16.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include "string"
#include "../cpp/types.h"
using namespace std;

class CalculatorLA {
private:
    CalculatorState state = START;//当前状态
    Node *root = new Node();//语法树根节点
public:
    CalculatorLA();

    /**
     * 初始化
     */
    void init();

    /**
     * 一次性解析整个表达式
     * @param expression 
     * @return 
     */
    double parse(string expression);

    /**
     * 一个字符一个字符地解析表达式
     * @param ch 字符
     * @return 计算结果
     */
    string nextChar(char ch);

    /**
     *解析数字
     * @param str 数字字符串
     * @return
     */
    double parseNumber(string str);

    double calculate(bool ignoreErrors = true);
};

#endif //CALCULATOR_CALCULATOR_H
