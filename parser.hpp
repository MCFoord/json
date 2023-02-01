#ifndef PARSER
#define PARSER

#include "inputhandler.hpp"
#include "json_t.hpp"
#include "lexer.hpp"

class Parser
{
    public:
        enum parse_state
        {
            PARSE_OBJECT_START,
            PARSE_OBJECT_END,
            PARSE_ARRAY_START,
            PARSE_ARRAY_END,
            PARSE_VALUE,
            PARSE_KEY,
            PARSE_ERROR
        };

        Parser(Lexer lexer);
        json_t* parse();
        json_t* parse_object();
        json_t* parse_array();
        void parse_key_value_pair(json_t* json, token_type token_type);
        json_t* parse_value();
        json_t* parse_number(std::string number_string);

    private:
        Lexer m_lexer;
        parse_state m_parse_state;
};

#endif //PARSER