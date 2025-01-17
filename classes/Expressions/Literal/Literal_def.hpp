#ifndef _LITERAL_DEF_
#define _LITERAL_DEF_

#include "../../_include/parsing_include.hpp"

Literal::Literal(const std::string& _value)
{
    this->value = _value;

    int index = 0;
    while (this->is_digit && index < this->value.size())
    {
        if (!std::isdigit(this->value[index++]))
        {
            this->is_digit = false;
            this->primitive_type = "bool";
        }   
    }
}

bool Literal::isBool() { return (this->primitive_type == "bool"); }

int Literal::evaluate()
{
    if (this->is_digit) { return std::stoi(this->value); }
    if (this->value == "true") { return 1; }

    return 0;
}

#endif