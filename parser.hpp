#ifndef PARSER
#define PARSER

class Parser
{
    public:
        enum parse_state
        {
            PARSE_OBJECT_START,
            PARSE_OBJECT_END,
            PARSE_ARRAY_START,
            PARSE_ARRAY_END
        };
};

#endif //PARSER