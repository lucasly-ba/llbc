#pragma once
#include <ast/exp.h>
#include <ast/type.h>
#include <gbir/inst/inst.h>
#include <gbir/value.h>

namespace gbir
{
    class BinopInst : public GbirInst
    {
    public:
        BinopInst(GbirValue left, ast::OpExp::Oper oper, GbirValue right,
                  GbirValue result);

        void accept(GbirVisitorBase& v) override;

        GbirValue left_get() const;
        void left_set(GbirValue left);

        ast::OpExp::Oper oper_get() const;
        void oper_set(ast::OpExp::Oper oper);

        GbirValue right_get() const;
        void right_set(GbirValue right);

        GbirValue result_get() const;
        void result_set(GbirValue result);

    private:
        GbirValue left_;
        ast::OpExp::Oper oper_;
        GbirValue right_;
        GbirValue result_;
    };

} // namespace gbir
