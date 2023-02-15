#include <iostream>
#include <string>
#include <variant>
#include <fstream>
#include "lexer.hpp"
#include "inputhandler.hpp"
#include "json_t.hpp"
#include "parser.hpp"
#include "exceptions.hpp"

int main(int argc, char *argv[]) 
{

    if (argc != 2)
    {
        std::cout << "incorrect number of arguments: ./test.run <file to parse>\n";
        return EXIT_FAILURE;
    }

    std::stringstream ss;

    ss << "hello ";
    ss << "";
    ss << "world\n";

    std::cout << ss.str();

    // json_t json = json_t(std::unordered_map<std::string, json_t*>({{"lol", new json_t(400)}, {"goodbye", new json_t("gimp")}}));
    // json_t testjson = json_t();

    // std::string key = "hello";
    // json_t val = 46;

    // json_t& test = json;
    // // test = 45;

    // json_t& test2 = testjson;
    // test2 = 900;

    // std::ifstream testfile;
    // testfile.open("./inputs/numbers.json");

    // std::cout << testfile.get() << "\n";

    // val = 95;
    // json[key] = 25;
    // val = json[key];
    // json[key] = "max";
    // val = json[key];
    // json[key] = -200;
    // val = json[key];
    // json[key] = 2.00;
    // val = json[key];
    // json[key] = true;
    // val = json[key];
    // json[key] = json_t();
    // json[key][key] = "jim";

    File_input_handler* input = new File_input_handler(argv[1]);
    Parser parser = Parser(Lexer(input));

    json_t* output;

    try
    {
        output = parser.parse();
    }
    catch (unexepected_token_exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(unexpected_character_exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << output->to_string(4) << "\n";
    
    return EXIT_SUCCESS;
}