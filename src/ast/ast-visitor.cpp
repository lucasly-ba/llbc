#include <ast/ast-visitor.h>

namespace ast
{
    void AstVisitor::visit(VarDec& e)
    {
        if (auto init = e.init_get())
            init->accept(*this);
    }

    void AstVisitor::visit(FuncDec& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void AstVisitor::visit(SceneDec& e)
    {
        if (auto precond = e.precondition_get())
            precond->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void AstVisitor::visit(PlayerDec& e)
    {
        e.dollar_get().accept(*this);
        e.chance_get().accept(*this);
        e.streak_get().accept(*this);
    }

    void AstVisitor::visit(OpExp& e)
    {
        e.left_get().accept(*this);
        e.right_get().accept(*this);
    }

    void AstVisitor::visit(IntExp& e)
    {
        (void)e;
    }

    void AstVisitor::visit(FloatExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(StringExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(BoolExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(DollarsExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(ChanceExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(StreakExp& e)
    {
        (void)e;
    }

    void AstVisitor::visit(CallExp& e)
    {
        for (auto& arg : e.args_get())
            arg->accept(*this);
    }

    void AstVisitor::visit(IdentExp& e)
    {
        (void)e;
    }
    void AstVisitor::visit(VarStmt& e)
    {
        e.vardec_get().accept(*this);
    }

    void AstVisitor::visit(AssignStmt& e)
    {
        e.value_get().accept(*this);
    }

    void AstVisitor::visit(IfStmt& e)
    {
        e.condition_get().accept(*this);
        for (auto& stmt : e.then_branch_get())
            stmt->accept(*this);
        for (auto& stmt : e.else_branch_get())
            stmt->accept(*this);
    }

    void AstVisitor::visit(LoopStmt& e)
    {
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void AstVisitor::visit(BreakStmt& e)
    {
        (void)e;
    }

    void AstVisitor::visit(ReturnStmt& e)
    {
        if (auto value = e.value_get())
            value->accept(*this);
    }

    void AstVisitor::visit(EntersStmt& e)
    {
        (void)e;
    }

    void AstVisitor::visit(StartStmt& e)
    {
        (void)e;
    }

    void AstVisitor::visit(ExpStmt& e)
    {
        e.exp_get().accept(*this);
    }

} // namespace ast
