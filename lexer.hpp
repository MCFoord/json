#ifndef LEXER
#define LEXER

#include <vector>
#include <istream>
#include "inputhandler.hpp"

class lexer
{
    public:
        enum token_type {
            TOKEN_BEGIN_OBJECT,
            TOKEN_END_OBJECT,
            TOKEN_BEGIN_ARRAY,
            TOKEN_END_ARRAY,
            TOKEN_NAME_SEPARATOR,
            TOKEN_VALUE_SEPARATOR,
            TOKEN_NUMBER,
            TOKEN_STRING,
            TOKEN_TRUE,
            TOKEN_FALSE,
            TOKEN_NULL,
            TOKEN_ERROR,
            TOKEN_EOF
        };

        token_type next_token();
        void skip_whitespace();
        char next_char();
        token_type string_token();
        token_type number_token();
        token_type literal_token(std::string literal, token_type token);
        void token_buffer_add(char c);

        //for testing, and running a full file without parsing
        std::vector<token_type> full_token_scan();

    private:
        input_handler input;
        int32_t line_character_pos;
        int32_t line_count;
        char current_char;
        std::string token_buffer;
};

#endif