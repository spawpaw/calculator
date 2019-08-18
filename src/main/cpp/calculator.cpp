#include <calculator.h>
#include <cmath>
#include <utility>
#include "string"
#include "queue"
#include "set"
#include "iostream"
#include "utils.h"

using namespace std;

CalculatorLA::CalculatorLA() {
    this->init();
}

void CalculatorLA::init() {

}

void CalculatorLA::analyze() {
    for (; currentIndex < expression.length(); ++currentIndex) {
        int numResult = 0;
        logd("state:" << currentState << endl)
        switch (currentState) {
            case DISPATCH_STATE:
                //分发状态
                if (prevState == START || prevState == PARSE_OPERATOR)
                    currentState = PARSE_NUMBER;
                else if (prevState == PARSE_OPERATOR) {
                    for (char opIndex : operators) {
                        if (expression[currentIndex] == opIndex) {
                            currentState = PARSE_OPERATOR;
                        }
                    }
                    currentState = PARSE_NUMBER;
                    logd("error" << endl);
                } else {
                    currentState = PARSE_OPERATOR;
                }
                currentIndex--;
                break;
            case PARSE_NUMBER:
                // 解析数字
                // 计划解析数字格式：
                // -- 带正负号的数字
                // -- 小数
                // -- 八进制 01234567
                // -- 16进制 0x0123456789ABCDEF
                // -- 科学计数 1e10

                if (expression[currentIndex] == '-' || expression[currentIndex] == '+') {
                    // todo 正负号判断
                    logd("error: not support +-" << endl);
                }
                while (currentIndex < expression.length()
                       && expression[currentIndex] >= '0'
                       && expression[currentIndex] <= '9') {
                    numResult *= 10;
                    numResult += expression[currentIndex] - '0';
                    char ch = expression[currentIndex];
                    currentIndex++;
                }

                pushNode(new Node(NUMBER, numResult));
                prevState = PARSE_NUMBER;
                currentState = DISPATCH_STATE;
                currentIndex--;
                break;
            case PARSE_OPERATOR:
                switch (expression[currentIndex]) {
                    case '+':
                        pushNode(new Node(OP_PLUS));
                        break;
                    case '-':
                        pushNode(new Node(OP_SUBTRACT));
                        break;
                    case '*':
                        pushNode(new Node(OP_MULTIPLY));
                        break;
                    case '/':
                        pushNode(new Node(OP_DIVIDE));
                        break;
                    case '^':
                        pushNode(new Node(OP_POW));
                        break;
                    case '%':
                        pushNode(new Node(OP_MODE));
                        break;
                    case '(':
                        pushNode(new Node(OP_L_BRACKET));
                        break;
                    case ')':
                        pushNode(new Node(OP_R_BRACKET));
                        break;
                    default:
                        logd("error: unsupported op " << expression[currentIndex] << endl);
                        break;
                }
                prevState = PARSE_OPERATOR;
                currentState = DISPATCH_STATE;
                break;
            default:
                logd("unhandled state" << endl);
                break;
        }
    }
    this->printGrammarTree();
}

double CalculatorLA::calculate(bool ignoreErrors) {
    analyze();
    return calculateTraversal(root);
}

void CalculatorLA::nextString(string expr) {
    init();
    this->expression = std::move(expr);
}


int CalculatorLA::pushNode(Node *node) {
    logd("push node:" << node->value << endl)
    Node *p;
    switch (node->type) {
        case NUMBER:
            if (currentTail->type == OP_NEGATIVE || currentTail->type == OP_PERM) {
                //单目运算符

                if (currentTail->lChild != nullptr) {
                    logd("error: illegal state:1" << endl);
                    return ERR_ILLEGAL_STATE;
                }
                currentTail->lChild = node;
                node->parent = currentTail;
            } else if (currentTail->type > OP_START && currentTail->type < OP_END) {
                //双目运算符

                if (currentTail->rChild != nullptr) {
                    logd("error: illegal state:2" << endl);
                    return ERR_ILLEGAL_STATE;
                }
                currentTail->rChild = node;
                node->parent = currentTail;
            } else {
                logd("error: illegal state:3" << endl);
                return ERR_ILLEGAL_STATE;
            }
            //树结构不发生变化
            break;
        case OP_PERM:
        case OP_PLUS:
        case OP_SUBTRACT:
        case OP_NEGATIVE:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_POW:
        case OP_MODE:
            if (node->type >= currentTail->type) {
                //如果新的运算符优先级更高
                //以当前最右运算符节点的右节点为支点进行左旋

                node->parent = currentTail;
                node->lChild = currentTail->rChild;
                currentTail->rChild = node;
                currentTail = node;
            } else {
                //否则以当前最右运算符节点为支点进行左旋

                // 最右节点为根节点时特殊处理
                if (currentTail == root) {
                    root = node;
                }
                node->parent = currentTail->parent;
                node->lChild = currentTail;
                currentTail->parent->rChild = node;
                currentTail->parent = node;
                currentTail = node;
            }
            break;
        case OP_L_BRACKET:
            //如果当前节点是有第二操作数的节点,或是左括号
            switch (currentTail->type) {
                case OP_PLUS:
                case OP_SUBTRACT:
                case OP_MULTIPLY:
                case OP_DIVIDE:
                case OP_POW:
                case OP_MODE:
                case OP_L_BRACKET:
                    if (currentTail->rChild != nullptr) {
                        loge("illegal state, number before `(`" << endl)
                        loge(currentTail->type << endl)
                        loge(currentTail->rChild->type << endl)
                    }
                    Node *plusNode;
                    plusNode = new Node(OP_PLUS, 0, node);
                    plusNode->lChild = new Node(NUMBER, 0, plusNode);

                    node->rChild = plusNode;

                    currentTail->rChild = node;
                    node->parent = currentTail;
                    currentTail = plusNode;
                    break;
                default:
                    loge("xxx")
                    break;
            }
            break;
        case OP_R_BRACKET:
            //回溯到上一个左括号
            p = currentTail;
            while (p != nullptr && p->type != OP_L_BRACKET) {
                p = p->parent;
            }
            if (p == nullptr) {
                loge("`)` before `(`" << endl)
            } else {
                p->type = OP_LR_BRACKET;
                currentTail = p->parent;
            }
            break;
        case OP_LR_BRACKET:
            logd("error: temporally not support brackets." << endl);
            return ERR_NOT_IMPLEMENTED;
        default:
            logd("error, not supported node type!" << endl)
            break;
    }
    return 0;
}

void CalculatorLA::printGrammarTree() {
    logd("lrd traversal:[" << expression << "]:\t");
    lrdTraversal(root);
    logd(endl);
}

void CalculatorLA::lrdTraversal(Node *node) {
    if (node == nullptr) {
        return;
    }
    lrdTraversal(node->lChild);
    lrdTraversal(node->rChild);
    string type;
    switch (node->type) {
        case OP_START:
            type = "START ";
            break;
        case OP_PLUS:
            type = "+ ";
            break;
        case OP_SUBTRACT:
            type = "- ";
            break;
        case OP_MULTIPLY:
            type = "* ";
            break;
        case OP_DIVIDE:
            type = "/ ";
            break;
        case OP_POW:
            type = "^ ";
            break;
        case OP_MODE:
            type = "% ";
            break;
        case OP_NEGATIVE:
            type = "--";
            break;
        case OP_PERM:
            type = "! ";
            break;
        case OP_END:
            type = "END ";
            break;
        case OP_L_BRACKET:
            type = "( ";
            break;
        case OP_R_BRACKET:
            type = ") ";
            break;
        case OP_LR_BRACKET:
            type = "()";
            break;
        case NUMBER:
            type = "NU";
            break;
    }
    if (node->type == NUMBER) {
        logd(node->value);
    } else {
        logd(type);
    }
    logd(",");
//    logd("[" << type << "," << node->value << "]");
}

double CalculatorLA::calculateTraversal(Node *node) {
    if (node == nullptr)
        return 0;
    double result = 0;
    double lValue = calculateTraversal(node->lChild);
    double rValue = calculateTraversal(node->rChild);
    switch (node->type) {
        case NUMBER:
            result = node->value;
            break;
        case OP_START:
            logd("error: illegal state: OP_START");
            break;
        case OP_PLUS:
            result = lValue + rValue;
            break;
        case OP_SUBTRACT:
            result = lValue - rValue;
            break;
        case OP_MULTIPLY:
            result = lValue * rValue;
            break;
        case OP_DIVIDE:
            result = lValue / rValue;
            break;
        case OP_POW:
            result = pow(lValue, rValue);
            break;
        case OP_MODE:
            result = (int) lValue % (int) rValue;
            break;
        case OP_NEGATIVE:
            result = -lValue;
            break;
        case OP_L_BRACKET:
            result = lValue + rValue;
            logd("error: illegal state: OP_L_BRACKET" << endl);
            break;
        case OP_R_BRACKET:
            result = lValue + rValue;
            logd("error: illegal state: OP_R_BRACKET" << endl);
            break;
        case OP_LR_BRACKET:
            result = lValue + rValue;
            break;
        case OP_PERM:
            logd("error: not supported op" << endl);
            break;
        case OP_END:
            logd("error: illegal state: OP_END" << endl);
            break;
    }
    return result;
}

