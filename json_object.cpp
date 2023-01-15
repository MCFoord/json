#include <string>
#include <iostream>
#include "value.hpp"
#include "json_object.hpp"


Value& Json_object::operator[](std::string key)
{
    auto iterable = object.find(key);

    if (iterable == object.end())
    {
        iterable = object.insert(std::make_pair(key, new Value())).first;
    }

    return *iterable->second;
}
