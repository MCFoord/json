#include <iostream>
#include <string>
#include "lexer.hpp"
#include "inputhandler.hpp"
#include "value.hpp"
#include "json_object.hpp"

int main(int argc, char *argv[]) 
{

    Json_object json = Json_object();

    std::string key = "hello";
    Value val = 25;
    json[key] = 25;

    std::cout << json[key] << "\n";

    return EXIT_SUCCESS;
}