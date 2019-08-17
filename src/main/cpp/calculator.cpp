#include <calculator.h>
#include "string"
#include "queue"
#include "set"
#include "iostream"

using namespace std;

CalculatorLA::CalculatorLA() {
    this->init();
}

void CalculatorLA::init() {

}

void CalculatorLA::analyze() {
    for (; currentIndex < expression.length(); ++currentIndex) {
        int numResult = 0;
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
                    cout << "error" << endl;
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
                    cout << "error: not support +-" << endl;
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
                        cout << "error: unsupported op " << expression[currentIndex] << endl;
                        break;
                }
                prevState = PARSE_OPERATOR;
                currentState = DISPATCH_STATE;
                break;
            default:
                cout << "unhandled state" << endl;
                break;
        }
    }
    this->printLATree();
}

double CalculatorLA::calculate(bool ignoreErrors) {
    analyze();
    return 0;
}

void CalculatorLA::nextString(string expr) {
    init();
    this->expression = expr;
}


int CalculatorLA::pushNode(Node *node) {
    switch (node->type) {
        case NUMBER:
            if (currentTail->type == OP_NEGATIVE || currentTail->type == OP_PERM) {
                //单目运算符

                if (currentTail->lChild != nullptr) {
                    cout << "error: illegal state:" << endl;
                    return ERR_ILLEGAL_STATE;
                }
                currentTail->lChild = node;
                node->parent = currentTail;
            } else if (currentTail->type > OP_START && currentTail->type < OP_END) {
                //双目运算符

                if (currentTail->rChild != nullptr) {
                    cout << "error: illegal state:" << endl;
                    return ERR_ILLEGAL_STATE;
                }
                currentTail->rChild = node;
                node->parent = currentTail;
            } else {
                cout << "error: illegal state:" << endl;
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
                currentTail->parent = node;
                currentTail = node;
            }
            break;
        case OP_L_BRACKET:
        case OP_R_BRACKET:
            //回溯到上一个左括号
        case OP_LR_BRACKET:
            cout << "error: temporally not support brackets." << endl;
            return ERR_NOT_IMPLEMENTED;
        default:
            cout << "error, not supported node type!" << endl;
    }
    return 0;
}

void CalculatorLA::printLATree() {
    cout << endl << "lrd traversal:[" << expression << "]" << endl;
    lrdTraversal(root);
    cout << endl;
}

void CalculatorLA::lrdTraversal(Node *node) {
    if (node == nullptr) {
        return;
    }
    lrdTraversal(node->lChild);
    lrdTraversal(node->rChild);
    string type = "";
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
        cout << node->value;
    } else {
        cout << type;
    }
    cout << ",";
//    cout << "[" << type << "," << node->value << "]";
}

