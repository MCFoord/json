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
            std::stringstream ss;
            ss << "PARSE_ERROR: unexpected json token \"" << token_value << "\" at line " << line_pos  << " char " << char_pos;

            m_what = ss.str();
        };

        const char* what() const noexcept override
        {
            return m_what.c_str();
        }; 

    private:
        std::string m_what;
};

class json_key_access_in_non_object_exception : public std::exception
{
    public:
        const char* what() const noexcept
        {
            return "ACCESS_ERROR: trying to access key in non object type";
        };
};


//value expected
//end of number expected
//end of string expected
//comma, end of object, or end of array expected
//object, array or literal expected
//key expected
class unexpected_character_exception : public std::exception
{
    public:
        unexpected_character_exception(std::string expected, char actual)
        {
            std::stringstream ss;

            ss << "LEX_ERROR: " << expected << " expected, '" << actual << "' received instead";

            m_what = ss.str();
        };

        const char* what() const noexcept
        {
            return m_what.c_str();
        };

    private:
        std::string m_what;
};


#endif //EXCEPTIONS