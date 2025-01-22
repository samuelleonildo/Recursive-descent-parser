#ifndef _TOKEN_
#define _TOKEN_

#include "../../_include/parsing_include.hpp"

class Token
{
public:
    // attributes
    enum Type {
        INT, // 0
        BOOL, // 1
        LPAREN, // 2 (
        RPAREN, // 3 )

        OR, // 4 ||
        AND, // 5 &&
        EQ, // 6 ==, !=
        REL, // 7 <, >, <=, >=
        ADD, // 8 +, -
        MUL, // 9 *, /
        UNARY, // 10 -, !
        END // 11 '\0'
    };
    Type type;
    std::string value;

    // constructors
    Token() : type(Token::BOOL), value("") {}
    explicit Token(const std::string& _value, Type _type);
};

#endif