#include <ast/type.h>
#include <optional>

namespace ast
{

    std::optional<Type> get_type(const std::string& value)
    {
        if (value == "int")
            return Type::Int;
        if (value == "float")
            return Type::Float;
        if (value == "string")
            return Type::String;
        if (value == "bool")
            return Type::Bool;
        if (value == "dollar")
            return Type::Dollar;
        if (value == "chance")
            return Type::Chance;
        if (value == "reputation")
            return Type::Reputation;
        return std::nullopt;
    }
    std::string to_string(Type type)
    {
        switch (type)
        {
        case Type::Int:
            return "int";
        case Type::Float:
            return "float";
        case Type::String:
            return "string";
        case Type::Bool:
            return "bool";
        case Type::Dollar:
            return "dollar";
        case Type::Chance:
            return "chance";
        case Type::Reputation:
            return "reputation";
        default:
            return "unknown";
        }
    }
} // namespace ast
