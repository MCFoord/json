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
    if(this->m_type != value_t::TYPE_OBJECT)
    {  
        throw json_key_access_in_non_object_exception();
    }

    return *std::get<std::map<std::string, json_t*>>(this->m_value).emplace(key, new json_t()).first->second;
}

std::string json_t::to_string()
{
    std::stringstream ss;
    bool b;
    std::string s;
    std::string object_last_key;
    json_t* array_last_element;

    switch(m_type)
    {
        case value_t::TYPE_OBJECT:
            object_last_key = std::get<std::map<std::string, json_t*>>(m_value).rbegin()->first;

            ss << "{";

            for(const auto& [key, value] : std::get<std::map<std::string, json_t*>>(m_value))
            {
                ss << "\"" << key << "\": " << value->to_string();

                if(key != object_last_key)
                {
                    ss << ",";
                }
            }

            ss << "}";
            break;

        case value_t::TYPE_ARRAY:
            array_last_element = std::get<std::vector<json_t*>>(m_value).back();

            ss << "[";

            for (const auto& e : std::get<std::vector<json_t*>>(m_value))
            {
                ss << e->to_string();

                if (e != array_last_element)
                {
                    ss << ",";
                }
            }

            ss << "]";
            break;

        case value_t::TYPE_NULL:
            ss << "null";
            break;

        case value_t::TYPE_BOOL:
            b = std::get<bool>(m_value);
            s = (b) ? "true" : "false";
            ss << s;
            break;

        case value_t::TYPE_UNSIGNED_INT:
            ss << std::get<unsigned int>(m_value);
            break;

        case value_t::TYPE_SIGNED_INT:
            ss << std::get<int>(m_value);
            break;

        case value_t::TYPE_DOUBLE:
            ss << std::get<double>(m_value);
            break;

        case value_t::TYPE_STRING:
            ss << "\"" << std::get<std::string>(m_value) << "\"";
            break;
    }

    return ss.str();
}