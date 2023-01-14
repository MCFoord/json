#ifndef VALUE
#define VALUE

#include <string>
#include <vector>
#include <variant>
#include <ostream>
#include <memory>
#include "json_object.hpp"
#include "value.hpp"

class Json_object;

class Value
{
    public:
        Value();
        Value(const char*);
        Value(unsigned int val);
        Value(int val);
        Value(double val);
        Value(std::string val);
        Value(bool val);
        Value(std::vector<Value> val);
        Value(std::unique_ptr<Json_object> val);
        Value(Json_object* val);
        // friend std::ostream& operator<<(std::ostream& stream, const Value& val)
        // {
        //     std::visit([&stream] (const auto& x) {stream << x;}, val);
        // };

    private:
        std::variant<unsigned int, int, double, std::string, bool, std::vector<Value>, Json_object*> value;
};

typedef std::unique_ptr<Value> ValuePtr;


#endif //VALUE