//
// Created by C9D0B1BC on 2019/8/16.
//

#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

// 当前词法分析器所处的状态
enum CalculatorState {
    START, //  初始状态
    PARSE_NUMBER_SYMBOL,//解析数字的符号
    PARSE_NUMBER_INTEGER,//解析数字的整数部分
    PARSE_OPERATOR // 解析运算符
};
// 语法树节点的类型
enum NodeType {
    OP_PLUS,//  +
    OP_SUBTRACT,//  -
    OP_NEGATIVE,//  - 负号，单目
    OP_MULTIPLY,//  *
    OP_DIVIDE,//  /
    OP_POW,//     ^
    OP_PERM,//    ! 全排列，单目
    OP_MODE,//    %
    OP_L_BRACKET,//  (
    OP_R_BRACKET,//  )
    OP_LR_BRACKET,//  ( )
    NUMBER,// 数字, 没有子节点
};

//语法树节点
struct Node {
    NodeType type;
    double value;
    Node *child1; // 子节点1
    Node *child2; // 子节点2，单目运算符此节点为NULL
};


#endif //CALCULATOR_TYPES_H
