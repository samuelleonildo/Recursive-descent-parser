#ifndef _UN_EXPRESSION_
#define _UN_EXPRESSION_

#include "../../_include/parsing_include.hpp"

class UnaryExpression : public Expression
{
private:
    Expression* exp = nullptr;
    Operand op;

public:
    explicit UnaryExpression(Expression* _exp, Operand _op);
    ~UnaryExpression();

    std::string& getPrimitiveType() override;
    int evaluate() override;
};

#endif