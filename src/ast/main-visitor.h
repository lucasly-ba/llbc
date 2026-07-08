#pragma once
#include <ast/visitor.h>

namespace ast
{
    class MainVisitor : public Visitor
    {
    public:
        void visit(VarDec& e) override;
        void visit(FuncDec& e) override;
        void visit(SceneDec& e) override;
        void visit(PlayerDec& e) override;

        void visit(OpExp& e) override;
        void visit(IntExp& e) override;
        void visit(FloatExp& e) override;
        void visit(StringExp& e) override;
        void visit(BoolExp& e) override;
        void visit(DollarsExp& e) override;
        void visit(ChanceExp& e) override;
        void visit(StreakExp& e) override;
        void visit(CallExp& e) override;
        void visit(IdentExp& e) override;

        void visit(VarStmt& e) override;
        void visit(IfStmt& e) override;
        void visit(LoopStmt& e) override;
        void visit(BreakStmt& e) override;
        void visit(ReturnStmt& e) override;
        void visit(ExpStmt& e) override;
    };
} // namespace ast
