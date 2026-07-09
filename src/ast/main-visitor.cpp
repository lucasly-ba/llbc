#include <ast/all.h>
#include <ast/main-visitor.h>

#include "exp.h"
#include "stmt.h"

namespace ast
{
    void MainVisitor::visit(VarDec& e)
    {
        if (auto init = e.init_get())
            init->accept(*this);
    }

    void MainVisitor::visit(FuncDec& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void MainVisitor::visit(SceneDec& e)
    {
        if (auto precond = e.precondition_get())
            precond->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void MainVisitor::visit(PlayerDec& e)
    {
        e.dollar_get().accept(*this);
        e.chance_get().accept(*this);
        e.streak_get().accept(*this);
    }

    void MainVisitor::visit(OpExp& e)
    {
        e.left_get().accept(*this);
        e.right_get().accept(*this);
    }

    void MainVisitor::visit(IntExp& e)
    {
        (void)e;
    }

    void MainVisitor::visit(FloatExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(StringExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(BoolExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(DollarsExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(ChanceExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(StreakExp& e)
    {
        (void)e;
    }

    void MainVisitor::visit(CallExp& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
    }

    void MainVisitor::visit(IdentExp& e)
    {
        (void)e;
    }
    void MainVisitor::visit(VarStmt& e)
    {
        e.vardec_get().accept(*this);
    }

    void MainVisitor::visit(IfStmt& e)
    {
        e.condition_get().accept(*this);
        for (auto& stmt : e.then_branch_get())
            stmt->accept(*this);
        for (auto& stmt : e.else_branch_get())
            stmt->accept(*this);
    }

    void MainVisitor::visit(LoopStmt& e)
    {
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void MainVisitor::visit(BreakStmt& e)
    {
        (void)e;
    }

    void MainVisitor::visit(ReturnStmt& e)
    {
        if (auto value = e.value_get())
            value->accept(*this);
    }

    void MainVisitor::visit(EntersStmt& e)
    {
        (void)e;
    }

    void MainVisitor::visit(StartStmt& e)
    {
        (void)e;
    }

    void MainVisitor::visit(ExpStmt& e)
    {
        e.exp_get().accept(*this);
    }

} // namespace ast
