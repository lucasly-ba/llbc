#include <gbir/value.h>

namespace gbir
{
    GbirValue::GbirValue(int id, ast::Type type)
        : id_(id)
        , type_(type)
    {}

    int GbirValue::id_get() const
    {
        return id_;
    }

    ast::Type GbirValue::type_get() const
    {
        return type_;
    }
} // namespace gbir
