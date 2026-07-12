#pragma once
#include <cstddef>
#include <ast/fwd.h>
#include <vector>

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
        virtual void accept(VisitorBase& v) = 0;

        const Location& location_get() const;
        void location_set(const Location&);

    protected:
        Location location_;
    };

    class Program
    {
    public:
        explicit Program(std::vector<dec_ptr> decs);
        ~Program();

        const std::vector<dec_ptr>& decs_get() const;
        std::vector<dec_ptr>& decs_get();
        void decs_set(std::vector<dec_ptr> decs);

    private:
        std::vector<dec_ptr> decs_;
    };
} // namespace ast
