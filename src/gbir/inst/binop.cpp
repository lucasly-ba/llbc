#include <gbir/inst/binop.h>

namespace gbir
{
    BinopInst::BinopInst(GbirValue left, ast::OpExp::Oper oper, GbirValue right,
                         GbirValue result)
        : left_(left)
        , oper_(oper)
        , right_(right)
        , result_(result)
    {}

    void BinopInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue BinopInst::left_get() const
    {
        return left_;
    }

    void BinopInst::left_set(GbirValue left)
    {
        left_ = left;
    }

    ast::OpExp::Oper BinopInst::oper_get() const
    {
        return oper_;
    }

    void BinopInst::oper_set(ast::OpExp::Oper oper)
    {
        oper_ = oper;
    }

    GbirValue BinopInst::right_get() const
    {
        return right_;
    }

    void BinopInst::right_set(GbirValue right)
    {
        right_ = right;
    }

    GbirValue BinopInst::result_get() const
    {
        return result_;
    }

    void BinopInst::result_set(GbirValue result)
    {
        result_ = result;
    }
} // namespace gbir
