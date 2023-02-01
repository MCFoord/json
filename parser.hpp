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
        parse_object();
        parse_array();

    private:
        Lexer m_lexer;
};

#endif //PARSER