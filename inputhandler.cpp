#include "inputhandler.hpp"
#include <fstream>
#include <sstream>
#include <string>


file_input_handler::file_input_handler(std::string file_name)
{
    this->src.open(file_name);
}

char file_input_handler::get_next_char()
{
    return this->src.get();
}

string_input_handler::string_input_handler(std::string str)
{
    this->src.str(str);
}

char string_input_handler::get_next_char()
{
    return this->src.get();
}