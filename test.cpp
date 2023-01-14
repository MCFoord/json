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
    Value val = 46;
    json[key] = 25;
    val = json[key];
    json[key] = "max";
    val = json[key];
    json[key] = -200;
    val = json[key];
    json[key] = 2.00;
    val = json[key];
    json[key] = true;
    val = json[key];
    Json_object json2 = Json_object();
    json[key] = &json2;
    val = json[key];


    return EXIT_SUCCESS;
}