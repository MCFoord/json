#ifndef INPUTHANDLER
#define INPUTHANDLER

#include <fstream>
#include <sstream>
#include <string>

class input_handler
{
    public:
        virtual char get_next_char()
        {
            return;
        };
};

class file_input_handler: public input_handler
{   
    public:
        file_input_handler(std::string file_name);
        char get_next_char();
    private:
        std::ifstream src;
};

class string_input_handler: public input_handler
{   
    public:
        string_input_handler(std::string str);
        char get_next_char();
    private:
        std::istringstream src;
};

#endif