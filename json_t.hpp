#ifndef VALUE
#define VALUE

#include <string>
#include <vector>
#include <variant>
#include <ostream>
#include <memory>
#include <map>
#include "json_t.hpp"
#include "value_t.hpp"

class json_t
{
    public:
        json_t();
        json_t(const char*);
        json_t(unsigned int val);
        json_t(int val);
        json_t(double val);
        json_t(std::string val);
        json_t(bool val);
        json_t(std::vector<json_t*> val);
        json_t(std::map<std::string, json_t*> val);
        json_t& operator[](std::string key);
        std::string to_string(int indent = 0, int level = 0, bool ignoreIndent = false);
        std::string add_indentation(int level, std::string indentation);
        // friend std::ostream& operator<<(std::ostream& stream, const Value& val)
        // {
        //     std::visit([&stream] (const auto& x) {stream << x;}, val);
        // };
    private:
        std::variant<unsigned int, int, double, std::string, bool, std::vector<json_t*>, std::map<std::string, json_t*>> m_value;
        value_t m_type;

};

#endif //VALUE