#include <optional>
#include <ast/type.h>

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
        if (value == "dollars")
            return Type::Dollars;
        if (value == "chance")
            return Type::Chance;
        if (value == "streak")
            return Type::Streak;
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
        case Type::Dollars:
            return "dollars";
        case Type::Chance:
            return "chance";
        case Type::Streak:
            return "streak";
        case Type::Void:
            return "void";
        default:
            return "unknown";
        }
    }
} // namespace ast
