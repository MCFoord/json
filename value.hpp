#ifndef VALUE
#define VALUE

#include <string>
#include <vector>
#include <variant>
#include "json_object.hpp"

class Json_object;

class Value
{
    public:
        Value();
    private:
        std::variant<unsigned int, int, double, std::string, bool, std::vector<Value>, Json_object> value;
};

#endif //VALUE