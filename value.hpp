#ifndef VALUE
#define VALUE

#include <string>
#include <vector>
#include <variant>
#include <ostream>
#include "json_object.hpp"
#include "value.hpp"

class Json_object;

class Value
{
    public:
        Value(unsigned int val);
        Value(int val);
        Value(double val);
        Value(std::string val);
        Value(bool val);
        Value(std::vector<Value> val);
        Value(Json_object val);
        friend std::ostream& operator<<(std::ostream& stream, const Value& val)
        {
            std::visit([&stream] (const auto& x) {stream << x;}, val);
        };

    private:
        std::variant<unsigned int, int, double, std::string, bool, std::vector<Value>, Json_object> value;
};

#endif //VALUE