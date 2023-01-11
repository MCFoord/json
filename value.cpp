#include "value.hpp"

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

Value::Value(std::vector<Value> val)
{
    value = val;
};

Value::Value(Json_object val)
{
    value = val;
};

