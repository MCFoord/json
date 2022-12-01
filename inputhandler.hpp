#ifndef INPUTHANDLER
#define INPUTHANDLER

#include <fstream>
#include <sstream>
#include <string>

class Input_handler
{
    public:
        virtual char get_next_char()
        {
            return std::char_traits<char>::eof();
        };
        virtual ~Input_handler() = default;
};

class File_input_handler: public Input_handler
{   
    public:
        File_input_handler(std::string file_name);
        char get_next_char() override;
    private:
        std::ifstream src;
};

class String_input_handler: public Input_handler
{   
    public:
        String_input_handler(std::string str);
        char get_next_char() override;
    private:
        std::istringstream src;
};

#endif