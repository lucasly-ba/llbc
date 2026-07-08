#pragma once
#include <ast/ast.h>
#include <ast/fwd.h>
#include <vector>

namespace ast
{
    class Exp : public Ast
    {
    public:
        explicit Exp(const Location& location);
    };

    class OpExp : public Exp
    {
    public:
        enum class Oper
        {
            ADD,
            SUB,
            MUL,
            DIV,
            EQ,
            NEQ,
            LT,
            LEQ,
            GT,
            GEQ,
            AND,
            OR,
        };
        OpExp(const Location& location, exp_ptr left, Oper oper, exp_ptr right);
        std::string to_string(Oper type);

        void accept(Visitor& v) override;

        Exp& left_get() const;
        void left_set(exp_ptr left);

        Oper oper_get() const;
        void oper_set(Oper oper);

        Exp& right_get() const;
        void right_set(exp_ptr right);

    private:
        exp_ptr left_;
        Oper oper_;
        exp_ptr right_;
    };

    class IntExp : public Exp
    {
    public:
        IntExp(const Location& location, int value);

        void accept(Visitor& v) override;

        int value_get() const;
        void value_set(int value);

    private:
        int value_;
    };

    class FloatExp : public Exp
    {
    public:
        FloatExp(const Location& location, float value);

        void accept(Visitor& v) override;

        float value_get() const;
        void value_set(float value);

    private:
        float value_;
    };

    class StringExp : public Exp
    {
    public:
        StringExp(const Location& location, std::string value);

        void accept(Visitor& v) override;

        const std::string& value_get() const;
        void value_set(std::string value);

    private:
        std::string value_;
    };

    class BoolExp : public Exp
    {
    public:
        BoolExp(const Location& location, bool value);

        void accept(Visitor& v) override;

        bool value_get() const;
        void value_set(bool value);

    private:
        bool value_;
    };

    class DollarsExp : public IntExp
    {
    public:
        DollarsExp(const Location& location, int value);

        void accept(Visitor& v) override;
    };

    class ChanceExp : public IntExp
    {
    public:
        ChanceExp(const Location& location, int value);

        void accept(Visitor& v) override;
    };

    class StreakExp : public IntExp
    {
    public:
        StreakExp(const Location& location, int value);

        void accept(Visitor& v) override;
    };

    class CallExp : public Exp
    {
    public:
        CallExp(const Location& location, std::string name,
                std::vector<exp_ptr> args);

        void accept(Visitor& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<exp_ptr>& args_get() const;
        std::vector<exp_ptr>& args_get();
        void args_set(std::vector<exp_ptr> args);

    private:
        std::string name_;
        std::vector<exp_ptr> args_;
    };

    class IdentExp : public Exp
    {
    public:
        IdentExp(const Location& location, std::string name);

        void accept(Visitor& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

    private:
        std::string name_;
    };

} // namespace ast
