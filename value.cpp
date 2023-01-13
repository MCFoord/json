#include "value.hpp"
#include <memory>

Value::Value(unsigned int val)
{
    value = val;
};

Value::Value(int val)
{
    value = val;
};

Value::Value(double val)
{
    value = val;
};

Value::Value(std::string val)
{
    value = val;
};

Value::Value(bool val)
{
    value = val;
};

//fix me
Value::Value(std::vector<Value> val)
{
    value = 0;
};

Value::Value(Json_object* val)
{
    this->value = val;
};

