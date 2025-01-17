#ifndef _BIN_EXPRESSION_
#define _BIN_EXPRESSION_

#include "../../_include/parsing_include.hpp"

class BinaryExpression : public Expression
{
private:
    Expression* left = nullptr;
    Operand op;
    Expression* right = nullptr;

public:
    explicit BinaryExpression(Expression* _left, Operand _op, Expression* _right);
    ~BinaryExpression();

    bool isBool() override;
    int evaluate() override;
};

#endif