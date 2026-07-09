#include <ranges>
#include <scope.h>

namespace bind
{
    void Scope::scope_begin()
    {
        scoped_map_.emplace_back();
    }

    void Scope::scope_end()
    {
        scoped_map_.pop_back();
    }

    Dec* Scope::get_dec(std::string dec_name) const
    {
        for (auto& map : scoped_map_ | std::views::reverse)
            if (auto it = map.find(dec_name); it != map.end())
                return it->second;
        return nullptr;
    }

    Dec* Scope::get_dec_in_first_scope(std::string dec_name) const
    {
        if (auto it = scoped_map_.front().find(dec_name);
            it != scoped_map_.front().end())
            return it->second;
        return nullptr;
    }
    Dec* Scope::get_dec_in_last_scope(std::string dec_name) const
    {
        if (auto it = scoped_map_.back().find(dec_name);
            it != scoped_map_.back().end())
            return it->second;
        return nullptr;
    }

    void Scope::put_dec(std::string dec_name, Dec* dec)
    {
        scoped_map_.back().insert({ dec_name, dec });
    }
} // namespace bind
