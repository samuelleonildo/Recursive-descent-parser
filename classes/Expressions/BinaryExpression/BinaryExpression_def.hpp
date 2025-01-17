#ifndef _BIN_EXPRESSION_DEF_
#define _BIN_EXPRESSION_DEF_

#include "../../_include/parsing_include.hpp"

BinaryExpression::BinaryExpression(Expression* _left, Operand _op, Expression* _right) : op(_op)
{
    this->left = _left;
    this->right = _right;

    std::string symbol = this->op.getSymbol();

    if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/") { this->primitive_type = "int"; }
    else { this->primitive_type = "bool"; }
}
BinaryExpression::~BinaryExpression()
{
    delete this->left;
    delete this->right;
}

std::string& BinaryExpression::getPrimitiveType() { return this->primitive_type; }

int BinaryExpression::evaluate()
{
    int left_val = this->left->evaluate();
    int right_val = this->right->evaluate();
    std::string symbol = this->op.getSymbol();

    if (symbol == "||") { return left_val || right_val; }
    if (symbol == "&&") { return left_val && right_val; }
    if (symbol == "==") { return left_val == right_val; }
    if (symbol == "!=") { return left_val != right_val; }
    if (symbol == "<") { return left_val < right_val; }
    if (symbol == ">") { return left_val > right_val; }
    if (symbol == "<=") { return left_val <= right_val; }
    if (symbol == ">=") { return left_val >= right_val; }
    if (symbol == "+") { return left_val + right_val; }
    if (symbol == "-") { return left_val - right_val; }
    if (symbol == "*") { return left_val * right_val; }
    if (symbol == "/") { return left_val / right_val; }

    // should not reach here
    return left_val + right_val;
}

#endif