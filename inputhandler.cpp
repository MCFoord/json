#include "inputhandler.hpp"
#include <fstream>
#include <sstream>
#include <string>


File_input_handler::File_input_handler(std::string file_name)
{
    this->src.open(file_name);
}

char File_input_handler::get_next_char()
{
    return this->src.get();
}

String_input_handler::String_input_handler(std::string str)
{
    this->src.str(str);
}

char String_input_handler::get_next_char()
{
    return this->src.get();
}