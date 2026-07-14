#include <gbir/inst/global.h>

namespace gbir
{
    GlobalAddrInst::GlobalAddrInst(std::string name, GbirValue result)
        : name_(std::move(name))
        , result_(result)
    {}

    void GlobalAddrInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& GlobalAddrInst::name_get() const
    {
        return name_;
    }

    void GlobalAddrInst::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    GbirValue GlobalAddrInst::result_get() const
    {
        return result_;
    }

    void GlobalAddrInst::result_set(GbirValue result)
    {
        result_ = result;
    }
} // namespace gbir
