#ifndef VALUE
#define VALUE

#include <any>
#include "value_t.hpp"
#include <string>
#include <vector>
#include <unordered_map>

union Value
{
    unsigned int uint;
    int sint;
    double dbl;
    std::string string;
    bool boolean;
    std::vector<Value> array;
    std::unordered_map<std::string, Value> object;
};

#endif //VALUE