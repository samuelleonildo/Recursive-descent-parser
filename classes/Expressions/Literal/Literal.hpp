#ifndef _LITERAL_
#define _LITERAL_

#include "../../_include/parsing_include.hpp"

class Literal : public Expression
{
private:
    bool is_digit = true;
    std::string value = "int";

public:
    // Literal() : is_digit(true), value("int") {}
    explicit Literal(const std::string& _value);

    bool isBool() override;
    int evaluate() override;
};

#endif