#ifndef VALUE
#define VALUE

#include <string>
#include <vector>
#include <variant>
#include <ostream>
#include <memory>
#include <unordered_map>
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
        json_t(std::vector<json_t> val);
        json_t(std::unordered_map<std::string, json_t*> val);
        json_t& operator[](std::string key);
        // friend std::ostream& operator<<(std::ostream& stream, const Value& val)
        // {
        //     std::visit([&stream] (const auto& x) {stream << x;}, val);
        // };
        std::variant<unsigned int, int, double, std::string, bool, std::vector<json_t>, std::unordered_map<std::string, json_t*>> value;
    private:
        
        value_t type;

};

#endif //VALUE