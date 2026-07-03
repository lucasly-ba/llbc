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

        void visit(OpExp& node) override;
        void visit(IntLitExp& node) override;
        void visit(DollarsLitExp& node) override;
        void visit(StringLitExp& node) override;
        void visit(CallExp& node) override;
        void visit(IdentExp& node) override;
        void visit(BuiltinExp& node) override;

        void visit(LetStmt& node) override;
        void visit(IfStmt& node) override;
        void visit(LoopStmt& node) override;
        void visit(BreakStmt& node) override;
        void visit(ReturnStmt& node) override;
        void visit(MatchStmt& node) override;
        void visit(ExprStmt& node) override;
        void visit(BuiltinStmt& node) override;

        void visit(Type& node) override;

        void visit(StringPattern& node) override;
        void visit(WildcardPattern& node) override;
    };
} // namespace ast
