#ifndef JSONOBJECT
#define JSONOBJECT

#include <unordered_map>
#include "value.hpp"

class Value;

class Json_object
{
    public:
        Json_object();
        Value& operator[](const std::string& key);
    private:
        std::unordered_map<std::string, Value*> object;

};

#endif // JSONOBJECT