#ifndef _UNARY_EXPRESSION_DEF_
#define _UNARY_EXPRESSION_DEF_

#include "../../_include/parsing_include.hpp"

UnaryExpression::UnaryExpression(Expression* _exp, Operand _op) : op(_op)
{
    this->exp = _exp;

    if (this->op.getSymbol() == "-" || this->op.getSymbol() == "+") { this->primitive_type = "int"; }
    else { this->primitive_type = "bool"; }
}
UnaryExpression::~UnaryExpression()
{
    delete this->exp;
}

bool UnaryExpression::isBool() { return (this->primitive_type == "bool"); }

int UnaryExpression::evaluate()
{
    int exp_val = this->exp->evaluate();
    std::string symbol = this->op.getSymbol();

    if (symbol == "-") { return -exp_val; }
    if (symbol == "!") { return !exp_val; }

    // should not reach here
    return exp_val;
}

#endif