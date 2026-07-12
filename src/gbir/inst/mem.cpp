#include <gbir/inst/mem.h>

namespace gbir
{
    MemInst::MemInst(GbirValue result)
        : result_(result)
    {}

    GbirValue MemInst::result_get() const
    {
        return result_;
    }

    void MemInst::result_set(GbirValue result)
    {
        result_ = result;
    }

    AllocaInst::AllocaInst(ast::Type var_type, GbirValue result)
        : MemInst(result)
        , type_(var_type)
    {}

    void AllocaInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    ast::Type AllocaInst::type_get() const
    {
        return type_;
    }

    void AllocaInst::type_set(ast::Type type)
    {
        type_ = type;
    }

    LoadInst::LoadInst(GbirValue read_value, GbirValue result)
        : MemInst(result)
        , read_value_(read_value)
    {}

    void LoadInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue LoadInst::read_value_get() const
    {
        return read_value_;
    }

    void LoadInst::read_value_set(GbirValue read_value)
    {
        read_value_ = read_value;
    }

    StoreInst::StoreInst(GbirValue target, GbirValue value)
        : target_(target)
        , value_(value)
    {}

    void StoreInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue StoreInst::target_get() const
    {
        return target_;
    }

    void StoreInst::target_set(GbirValue target)
    {
        target_ = target;
    }

    GbirValue StoreInst::value_get() const
    {
        return value_;
    }

    void StoreInst::value_set(GbirValue value)
    {
        value_ = value;
    }
} // namespace gbir
