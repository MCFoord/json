#include <iostream>
#include <string>
#include <variant>
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

    // std::cout << std::get<int>(val) << "\n";

    return EXIT_SUCCESS;
}