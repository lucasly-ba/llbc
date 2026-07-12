#pragma once
#include <ast/type.h>
#include <gbir/inst/inst.h>
#include <gbir/value.h>

namespace gbir
{
    class MemInst : public GbirInst
    {
    public:
        explicit MemInst(GbirValue result);
        GbirValue result_get() const;
        void result_set(GbirValue result);

    private:
        GbirValue result_;
    };
    class AllocaInst : public MemInst
    {
    public:
        AllocaInst(ast::Type var_type, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        ast::Type type_get() const;
        void type_set(ast::Type type);

    private:
        ast::Type type_;
    };

    class LoadInst : public MemInst
    {
    public:
        LoadInst(GbirValue read_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        GbirValue read_value_get() const;
        void read_value_set(GbirValue read_value);

    private:
        GbirValue read_value_;
    };

    class StoreInst : public GbirInst
    {
    public:
        StoreInst(GbirValue target, GbirValue value);
        void accept(GbirVisitorBase& v) override;
        GbirValue target_get() const;
        void target_set(GbirValue target);
        GbirValue value_get() const;
        void value_set(GbirValue value);

    private:
        GbirValue target_;
        GbirValue value_;
    };

} // namespace gbir
