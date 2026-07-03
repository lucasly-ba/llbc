#include <type.h>
namespace ast
{
    std::string to_string(Type type)
    {
        switch (type)
        {
        case Type::Coin:
            return "coin";
        case Type::Chance:
            return "chance";
        case Type::Reputation:
            return "reputation";
        }
        return "";
    }
} // namespace ast
