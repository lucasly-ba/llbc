#pragma once
#include <ast/type.h>
#include <gbir/inst/inst.h>
#include <gbir/value.h>
#include <string>

namespace gbir
{
    class GlobalAddrInst : public GbirInst
    {
    public:
        GlobalAddrInst(std::string name, GbirValue result);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);
        GbirValue result_get() const;
        void result_set(GbirValue result);

    private:
        std::string name_;
        GbirValue result_;
    };
} // namespace gbir
