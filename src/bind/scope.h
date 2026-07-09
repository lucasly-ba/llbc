#pragma once
#include <ast/all.h>
#include <map>
namespace bind
{
    using namespace ast;
    class Scope
    {
    public:
        Scope() = default;
        void scope_begin();
        void scope_end();
        Dec* get_dec(std::string dec_name) const;
        Dec* get_dec_in_first_scope(std::string dec_name) const;
        Dec* get_dec_in_last_scope(std::string dec_name) const;
        void put_dec(std::string dec_name, Dec* dec);

    private:
        std::vector<std::map<std::string, Dec*>> scoped_map_;
    };
} // namespace bind
