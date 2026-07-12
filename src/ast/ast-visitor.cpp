#include <ast/ast-visitor.h>

namespace ast
{
    void Visitor::visit(VarDec& e)
    {
        if (auto init = e.init_get())
            init->accept(*this);
    }

    void Visitor::visit(FuncDec& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void Visitor::visit(SceneDec& e)
    {
        if (auto precond = e.precondition_get())
            precond->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void Visitor::visit(PlayerDec& e)
    {
        e.dollar_get().accept(*this);
        e.chance_get().accept(*this);
        e.streak_get().accept(*this);
    }

    void Visitor::visit(OpExp& e)
    {
        e.left_get().accept(*this);
        e.right_get().accept(*this);
    }

    void Visitor::visit(IntExp& e)
    {
        (void)e;
    }

    void Visitor::visit(FloatExp& e)
    {
        (void)e;
    }
    void Visitor::visit(StringExp& e)
    {
        (void)e;
    }
    void Visitor::visit(BoolExp& e)
    {
        (void)e;
    }
    void Visitor::visit(DollarsExp& e)
    {
        (void)e;
    }
    void Visitor::visit(ChanceExp& e)
    {
        (void)e;
    }
    void Visitor::visit(StreakExp& e)
    {
        (void)e;
    }

    void Visitor::visit(CallExp& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
    }

    void Visitor::visit(IdentExp& e)
    {
        (void)e;
    }
    void Visitor::visit(VarStmt& e)
    {
        e.vardec_get().accept(*this);
    }

    void Visitor::visit(AssignStmt& e)
    {
        e.value_get().accept(*this);
    }

    void Visitor::visit(IfStmt& e)
    {
        e.condition_get().accept(*this);
        for (auto& stmt : e.then_branch_get())
            stmt->accept(*this);
        for (auto& stmt : e.else_branch_get())
            stmt->accept(*this);
    }

    void Visitor::visit(LoopStmt& e)
    {
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void Visitor::visit(BreakStmt& e)
    {
        (void)e;
    }

    void Visitor::visit(ReturnStmt& e)
    {
        if (auto value = e.value_get())
            value->accept(*this);
    }

    void Visitor::visit(EntersStmt& e)
    {
        (void)e;
    }

    void Visitor::visit(StartStmt& e)
    {
        (void)e;
    }

    void Visitor::visit(ExpStmt& e)
    {
        e.exp_get().accept(*this);
    }

} // namespace ast
