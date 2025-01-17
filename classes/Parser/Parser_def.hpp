#ifndef _PARSER_DEF_
#define _PARSER_DEF_

#include "../_include/parsing_include.hpp"

Parser::Parser(const std::string& _input) : tokenizer(_input)
{
    curr_token = this->tokenizer.nextToken();
}
Parser::~Parser()
{
    this->is_possible = true;
    this->is_bool = false;
}

bool Parser::isPossible()
{
    return this->is_possible;
}
bool Parser::isBool()
{
    return this->is_bool;
}
void Parser::resetStaticBools()
{
    this->is_possible = true;
    this->is_bool = false;
}

void Parser::consume()
{
    this->curr_token = this->tokenizer.nextToken();
}

Expression* Parser::parse_exp()
{
    return Parser::parse_or_exp();
}
Expression* Parser::parse_or_exp()
{
    Expression* e1 = this->parse_and_exp();

    if (curr_token.type == Token::OR)
    {
        this->is_bool = true;

        Operand op(curr_token.value);
        this->consume();

        Expression* e2 = this->parse_and_exp();

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_and_exp()
{
    Expression* e1 = this->parse_eq_exp();

    if (curr_token.type == Token::AND)
    {
        this->is_bool = true;

        Operand op(curr_token.value);
        this->consume();

        Expression* e2 = this->parse_eq_exp();

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_eq_exp()
{
    Expression* e1 = this->parse_rel_exp();

    if (curr_token.type == Token::EQ)
    {
        this->is_bool = true;

        Operand op(curr_token.value);
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

    if (curr_token.type == Token::REL)
    {
        this->is_bool = true;

        Operand op(curr_token.value);
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

    if (curr_token.type == Token::ADD)
    {
        Operand op(curr_token.value);
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

    if (curr_token.type == Token::MUL)
    {
        Operand op(curr_token.value);
        this->consume();

        Expression* e2 = this->parse_unary_exp();

        if (e1->isBool() || e1->isBool() || (op.getSymbol() == "/" && e2->evaluate() == 0)) { this->is_possible = false; }

        e1 = new BinaryExpression(e1, op, e2);
    }

    return e1;
}

Expression* Parser::parse_unary_exp()
{
    if (curr_token.type == Token::UNARY)
    {
        Operand op(curr_token.value);
        this->consume();

        Expression* e2 = this->parse_literal();

        std::string symbol = op.getSymbol();

        if (symbol == "-" || symbol == "+")
        {
            if (e2->isBool() || symbol == "-" && e2->evaluate() == 0)
            {
                this->is_possible = false;
            }
        }

        if (symbol == "!") { this->is_bool = true; }

        e2 = new UnaryExpression(e2, op);

        return e2;
    }

    Expression* e1 = this->parse_literal();

    return e1;
}

Expression* Parser::parse_literal()
{
    if (curr_token.type == Token::INT || curr_token.type == Token::BOOL)
    {
        Expression* literal = new Literal(curr_token.value);
        this->consume();

        return literal;
    }
    else if (curr_token.type == Token::LPAREN)
    {
        this->consume(); // l-paren
        Expression* exp = parse_exp();
        this->consume(); // r-paren

        return exp;
    }
    else
    {
        if (curr_token.type == Token::ADD)
        {
            Operand op(curr_token.value);
            this->consume();

            Expression* exp2 = parse_exp();
            Expression* exp = new UnaryExpression(exp2, op);

            return exp;
        }
        if (curr_token.type == Token::UNARY)
        {
            if (curr_token.value == "!")
            {
                this->is_bool = true;

                Operand op(curr_token.value);
                this->consume();

                Expression* exp2 = parse_exp();
                Expression* exp = new UnaryExpression(exp2, op);

                return exp;
            }

            return parse_exp();
        }

        this->is_possible = false;

        Expression* literal = new Literal("false");
        return literal;
    }
}

#endif