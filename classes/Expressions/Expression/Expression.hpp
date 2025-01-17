#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "../../_include/parsing_include.hpp"

class Expression
{
protected:
    std::string primitive_type = "";

public:
    virtual ~Expression() = default;
    virtual std::string& getPrimitiveType() = 0;
    virtual int evaluate() = 0;
};

#endif