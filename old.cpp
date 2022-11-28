#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "parser.h"

using std::vector;
using std::pair;
using std::string;

string parse::readFile()
{
    std::ifstream fs;
    fs.open("test.json");
    vector<char> input;

    char c;
    fs.get(c);
    while (!fs.eof())
    {
        if (!isspace(c))
        {
            input.push_back(c);
        }
        fs.get(c);
    }

    return std::string(input.begin(), input.end());
}

vector<pair<string, string>> parse::lex(string& jsonString)
{
    auto lexers = {lexSyntax, lexString, lexNumber, lexbool};
    vector<pair<string, string>> tokens;
    unsigned int i = 0;
    unsigned int idx = 0;
    while (i < jsonString.length())
    {
        for (auto lexer : lexers)
        {
            idx = lexer(tokens, jsonString, idx);
        }
        if (idx == i)
        {
            ++idx;
            i = idx;
        }
        i = idx;
    }

    for (auto token : tokens)
    {
        std::cout << "token: \"" << token.first << "\" type: " << token.second << std::endl;
    }
    std::cout << std::endl;
    return tokens;
}

int parse::lexSyntax(vector<pair<string, string>>& tokens, string& jsonString,unsigned int idx)
{
    char c = jsonString[idx];
    if (c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',')
    {
        tokens.push_back(std::make_pair(string(1, c), "syntax"));
        ++idx;
    }
    return idx;
}

int parse::lexString(vector<pair<string, string>>& tokens, string& jsonString, unsigned int idx)
{
    char c = jsonString[idx];
    string token = "";
    if (c == '"')
    {
        ++idx;
        c = jsonString[idx];
        while (c != '"' && idx < jsonString.length())
        {
            token.push_back(c);
            ++idx;
            c = jsonString[idx];
        }
        if (idx != jsonString.length())
        {
            tokens.push_back(std::make_pair(token, "string"));
        }
        ++idx;
    }
    return idx;
}

//only works for ints at this stage
int parse::lexNumber(vector<pair<string, string>>& tokens, string& jsonString, unsigned int idx)
{
    char c = jsonString[idx];
    string token = "";
    if (c >= '0' && c <= '9')
    {
        while (c >= '0' && c <= '9')
        {
            token.push_back(c);
            ++idx;
            c = jsonString[idx];
        }
        tokens.push_back(std::make_pair(token, "int"));
    }
    return idx;
}

//does not deal with null at this stage, may need to change later
//also may want to change the way it checks for the token - possibly open to errors
int parse::lexbool(vector<pair<string, string>>& tokens, string& jsonString, unsigned int idx)
{
    char c = jsonString[idx];
    string token = "";
    if (isBoolVal("true", jsonString, idx))
    {
        for (int i = 0; i < 4; ++i)
        {
            token.push_back(c);
            ++idx;
            c = jsonString[idx];
        }
        tokens.push_back(std::make_pair(token, "bool"));
    }
    else if (isBoolVal("false", jsonString, idx))
    {
        for (int i = 0; i < 5; ++i)
        {
            token.push_back(c);
            ++idx;
            c = jsonString[idx];
        }
        tokens.push_back(std::make_pair(token, "bool"));
    }
    return idx;
}

bool parse::isBoolVal(string boolVal, string& jsonString, unsigned int idx)
{
    bool isBoolVal = true;
    char c = jsonString[idx];
    for (char bc : boolVal)
    {
        if (c != bc)
        {
            isBoolVal = false;
        }
        ++idx;
        c = jsonString[idx];
    }
    return isBoolVal;
}