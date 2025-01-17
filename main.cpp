#include "./classes/_include/parsing_include.hpp"

int main(void)
{
    std::string input = "";
    std::cout << "input: ";
    std::getline(std::cin, input);

    try
    {
        Parser parser(input);
        Expression* expression = parser.parse_exp();

        if (parser.isPossible())
        {
            if (parser.isBool())
            {
                expression->evaluate() ? std::cout << "true" : std::cout << "false";
                std::cout << '\n';
            }
            else
            {
                std::cout << expression->evaluate() << '\n';
            }
        }
        else
        {
            std::cout << "error" << '\n';
        }

        delete expression;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}