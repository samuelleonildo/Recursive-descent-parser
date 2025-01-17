#ifndef _TOKEN_DEF_
#define _TOKEN_DEF_

#include "../../_include/parsing_include.hpp"

Token::Token(const std::string& _value, Token::Type _type)
{
    this->value = _value;
    this->type = _type;
}

#endif