#ifndef JSONOBJECT
#define JSONOBJECT

#include <unordered_map>
#include <memory>
#include "value.hpp"

class Value;

class Json_object
{
    public:
        Value& operator[](std::string key);
    private:
        std::unordered_map<std::string, Value*> object;

};

typedef std::unique_ptr<Json_object> JsonPtr;

#endif // JSONOBJECT