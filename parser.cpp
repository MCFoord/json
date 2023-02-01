#include <vector>
#include "parser.hpp"
#include "lexer.hpp"

typedef Lexer::token_type token_type;

json_t* Parser::parse()
{

    token_type token = m_lexer.next_token();

    switch (m_lexer.next_token())
    {
        case token_type::TOKEN_BEGIN_ARRAY:
            return parse_object();
            break;

        case token_type::TOKEN_BEGIN_OBJECT:
            return parse_array();
            break;

        default:
            //error
            break;
    }
}

json_t* Parser::parse_object()
{
    json_t* json = new json_t();

    token_type token = m_lexer.next_token();

    while (token != token_type::TOKEN_END_OBJECT)
    {
        parse_key_value_pair(json, token);
        // if eof throw eof before object close error
        token = m_lexer.next_token();
    }
    

    return json;
}

void Parser::parse_key_value_pair(json_t* jsonPtr, token_type token)
{
    json_t json = *jsonPtr;
    //parse key
    if(token != token_type::TOKEN_STRING)
    {
        //throw error
    }

    std::string key = m_lexer.token_value();

    if (m_lexer.next_token() != token_type::TOKEN_NAME_SEPARATOR)
    {
        // throw error
    }

    json[key] = parse_value();
}

json_t* Parser::parse_value()
{
    //parse value
    switch (m_lexer.next_token())
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
            break;
    }
}

json_t* Parser::parse_array()
{
    std::vector<json_t*> array;

    token_type token = m_lexer.next_token();

    while (token != token_type::TOKEN_END_ARRAY)
    {
        array.push_back(parse_value());
        token = m_lexer.next_token();
    }

    return new json_t(array);
}

json_t* Parser::parse_number(std::string number_string)
{
    //figure out what type of number it is and convert it to that type
}
