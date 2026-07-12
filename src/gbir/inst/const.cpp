#include <gbir/inst/const.h>

namespace gbir
{
    ConstInst::ConstInst(GbirValue result)
        : result_(result)
    {}

    GbirValue ConstInst::result_get() const
    {
        return result_;
    }

    void ConstInst::result_set(GbirValue result)
    {
        result_ = result;
    }

    ConstIntBaseInst::ConstIntBaseInst(int raw_value, GbirValue result)
        : ConstInst(result)
        , raw_value_(raw_value)
    {}

    int ConstIntBaseInst::raw_value_get() const
    {
        return raw_value_;
    }

    void ConstIntBaseInst::raw_value_set(int raw_value)
    {
        raw_value_ = raw_value;
    }

    ConstIntInst::ConstIntInst(int raw_value, GbirValue result)
        : ConstIntBaseInst(raw_value, result)
    {}

    void ConstIntInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    ConstFloatInst::ConstFloatInst(float raw_value, GbirValue result)
        : ConstInst(result)
        , raw_value_(raw_value)
    {}

    void ConstFloatInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    float ConstFloatInst::raw_value_get() const
    {
        return raw_value_;
    }

    void ConstFloatInst::raw_value_set(float raw_value)
    {
        raw_value_ = raw_value;
    }

    ConstStringInst::ConstStringInst(std::string raw_value, GbirValue result)
        : ConstInst(result)
        , raw_value_(std::move(raw_value))
    {}

    void ConstStringInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    std::string ConstStringInst::raw_value_get() const
    {
        return raw_value_;
    }

    void ConstStringInst::raw_value_set(std::string raw_value)
    {
        raw_value_ = std::move(raw_value);
    }

    ConstBoolInst::ConstBoolInst(bool raw_value, GbirValue result)
        : ConstInst(result)
        , raw_value_(raw_value)
    {}

    void ConstBoolInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    bool ConstBoolInst::raw_value_get() const
    {
        return raw_value_;
    }

    void ConstBoolInst::raw_value_set(bool raw_value)
    {
        raw_value_ = raw_value;
    }

    ConstDollarsInst::ConstDollarsInst(int raw_value, GbirValue result)
        : ConstIntBaseInst(raw_value, result)
    {}

    void ConstDollarsInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    ConstChanceInst::ConstChanceInst(int raw_value, GbirValue result)
        : ConstIntBaseInst(raw_value, result)
    {}

    void ConstChanceInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    ConstStreakInst::ConstStreakInst(int raw_value, GbirValue result)
        : ConstIntBaseInst(raw_value, result)
    {}

    void ConstStreakInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }
} // namespace gbir
