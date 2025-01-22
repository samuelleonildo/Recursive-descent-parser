#ifndef _PARSER_DEF_
#define _PARSER_DEF_

#include "../_include/parsing_include.hpp"

Parser::Parser(const std::string& _input) : tokenizer(_input)
{
    this->curr_token = this->tokenizer.nextToken();
    this->increaseParenCnt();
}
Parser::~Parser()
{
    this->is_possible = true;
    this->is_bool = false;
}

void Parser::increaseParenCnt()
{
    std::string curr_value = this->curr_token.value;

    if (curr_value == "(") { this->lparen_cnt++; }
    else if (curr_value == ")") { this->rparen_cnt++; }
}

bool Parser::isPossible()
{
    return ( this->lparen_cnt == this->rparen_cnt ) ? this->is_possible : false;
}

bool Parser::isBool() { return this->is_bool; }

void Parser::consume()
{
    this->curr_token = this->tokenizer.nextToken();
    this->increaseParenCnt();
}

Expression* Parser::parse_exp()
{
    return this->parse_or_exp();
}
Expression* Parser::parse_or_exp()
{
    Expression* e1 = this->parse_and_exp();

    while (this->curr_token.type == Token::OR)
    {
        this->is_bool = true;

        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_and_exp();

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_and_exp()
{
    Expression* e1 = this->parse_eq_exp();

    while (this->curr_token.type == Token::AND)
    {
        this->is_bool = true;

        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_eq_exp();

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_eq_exp()
{
    Expression* e1 = this->parse_rel_exp();

    while (this->curr_token.type == Token::EQ)
    {
        this->is_bool = true;

        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_rel_exp();

        if (e1->isBool() != e2->isBool()) { this->is_possible = false; }

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_rel_exp()
{
    Expression* e1 = this->parse_add_exp();

    while (this->curr_token.type == Token::REL)
    {
        this->is_bool = true;

        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_add_exp();

        if (e1->isBool() || e2->isBool()) { this->is_possible = false; }

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_add_exp()
{
    Expression* e1 = this->parse_mul_exp();

    while (this->curr_token.type == Token::ADD)
    {
        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_mul_exp();

        if (e1->isBool() || e2->isBool()) { this->is_possible = false; }

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_mul_exp()
{
    Expression* e1 = this->parse_unary_exp();

    while (this->curr_token.type == Token::MUL)
    {
        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_unary_exp();

        if (e1->isBool() || e2->isBool() || (op.getSymbol() == "/" && e2->evaluate() == 0)) { this->is_possible = false; }

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_unary_exp()
{
    if (this->curr_token.type == Token::UNARY || this->curr_token.type == Token::ADD)
    {
        Operand op(this->curr_token.value);
        this->consume();

        Expression* e2 = this->parse_unary_exp();
        std::string symbol = op.getSymbol();

        if ((symbol == "-" || symbol == "+") && e2->isBool()) { this->is_possible = false; }
        if (symbol == "!") { this->is_bool = true; }

        return new UnaryExpression(e2, op);
    }

    return this->parse_literal();
}

Expression* Parser::parse_literal()
{
    if (this->curr_token.type == Token::INT || this->curr_token.type == Token::BOOL)
    {
        Expression* literal = new Literal(this->curr_token.value);
        this->consume();

        return literal;
    }
    else if (this->curr_token.type == Token::LPAREN)
    {
        this->consume(); // l-paren
        Expression* exp = parse_exp();
        this->consume(); // r-paren

        return exp;
    }

    // only syntactically invalid expressions reach here
    // ex: '2 + * 3'
    this->is_possible = false;
    return new Literal("false"); // returning garbage
}

#endif