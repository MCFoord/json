#include <iostream>
#include "lexer.hpp"
#include "inputhandler.hpp"

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        return EXIT_FAILURE;
    }
    std::cout << argv[1] << '\n';

    File_input_handler input_handler = File_input_handler(argv[1]);
    Input_handler* handler = &input_handler;

    Lexer lexer = Lexer(handler);
    lexer.full_token_scan();
    return EXIT_SUCCESS;
}