#include "parser.hpp"
#include "lexer.hpp"

json_t* Parser::parse()
{

    Lexer::token_type token = m_lexer.next_token();

    switch (m_lexer.next_token())
    {
        case Lexer::token_type::TOKEN_BEGIN_ARRAY:
            parse_object();
            break;

        case Lexer::token_type::TOKEN_BEGIN_OBJECT:
            parse_array();
            break;

        default:
            //error
            break;
    }
}