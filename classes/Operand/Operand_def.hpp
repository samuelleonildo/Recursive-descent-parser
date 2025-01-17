#ifndef _OPERAND_DEF_
#define _OPERAND_DEF_

#include "../_include/parsing_include.hpp"

Operand::Operand(const std::string& _symbol)
{
    this->symbol = _symbol;
}

const std::string& Operand::getSymbol()
{
    return this->symbol;
}

#endif