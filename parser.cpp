#include <vector>
#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "exceptions.hpp"

typedef Lexer::token_type token_type;

Parser::Parser(Lexer lexer)
{
    this->m_lexer = lexer;
}

Parser::Parser() {};

json_t* Parser::parse()
{
    
    switch (next_token())
    {
        case token_type::TOKEN_BEGIN_ARRAY:
            return parse_array();
            break;

        case token_type::TOKEN_BEGIN_OBJECT:
            return parse_object();
            break;

        default:
            throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());
            break;
    }
}

json_t* Parser::parse_object()
{
    json_t* json = new json_t();

    next_token();
    token_type peeked_token;

    while (m_current_token != token_type::TOKEN_END_OBJECT)
    {
        parse_key_value_pair(*json, m_current_token);
        // if eof throw eof before object close error
        peeked_token = m_lexer.peek_next_token();

        if (peeked_token != token_type::TOKEN_END_OBJECT && peeked_token != token_type::TOKEN_VALUE_SEPARATOR)
        {
            throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());
        }

        if (next_token() == token_type::TOKEN_VALUE_SEPARATOR)
        {
            next_token();
        }
    }

    return json;
}

void Parser::parse_key_value_pair(json_t& json, token_type token)
{
    //parse key
    if(token != token_type::TOKEN_STRING)
    {
        throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());
    }

    std::string key = m_lexer.token_value();

    if (next_token() != token_type::TOKEN_NAME_SEPARATOR)
    {
        throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());
    }

    json_t* val = parse_value();

    json[key] = *val;
}

json_t* Parser::parse_value()
{
    //parse value
    

    switch (next_token())
    {
        case token_type::TOKEN_BEGIN_OBJECT:
            return parse_object();
            break;

        case token_type::TOKEN_BEGIN_ARRAY:
            return parse_array();  
            break;

        case token_type::TOKEN_NUMBER:
            return parse_number(m_lexer.token_value());
            break;

        case token_type::TOKEN_STRING:
            return new json_t(m_lexer.token_value());
            break;

        case token_type::TOKEN_TRUE:
            return new json_t(true);
            break;

        case token_type::TOKEN_FALSE:
            return new json_t(false);
            break;

        // // need to add support for this case elsewhere I think
        // case token_type::TOKEN_NULL:
        //     return new json_t(nullptr);
        //     break;
    
        default:
            // probably need to separate these errors to be specific
            // parse error
            throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());
            break;
    }
}

json_t* Parser::parse_array()
{
    std::vector<json_t*> array;
    token_type peeked_token;

    while (m_current_token != token_type::TOKEN_END_ARRAY)
    {
        array.push_back(parse_value());

    
        peeked_token = m_lexer.peek_next_token();

        if (peeked_token != token_type::TOKEN_END_ARRAY && peeked_token != token_type::TOKEN_VALUE_SEPARATOR)
        {
            throw unexepected_token_exception(m_lexer.token_value_string(m_current_token), m_lexer.get_char_pos(), m_lexer.get_line_pos());     
        }

        next_token();
    }

    return new json_t(array);
}

json_t* Parser::parse_number(std::string number_string)
{
    //figure out what type of number it is and convert it to that type

    for (char& c : number_string)
    {
        if (c == '.' || c == 'e' || c == 'E')
        {
            return new json_t(std::stod(number_string));
        }
    }
    
    int num = std::stoi(number_string);
    return new json_t(num);
}

token_type Parser::next_token()
{
    m_current_token = m_lexer.next_token();
    return m_current_token;
}