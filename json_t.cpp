#include <memory>
#include <string>
#include "json_t.hpp"


json_t::json_t(): value(std::unordered_map<std::string, json_t*>()) {};

json_t::json_t(const char* val)
{
    std::string string = val;
    this->value = string;
};

json_t::json_t(unsigned int val): value(val) {};

json_t::json_t(int val): value(val) {};

json_t::json_t(double val): value(val) {};

json_t::json_t(std::string val): value(val) {};

json_t::json_t(bool val): value(val) {};

json_t::json_t(std::vector<json_t> val): value(val) {};

json_t::json_t(std::unordered_map<std::string, json_t*> val): value(val) {};

json_t& json_t::operator[](std::string key)
{
    if(this->type != value_t::TYPE_OBJECT)
    {  
        // throw an error
    }

    return *std::get<std::unordered_map<std::string, json_t*>>(this->value).emplace(key, new json_t()).first->second;
}