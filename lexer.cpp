#include <vector>
#include <istream>
#include <iostream>
#include <string>
#include <iomanip>
#include "lexer.hpp"
#include "inputhandler.hpp"

Lexer::Lexer(Input_handler* input)
{
    this->m_input = input;
    m_line_character_pos = 0;
    m_line_count = 0;
    m_current_char_unprocessed = false;
    m_token_peeked = false;
}

Lexer::Lexer() {};

Lexer::token_type Lexer::next_token()
{
    if (m_token_peeked)
    {
        m_token_peeked = false;
        return m_next_token;
    }

    if (!m_current_char_unprocessed)
    {
        next_char();
    }
    else
    {
        m_current_char_unprocessed = false;
    }

    skip_whitespace();

    switch (m_current_char)
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

Lexer::token_type Lexer::peek_next_token()
{
    m_next_token = next_token();
    m_token_peeked = true;
    return m_next_token;
}

std::string Lexer::token_value_string(token_type token)
{
    std::string value;
    switch (token)
    {
        case token_type::TOKEN_BEGIN_OBJECT:
            return "{";
            break;
        case token_type::TOKEN_END_OBJECT:
            return "}";
            break;
        case token_type::TOKEN_BEGIN_ARRAY:
            return "[";
            break;
        case token_type::TOKEN_END_ARRAY:
            return "]";
            break;
        case token_type::TOKEN_NAME_SEPARATOR:
            return ":";
            break;
        case token_type::TOKEN_VALUE_SEPARATOR:
            return ",";
            break;
        case token_type::TOKEN_NUMBER:
            value = m_token_values.front();
            m_token_values.pop();
            return value;
            break;
        case token_type::TOKEN_STRING:
            value = m_token_values.front();
            m_token_values.pop();
            return value;
            break;
        case token_type::TOKEN_TRUE:
            return "true";
            break;
        case token_type::TOKEN_FALSE:
            return "false";
            break;
        case token_type::TOKEN_NULL:
            return "null";
            break;
        case token_type::TOKEN_ERROR:
            return "ERROR";
            break;
        case token_type::TOKEN_EOF:
            return "EOF";
            break;
        default:
            return "ENUM ERROR";
            break;
    }
}

std::string Lexer::token_name_string(token_type token)
{
    switch (token)
    {
        case token_type::TOKEN_BEGIN_OBJECT:
            return "TOKEN_BEGIN_OBJECT";
            break;
        case token_type::TOKEN_END_OBJECT:
            return "TOKEN_END_OBJECT";
            break;
        case token_type::TOKEN_BEGIN_ARRAY:
            return "TOKEN_BEGIN_ARRAY";
            break;
        case token_type::TOKEN_END_ARRAY:
            return "TOKEN_END_ARRAY";
            break;
        case token_type::TOKEN_NAME_SEPARATOR:
            return "TOKEN_NAME_SEPARATOR";
            break;
        case token_type::TOKEN_VALUE_SEPARATOR:
            return "TOKEN_VALUE_SEPARATOR";
            break;
        case token_type::TOKEN_NUMBER:
            return"TOKEN_NUMBER";
            break;
        case token_type::TOKEN_STRING:
            return"TOKEN_STRING";
            break;
        case token_type::TOKEN_TRUE:
            return "TOKEN_TRUE";
            break;
        case token_type::TOKEN_FALSE:
            return "TOKEN_FALSE";
            break;
        case token_type::TOKEN_NULL:
            return "TOKEN_NULL";
            break;
        case token_type::TOKEN_ERROR:
            return "TOKEN_ERROR";
            break;
        case token_type::TOKEN_EOF:
            return "TOKEN_EOF";
            break;
        default:
            return "ENUM ERROR";
            break;
    }
}

void Lexer::skip_whitespace()
{
    while(m_current_char == ' ' || m_current_char == '\n' || m_current_char == '\t' || m_current_char == '\r')
    {
        next_char();
    }
}

//# todo: add unicode escapes 
Lexer::token_type Lexer::string_token()
{
    m_token_buffer.clear();

    while (m_current_char != std::char_traits<char>::eof())
    {
        switch (next_char())
        {
            //valid string
            case '\"':
                m_token_values.push(m_token_buffer);
                return token_type::TOKEN_STRING;
                break;
            
            // escapes
            case '\\':
                switch (next_char())
                {
                    case '\"':
                        m_token_buffer.push_back('\"');
                        break;

                    case '\\':
                        m_token_buffer.push_back('\\');
                        break;

                    case '/':
                        m_token_buffer.push_back('/');
                        break;

                    case 'b':
                        m_token_buffer.push_back('\b');
                        break;

                    case 'f':
                        m_token_buffer.push_back('\f');
                        break;

                    case 'n':
                        m_token_buffer.push_back('\n');
                        break;

                    case 'r':
                        m_token_buffer.push_back('\r');
                        break;

                    case 't':
                        m_token_buffer.push_back('\t');
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
                m_token_buffer.push_back(m_current_char);
                break;

            default:
                return token_type::TOKEN_ERROR;
                break;
        }
    }
    
    //eof reached before valid string found
    return token_type::TOKEN_ERROR;
}

Lexer::token_type Lexer::number_token()
{
    number_state state = number_state::STATE_INITIAL;
    m_token_buffer.clear();
    while (true)
    {
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
                m_token_values.push(m_token_buffer);
                m_current_char_unprocessed = true;
                return token_type::TOKEN_NUMBER;
                break;
                
            case number_state::STATE_ERROR:
                return token_type::TOKEN_ERROR;
                break;
        }
    }
}

Lexer::number_state Lexer::number_state_initial()
{
    switch (m_current_char)
    {
        case '-':
            m_token_buffer.push_back(m_current_char);
            return number_state_minus();
            break;

        case '0':
            m_token_buffer.push_back(m_current_char);
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_number();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

Lexer::number_state Lexer::number_state_minus()
{
    switch (next_char())
    {
        case '0':
            m_token_buffer.push_back(m_current_char);
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_number();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

Lexer::number_state Lexer::number_state_zero()
{
    switch (next_char())
    {
        case '.':
            m_token_buffer.push_back(m_current_char);
            return number_state_mantissa();
            break;

        case 'e':
        case 'E':
            m_token_buffer.push_back(m_current_char);
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
            m_token_buffer.push_back(m_current_char);
            return number_state::STATE_ERROR;
            break;

        default:
            return number_state::STATE_FINAL;
            break;
    }
}

Lexer::number_state Lexer::number_state_digit_number()
{
    switch (next_char())
    {
        case '.':
            m_token_buffer.push_back(m_current_char);
            return number_state_mantissa();
            break;
        
        case 'e':
        case 'E':
            m_token_buffer.push_back(m_current_char);
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_number();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

Lexer::number_state Lexer::number_state_digit_fraction()
{
    switch (next_char())
    {
        case 'e':
        case 'E':
            m_token_buffer.push_back(m_current_char);
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_fraction();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

Lexer::number_state Lexer::number_state_digit_exponent()
{
    switch (next_char())
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_exponent();
            break;
        
        default:
            return number_state::STATE_FINAL;
            break;
    }
}

Lexer::number_state Lexer::number_state_mantissa()
{
    switch (next_char())
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_fraction();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

Lexer::number_state Lexer::number_state_e()
{
    switch (next_char())
    {
        case '+':
        case '-':
            m_token_buffer.push_back(m_current_char);
            return number_state_plus_minus();
            break;

        default:
            return number_state::STATE_ERROR;
            break;
    }
}

Lexer::number_state Lexer::number_state_plus_minus()
{
    switch (next_char())
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
            m_token_buffer.push_back(m_current_char);
            return number_state_digit_exponent();
            break;
        
        default:
            return number_state::STATE_ERROR;
            break;
    }
}

Lexer::token_type Lexer::literal_token(std::string literal, token_type token)
{
    for (auto& c : literal)
    {
        if (c != m_current_char)
        {
            return token_type::TOKEN_ERROR;
        }
        next_char();
    }
    
    m_current_char_unprocessed = true;
    return token;
}

void Lexer::full_token_scan()
{
    std::vector<token_type> tokens;
    token_type token = next_token();

    tokens.push_back(token);

    while (token != token_type::TOKEN_EOF && token != token_type::TOKEN_ERROR)
    {
        token = next_token();
        tokens.push_back(token);
    }

    for (auto& t : tokens)
    {
        std::cout << std::setw(25)
                  << std::left
                  << token_name_string(t)
                  << std::setw(20)
                  << std::left
                  << token_value_string(t)
                  << '\n';
    }
}

char Lexer::next_char()
{
    m_current_char = m_input->get_next_char();
    ++m_line_character_pos;

    if (m_current_char == '\n')
    {
        ++m_line_count;
        m_line_character_pos = 0; 
    }

    return m_current_char;
}

std::string Lexer::token_value()
{
    return m_token_buffer;
}

int Lexer::get_char_pos()
{
    return m_line_character_pos;
}

int Lexer::get_line_pos()
{
    return m_line_count;
}