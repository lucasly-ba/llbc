#pragma once
#include <ast/visitor.h>

namespace ast
{
    class DefaultVisitor : Visitor
    {
    public:
        void visit(VarDec& node) override;
        void visit(FuncDec& node) override;
        void visit(SceneDec& node) override;
        void visit(PlayerDec& node) override;

        void visit(OpExp& node) override;
        void visit(IntExp& node) override;
        void visit(FloatExp& node) override;
        void visit(StringExp& node) override;
        void visit(BoolExp& node) override;
        void visit(DollarsExp& node) override;
        void visit(ChanceExp& node) override;
        void visit(ReputationExp& node) override;
        void visit(CallExp& node) override;
        void visit(IdentExp& node) override;

        void visit(VarStmt& node) override;
        void visit(IfStmt& node) override;
        void visit(LoopStmt& node) override;
        void visit(BreakStmt& node) override;
        void visit(ReturnStmt& node) override;
        void visit(ExpStmt& node) override;
    };
} // namespace ast
