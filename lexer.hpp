#ifndef LEXER
#define LEXER

#include <vector>
#include <istream>
#include <string>
#include <queue>
#include "inputhandler.hpp"

class Lexer
{
    public:
        enum token_type
        {
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

        enum number_state
        {
            STATE_INITIAL,
            STATE_MINUS,
            STATE_ZERO,
            STATE_DIGIT_NUMBER,
            STATE_DIGIT_FRACTION,
            STATE_DIGIT_EXPONENT,
            STATE_MANTISSA,
            STATE_E,
            STATE_PLUS_MINUS,
            STATE_FINAL,
            STATE_ERROR
        };

        Lexer(Input_handler* input);
        token_type next_token();
        void skip_whitespace();
        char next_char();
        token_type string_token();
        token_type number_token();
        token_type literal_token(std::string literal, token_type token);
        void token_buffer_add(char c);

        number_state number_state_initial();
        number_state number_state_minus();
        number_state number_state_zero();
        number_state number_state_digit_number();
        number_state number_state_digit_fraction();
        number_state number_state_digit_exponent();
        number_state number_state_mantissa();
        number_state number_state_plus_minus();
        number_state number_state_e();
        
        //for testing, and running a full file without parsing
        void full_token_scan();
        std::string debug_token_name_string(token_type token);
        std::string debug_token_value_string(token_type token);

    private:
        Input_handler* input;
        int32_t line_character_pos;
        int32_t line_count;
        char current_char;
        std::string token_buffer;
        bool current_char_unprocessed;
        std::queue<std::string> token_values;
        
};

#endif //LEXER