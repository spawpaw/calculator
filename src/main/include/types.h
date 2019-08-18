//
// Created by C9D0B1BC on 2019/8/16.
//

#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

// 当前词法分析器所处的状态
enum CalculatorState {
    START, //  初始状态
    DISPATCH_STATE, // 用于决定下一个要进入的状态
    PARSE_NUMBER,//解析数字
    PARSE_OPERATOR // 解析运算符
};
/**
 * 语法树节点的类型
 * ordinal越高，则优先级越高
 */
enum NodeType {
    OP_START,//         标记，op
    OP_PLUS,//       +
    OP_SUBTRACT,//   -
    OP_MULTIPLY,//   *
    OP_DIVIDE,//     /
    OP_POW,//        ^
    OP_MODE,//       %
    OP_NEGATIVE,//   -  负号，单目
    OP_PERM,//       !  全排列，单目
    OP_END,//           标记，op
    OP_L_BRACKET,//  (
    OP_R_BRACKET,//  )
    OP_LR_BRACKET,// ()
    NUMBER,// 数字, 没有子节点
};

//语法树节点
struct Node {
    NodeType type;
    double value; // op节点没有value
    Node *parent; // 父节点
    Node *lChild; // 子节点1
    Node *rChild; // 子节点2，当op为单目运算符此节点为NULL
    Node(NodeType type = NUMBER, double value = 0, Node *parent = nullptr, Node *child1 = nullptr,
         Node *child2 = nullptr)
            : type(type), value(value), parent(parent), lChild(child1), rChild(child2) {}

};

enum Codes {
    OK,
    ERR_ILLEGAL_STATE,
    ERR_NOT_IMPLEMENTED,
};

#endif //CALCULATOR_TYPES_H
