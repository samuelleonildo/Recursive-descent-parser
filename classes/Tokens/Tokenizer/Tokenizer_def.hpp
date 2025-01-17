#ifndef _TOKENIZER_DEF_
#define _TOKENIZER_DEF_

#include "../../_include/parsing_include.hpp"

Tokenizer::Tokenizer(const std::string& _input)
{
    this->input = _input;
}
// Tokenizer& Tokenizer::operator=(const std::string& _input)
// {
//     this->input = _input;
//     return *this;
// }

char Tokenizer::peek()
{
    if (this->index < input.size()) { return input[this->index]; }
    return '\0';
}

char Tokenizer::get()
{
    if (this->index < input.size()) { return input[this->index++]; }
    return '\0';
}

void Tokenizer::skipWhiteSpace()
{
    while (std::isspace(this->peek())) { this->get(); }
}

Token Tokenizer::nextToken()
{
    skipWhiteSpace();

    char current = this->peek();

    if (std::isdigit(current))
    {
        std::string number = "";
        while (std::isdigit(this->peek())) { number += this->get(); }
        
        return Token(number, Token::INT);
    }

    if (std::isalpha(current))
    {
        std::string identifier = "";
        while (std::isalpha(this->peek())) { identifier += this->get(); }

        return Token(identifier, Token::BOOL);
    }

    skipWhiteSpace();

    switch (this->get())
    {
    case '|':
        if (this->peek() == '|')
        {
            this->get();
            return Token("||", Token::OR);
        }

    case '&':
        if (this->peek() == '&')
        {
            this->get();
            return Token("&&", Token::AND);
        }

    case '=':
        if (this->peek() == '=')
        {
            this->get();
            return Token("==", Token::EQ);
        }

    case '!':
        if (this->peek() == '=')
        { 
            this->get();
            return Token("!=", Token::EQ);
        }
        
        return Token("!", Token::UNARY);

    case '<':
        if (this->peek() == '=')
        {
            this->get();
            return Token("<=", Token::REL);
        }

        return Token("<", Token::REL);

    case '>':
        if (this->peek() == '=')
        {
            this->get();
            return Token(">=", Token::REL);
        }

        return Token(">", Token::REL);

    case '+':
        if (this->peek() == ' ')
        {
            return Token("+", Token::ADD);
        }
        return Token("+", Token::UNARY);

    case '-':
        if (this->peek() == ' ')
        {
            return Token("-", Token::ADD);
        }
        return Token("-", Token::UNARY);

    case '*':
        return Token("*", Token::MUL);

    case '/':
        return Token("/", Token::MUL);

    case '(':
        return Token("(", Token::LPAREN);

    case ')':
        return Token(")", Token::RPAREN);

    case '\0':
        return Token("\0", Token::END);

    default:
        return Token("\0", Token::END);

        break;
    }
}

#endif