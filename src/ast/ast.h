#pragma once
#include <cstddef>
#include <fwd.h>

namespace ast
{
    struct Location
    {
        size_t col;
        size_t line;
    };

    class Ast
    {
    public:
        explicit Ast(const Location& location);
        Ast(const Ast&) = delete;
        Ast& operator=(const Ast&) = delete;
        Ast(Ast&&) = delete;
        Ast& operator=(Ast&&) = delete;

        virtual ~Ast() = default;
        virtual void accept(Visitor& v) = 0;

        const Location& location_get() const;
        void location_set(const Location&);

    protected:
        Location location_;
    };
} // namespace ast
