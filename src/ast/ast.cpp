#include <ast.h>

namespace ast
{
    const Location& Ast::location_get() const
    {
        return location_;
    }

    void Ast::location_set(const Location& location)
    {
        location_ = location;
    }

} // namespace ast
