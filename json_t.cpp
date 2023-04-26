#include <memory>
#include <string>
#include "json_t.hpp"
#include "value_t.hpp"
#include "exceptions.hpp"


json_t::json_t(): m_value(std::map<std::string, json_t*>()), m_type(value_t::TYPE_OBJECT){};

json_t::json_t(const char* val)
{
    std::string string = val;
    m_value = string;
    m_type = value_t::TYPE_STRING;
};

json_t::json_t(unsigned int val): m_value(val), m_type(value_t::TYPE_UNSIGNED_INT){};

json_t::json_t(int val): m_value(val), m_type(value_t::TYPE_SIGNED_INT){};

json_t::json_t(double val): m_value(val), m_type(value_t::TYPE_DOUBLE){};

json_t::json_t(std::string val): m_value(val), m_type(value_t::TYPE_STRING){};

json_t::json_t(bool val): m_value(val), m_type(value_t::TYPE_BOOL){};

json_t::json_t(std::vector<json_t*> val): m_value(val), m_type(value_t::TYPE_ARRAY){};

json_t::json_t(std::map<std::string, json_t*> val): m_value(val), m_type(value_t::TYPE_OBJECT){};

json_t& json_t::operator[](std::string key)
{
    if (this->m_type != value_t::TYPE_OBJECT)
    {  
        throw json_key_access_in_non_object_exception();
    }

    return *std::get<std::map<std::string, json_t*>>(this->m_value).emplace(key, new json_t()).first->second;
}

std::string json_t::to_string(int indent, int level, bool ignoreIndent) {
    std::string result;
    std::string indentation = std::string(indent, ' ');

    switch(m_type) {
        case value_t::TYPE_UNSIGNED_INT:
            result += std::to_string(std::get<unsigned int>(m_value));
            break;

        case value_t::TYPE_SIGNED_INT:
            result += std::to_string(std::get<int>(m_value));
            break;

        case value_t::TYPE_DOUBLE:
            result += std::to_string(std::get<double>(m_value));
            break;

        case value_t::TYPE_STRING:
            result += "\"" + std::get<std::string>(m_value) + "\"";
            break;

        case value_t::TYPE_NULL:
            result += "null";
            break;

        case value_t::TYPE_BOOL:
            result += std::get<bool>(m_value) ? "true" : "false";
            break;

        case value_t::TYPE_ARRAY:
        {
            result += ignoreIndent ? "[\n" : add_indentation(level, indentation) + "[\n";
            auto arr = std::get<std::vector<json_t*>>(m_value);
            for (auto it = arr.begin(); it != arr.end(); ++it)
            {
                result += add_indentation(level + 1, indentation) + (*it)->to_string(indent, level + 1, true);
                if (it != arr.end() - 1)
                {
                    result += ",";
                }
                result += "\n";
            }
            result += add_indentation(level, indentation) + "]";
            break;
        }

        case value_t::TYPE_OBJECT:
        {
            result += ignoreIndent ? "{\n" : add_indentation(level, indentation) + "{\n";
            auto obj = std::get<std::map<std::string, json_t*>>(m_value);
            std::map<std::string, json_t*>::iterator lastElement;
            lastElement = obj.end();
            --lastElement;

            for (auto it = obj.begin(); it != obj.end(); ++it)
            {
                result += add_indentation(level + 1, indentation) + "\"" + it->first + "\": " + it->second->to_string(indent, level + 1, true);
                if (it != lastElement)
                {
                    result += ",";
                }
                result += "\n";
            }
            result += add_indentation(level, indentation) + "}";
            break;
        }
    }

    return result;
}

std::string json_t::add_indentation(int level, std::string indentation) {
    std::string result;
    for (int i = 0; i < level; ++i)
    {
        result += indentation;
    }
    return result;
}