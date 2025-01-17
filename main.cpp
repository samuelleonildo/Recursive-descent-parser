#include "./classes/_include/parsing_include.hpp"

int main(void)
{
    try
    {
        int c = 0;
        std::cin >> c;
        std::cin.ignore();

        std::string* input_arr = new std::string[c];

        for (int i = 0; i < c; i++) { std::getline(std::cin, input_arr[i]); }
        for (int i = 0; i < c; i++) 
        {
            Parser parser(input_arr[i]);
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

        delete[] input_arr;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}