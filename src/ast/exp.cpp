#include <ast/exp.h>
#include <ast/visitor.h>

namespace ast
{
    Exp::Exp(const Location& location)
        : Ast(location)
    {}

    OpExp::OpExp(const Location& location, exp_ptr left, Oper oper,
                 exp_ptr right)
        : Exp(location)
        , left_(std::move(left))
        , oper_(oper)
        , right_(std::move(right))
    {}

    void OpExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    std::string OpExp::to_string(OpExp::Oper op)
    {
        switch (op)
        {
        case OpExp::Oper::ADD:
            return "+";
        case OpExp::Oper::SUB:
            return "-";
        case OpExp::Oper::MUL:
            return "*";
        case OpExp::Oper::DIV:
            return "/";
        case OpExp::Oper::EQ:
            return "==";
        case OpExp::Oper::NEQ:
            return "!=";
        case OpExp::Oper::LT:
            return "<";
        case OpExp::Oper::LEQ:
            return "<=";
        case OpExp::Oper::GT:
            return ">";
        case OpExp::Oper::GEQ:
            return ">=";
        case OpExp::Oper::AND:
            return "&&";
        case OpExp::Oper::OR:
            return "||";
        default:
            return "unknown";
        }
    }
    Exp& OpExp::left_get() const
    {
        return *left_;
    }

    void OpExp::left_set(exp_ptr left)
    {
        left_ = std::move(left);
    }

    OpExp::Oper OpExp::oper_get() const
    {
        return oper_;
    }

    void OpExp::oper_set(Oper oper)
    {
        oper_ = oper;
    }

    Exp& OpExp::right_get() const
    {
        return *right_;
    }

    void OpExp::right_set(exp_ptr right)
    {
        right_ = std::move(right);
    }

    IntBaseExp::IntBaseExp(const Location& location, int value)
        : Exp(location)
        , value_(value)
    {}

    int IntBaseExp::value_get() const
    {
        return value_;
    }

    void IntBaseExp::value_set(int value)
    {
        value_ = value;
    }

    IntExp::IntExp(const Location& location, int value)
        : IntBaseExp(location, value)
    {}

    void IntExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    FloatExp::FloatExp(const Location& location, float value)
        : Exp(location)
        , value_(value)
    {}

    void FloatExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    float FloatExp::value_get() const
    {
        return value_;
    }

    void FloatExp::value_set(float value)
    {
        value_ = value;
    }

    StringExp::StringExp(const Location& location, std::string value)
        : Exp(location)
        , value_(std::move(value))
    {}

    void StringExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& StringExp::value_get() const
    {
        return value_;
    }

    void StringExp::value_set(std::string value)
    {
        value_ = std::move(value);
    }

    BoolExp::BoolExp(const Location& location, bool value)
        : Exp(location)
        , value_(value)
    {}

    void BoolExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    bool BoolExp::value_get() const
    {
        return value_;
    }

    void BoolExp::value_set(bool value)
    {
        value_ = value;
    }

    DollarsExp::DollarsExp(const Location& location, int value)
        : IntBaseExp(location, value)
    {}

    void DollarsExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    ChanceExp::ChanceExp(const Location& location, int value)
        : IntBaseExp(location, value)
    {}

    void ChanceExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    StreakExp::StreakExp(const Location& location, int value)
        : IntBaseExp(location, value)
    {}

    void StreakExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    CallExp::CallExp(const Location& location, std::string name,
                     std::vector<exp_ptr> args)
        : Exp(location)
        , name_(std::move(name))
        , args_(std::move(args))
    {}

    void CallExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& CallExp::name_get() const
    {
        return name_;
    }

    void CallExp::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const std::vector<exp_ptr>& CallExp::args_get() const
    {
        return args_;
    }

    std::vector<exp_ptr>& CallExp::args_get()
    {
        return args_;
    }

    void CallExp::args_set(std::vector<exp_ptr> args)
    {
        args_ = std::move(args);
    }

    const Dec* CallExp::def_get() const
    {
        return def_;
    }

    void CallExp::def_set(Dec* def)
    {
        def_ = def;
    }

    IdentExp::IdentExp(const Location& location, std::string name)
        : Exp(location)
        , name_(std::move(name))
    {}

    void IdentExp::accept(VisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& IdentExp::name_get() const
    {
        return name_;
    }

    void IdentExp::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const Dec* IdentExp::def_get() const
    {
        return def_;
    }

    void IdentExp::def_set(Dec* def)
    {
        def_ = def;
    }
} // namespace ast
