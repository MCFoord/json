#include <iostream>
#include <string>
#include <variant>
#include "lexer.hpp"
#include "inputhandler.hpp"
#include "json_t.hpp"

int main(int argc, char *argv[]) 
{

    json_t json = json_t(std::unordered_map<std::string, json_t*>({{"lol", new json_t(400)}, {"goodbye", new json_t("gimp")}}));
    json_t testjson = json_t();

    std::string key = "hello";
    json_t val = 46;

    json_t& test = json;
    // test = 45;

    json_t& test2 = testjson;
    test2 = 900;

    val = 95;
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
    json[key] = json_t();
    json[key][key] = "jim";


    return EXIT_SUCCESS;
}