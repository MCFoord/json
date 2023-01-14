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
        //need to be an actual value pointer to an empty value - may need ot ensure that pointer to value is removed when updating it to a new one
    }

    return *iterable->second;
}
