#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <iostream>
#include <sstream>
#include "parser.hpp"
#include "lexer.hpp"

typedef Lexer::token_type token_type;

class unexepected_token_exception : public std::exception
{
    public:
        unexepected_token_exception(std::string token_value, int char_pos, int line_pos)
        {
            m_token_value = token_value;
            m_char_pos = char_pos;
            m_line_pos = line_pos;
        };

        const char* what()
        {
            std::stringstream ss;

            ss << "unexpected token: \""
               << m_token_value
               << "\" at line "
               << m_line_pos 
               << "char "
               << m_char_pos
               <<".\n";
            
            return ss.str().c_str();
        };

    private:
        std::string m_token_value;
        int m_char_pos;
        int m_line_pos;
};

#endif //EXCEPTIONS