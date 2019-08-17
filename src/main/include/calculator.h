//
// Created by C9D0B1BC on 2019/8/16.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include "string"
#include "types.h"
#include "set"

using namespace std;

class CalculatorLA {
private:
    CalculatorState currentState = DISPATCH_STATE;//当前状态
    CalculatorState prevState = START;//之前的状态
    set<CalculatorState> availableNextState = set<CalculatorState>();

    Node *root = new Node(OP_PLUS,
                          0,
                          nullptr,
                          new Node(NUMBER));//语法树根节点, 初始为0+?
    Node *currentTail = root;//当前的最右运算符节点
    string expression = "";
    unsigned int currentIndex = 0;//当前解析第几个字符
    const string operators = "+-*/()%^!";
protected:
    /**
     * 初始化
     */
    void init();

    /**
     * 向语法树推送节点，
     * - 如果新的节点是运算符:
     * ---- 如果该运算符的优先级比当前节点高，则该运算符节点替换当前节点的右节点，并将原先的右节点变为运算符节点的左节点
     * ---- 如果该运算符的优先级和当前节点相同或者比当前节点低，则将当前节点变为该运算符节点的左节点
     * - 如果新的节点是数值:
     * ---- 如果当前节点是单目运算符，则将该数值节点插入当前节点的左子树
     * ---- 如果当前节点是双目运算符，则将该数值节点插入当前节点的右子树，如果右子树不为空，则报错
     * *当前节点指当前语法树最右侧的运算符节点
     * 括号进行特殊处理
     * @return 成功0，其他:出现错误
     */
    int pushNode(Node *node);

    /**
     *
     * @return
     */
    double calculateTraversal(Node *node);

    /**
     * 将表达式解析为语法树
     */
    void analyze();

    /**
     * 打印语法树
     */
    void printGrammarTree();

    /**
     * 后续遍历语法树
     */
    static void lrdTraversal(Node *node);

public:
    CalculatorLA();

    /**
     * 一次性解析整个表达式
     * @param expr
     * @return 
     */
    void nextString(string expr);

    /**
     * 计算当前分析出的语法树
     */
    double calculate(bool ignoreErrors = true);
};

#endif //CALCULATOR_CALCULATOR_H
