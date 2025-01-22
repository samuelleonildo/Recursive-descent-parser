#ifndef _PARSER_
#define _PARSER_

#include "../_include/parsing_include.hpp"

class Parser
{
private:
    inline static bool is_possible = true;
    inline static bool is_bool = false;

    int lparen_cnt = 0;
    int rparen_cnt = 0;

    Tokenizer tokenizer;
    Token curr_token;

    void consume();

    Expression* parse_or_exp();
    Expression* parse_and_exp();
    Expression* parse_eq_exp();
    Expression* parse_rel_exp();

    Expression* parse_add_exp();
    Expression* parse_mul_exp();
    Expression* parse_unary_exp();

    Expression* parse_literal();

public:
    explicit Parser(const std::string& _input);
    ~Parser();
    
    Expression* parse_exp();

    bool isPossible();
    bool isBool();

    void increaseParenCnt();
};

#endif