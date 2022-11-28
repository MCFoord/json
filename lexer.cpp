#include "lexer.hpp"
#include "inputhandler.hpp"
#include <vector>
#include <istream>
#include <iostream>
#include <string>

lexer::token_type lexer::next_token()
{
    switch (next_char())
    {
    case '[':
        return token_type::TOKEN_BEGIN_ARRAY;
        break;
    case ']':
        return token_type::TOKEN_END_ARRAY;
        break;

    case '{':
        return token_type::TOKEN_BEGIN_OBJECT;
        break;

    case '}':
        return token_type::TOKEN_END_OBJECT;
        break;

    case ':':
        return token_type::TOKEN_NAME_SEPARATOR;
        break;

    case ',':
        return token_type::TOKEN_VALUE_SEPARATOR;
        break;

    case '\"':
        return string_token();
        break;

    case 't':
        return literal_token("true", token_type::TOKEN_TRUE);
        break;

    case 'f':
        return literal_token("false", token_type::TOKEN_TRUE);
        break;

    case 'n':
        return literal_token("null", token_type::TOKEN_TRUE);
        break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '-':
        return number_token();
        break;

    case std::char_traits<char>::eof():
        return token_type::TOKEN_EOF;
        break;

    default:
        return token_type::TOKEN_ERROR;
    }
}

void lexer::skip_whitespace()
{
    while(current_char == ' ' || current_char == '\n' || current_char == '\t' || current_char == '\r')
    {
        next_char();
    }
}

std::vector<lexer::token_type> full_token_scan()
{

}

char lexer::next_char()
{
    current_char = input.get_next_char();
    ++line_character_pos;

    if (current_char == '\n')
    {
        ++line_count;
        line_character_pos = 0;
    }

    return current_char;
}