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
        return literal_token("false", token_type::TOKEN_FALSE);
        break;

    case 'n':
        return literal_token("null", token_type::TOKEN_NULL);
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

//# todo: add unicode escapes 
lexer::token_type lexer::string_token()
{
    token_buffer.clear();

    while (current_char != std::char_traits<char>::eof())
    {
        switch (next_char())
        {
            //valid string
            case '\"':
                return token_type::TOKEN_STRING;
                break;
            
            // escapes
            case '\\':
                switch (next_char())
                {
                    case '\"':
                        token_buffer.push_back('\"');
                        break;

                    case '\\':
                        token_buffer.push_back('\\');
                        break;

                    case '/':
                        token_buffer.push_back('/');
                        break;

                    case 'b':
                        token_buffer.push_back('\b');
                        break;

                    case 'f':
                        token_buffer.push_back('\f');
                        break;

                    case 'n':
                        token_buffer.push_back('\n');
                        break;

                    case 'r':
                        token_buffer.push_back('\r');
                        break;

                    case 't':
                        token_buffer.push_back('\t');
                        break;

                    default:
                        // incorrect escaped character
                        return token_type::TOKEN_ERROR;
                        break;
                }
            
            //valid unescaped characters
            case 0x20:
            case 0x21:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x27:
            case 0x28:
            case 0x29:
            case 0x2A:
            case 0x2B:
            case 0x2C:
            case 0x2D:
            case 0x2E:
            case 0x2F:
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
            case 0x3A:
            case 0x3B:
            case 0x3C:
            case 0x3D:
            case 0x3E:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x44:
            case 0x45:
            case 0x46:
            case 0x47:
            case 0x48:
            case 0x49:
            case 0x4A:
            case 0x4B:
            case 0x4C:
            case 0x4D:
            case 0x4E:
            case 0x4F:
            case 0x50:
            case 0x51:
            case 0x52:
            case 0x53:
            case 0x54:
            case 0x55:
            case 0x56:
            case 0x57:
            case 0x58:
            case 0x59:
            case 0x5A:
            case 0x5B:
            case 0x5D:
            case 0x5E:
            case 0x5F:
            case 0x60:
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x64:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x68:
            case 0x69:
            case 0x6A:
            case 0x6B:
            case 0x6C:
            case 0x6D:
            case 0x6E:
            case 0x6F:
            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77:
            case 0x78:
            case 0x79:
            case 0x7A:
            case 0x7B:
            case 0x7C:
            case 0x7D:
            case 0x7E:
            case 0x7F:
                token_buffer.push_back(current_char);
                break;

            default:
                return token_type::TOKEN_ERROR;
                break;
        }
    }
    
    //eof reached before valid string found
    return token_type::TOKEN_ERROR;
}

lexer::token_type lexer::number_token()
{
    number_state state = number_state::STATE_INITIAL;

    switch (state)
    {
        case number_state::STATE_INITIAL:
            state = number_state_initial();
            break;
        case number_state::STATE_MINUS:
            state = number_state_minus();
            break;

        case number_state::STATE_ZERO:
            state = number_state_zero();
            break;

        case number_state::STATE_DIGIT_NUMBER:
            state = number_state_digit_number();
            break;

        case number_state::STATE_DIGIT_FRACTION:
            state = number_state_digit_fraction();
            break;

        case number_state::STATE_DIGIT_EXPONENT:
            state = number_state_digit_exponent();
            break;

        case number_state::STATE_MANTISSA:
            state = number_state_mantissa();
            break;

        case number_state::STATE_E:
            state = number_state_e();
            break;

        case number_state::STATE_PLUS_MINUS:
            state = number_state_plus_minus();
            break;

        case number_state::STATE_FINAL:

            break;
            
        case number_state::STATE_ERROR:

            break;
    }
}

lexer::number_state lexer::number_state_initial()
{
    switch (current_char)
    {
        case '-':
            return number_state_minus();
            break;

        case '0':
            return number_state_zero();
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return number_state_digit_number();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

lexer::number_state lexer::number_state_minus()
{
    switch (next_token())
    {
        case '0':
            return number_state_zero();
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return number_state_digit_number();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

lexer::number_state lexer::number_state_zero()
{
    switch (next_token())
    {
        case '.':
            return number_state_mantissa();
            break;

        case 'e':
        case 'E':
            return number_state_e();
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
            return number_state::STATE_ERROR;
            break;

        default:
            return number_state::STATE_FINAL;
            break;
    }
}

lexer::number_state lexer::number_state_digit_number()
{
    switch (next_token())
    {
        case '.':
            return number_state_mantissa();
            break;
        
        case 'e':
        case 'E':
            return number_state_e();
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
            return number_state_digit_number();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

lexer::number_state lexer::number_state_digit_fraction()
{
    switch (next_token())
    {
        case 'e':
        case 'E':
            return number_state_e();
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
            return number_state_digit_fraction();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

lexer::number_state lexer::number_state_digit_exponent()
{
    switch (next_token())
    {
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
            return number_state_digit_exponent();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

lexer::number_state lexer::number_state_mantissa()
{
    switch (next_token())
    {
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
            return number_state_digit_fraction();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

lexer::number_state lexer::number_state_e()
{
    switch (next_token())
    {
        case '+':
        case '-':
            return number_state_plus_minus();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

lexer::number_state lexer::number_state_plus_minus()
{
    switch (next_token())
    {
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
            return number_state_digit_exponent();
            break;
        
        default:
            return number_state::STATE_ERROR;
            break;
    }
}

lexer::token_type lexer::literal_token(std::string literal, token_type token)
{
    for (auto& c : literal)
    {
        if (c != next_char())
        {
            return token_type::TOKEN_ERROR;
        }
    }

    return token;
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
