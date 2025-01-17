#ifndef _TOKENIZER_
#define _TOKENIZER_

#include "../../_include/parsing_include.hpp"

class Tokenizer
{
private:
    std::string input = "";
    int index = 0;

    char peek();
    char get();
    void skipWhiteSpace();

public:
    explicit Tokenizer(const std::string& _input);
    // Tokenizer& operator=(const std::string& _input);
    Token nextToken();
};

#endif