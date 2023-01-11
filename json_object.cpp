#include <string>
#include "json_object.hpp"

template<typename T>
T& Json_object::operator[](const std::string& key)
{
    auto iterable = object.find(key);

    if (iterable == object.end())
    {
        iterable = object.insert()
    }
}