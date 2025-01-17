#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "../../_include/parsing_include.hpp"

class Expression
{
protected:
    std::string primitive_type = "";

public:
    virtual ~Expression() = default;
    virtual int evaluate() = 0;
    virtual bool isBool() = 0;
};

#endif