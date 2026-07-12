#pragma once
#include <ast/type.h>

namespace gbir
{
    class GbirValue
    {
    public:
        GbirValue(int id, ast::Type type);

        int id_get() const;
        ast::Type type_get() const;

    private:
        int id_;
        ast::Type type_;
    };
} // namespace gbir
