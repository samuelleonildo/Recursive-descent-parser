#ifndef _OPERAND_
#define _OPERAND_

#include "../_include/parsing_include.hpp"

class Operand
{
private:
    std::string symbol = "";

public:
    explicit Operand(const std::string& _symbol);
    const std::string& getSymbol();
};

#endif