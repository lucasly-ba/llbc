#pragma once
#include <ast/fwd.h>

namespace ast
{
    class Visitor
    {
    public:
        virtual ~Visitor() = default;

        virtual void visit(VarDec& node) = 0;
        virtual void visit(FuncDec& node) = 0;
        virtual void visit(SceneDec& node) = 0;

        virtual void visit(OpExp& node) = 0;
        virtual void visit(IntLitExp& node) = 0;
        virtual void visit(DollarsLitExp& node) = 0;
        virtual void visit(StringLitExp& node) = 0;
        virtual void visit(CallExp& node) = 0;
        virtual void visit(IdentExp& node) = 0;
        virtual void visit(BuiltinExp& node) = 0;

        virtual void visit(LetStmt& node) = 0;
        virtual void visit(IfStmt& node) = 0;
        virtual void visit(LoopStmt& node) = 0;
        virtual void visit(BreakStmt& node) = 0;
        virtual void visit(ReturnStmt& node) = 0;
        virtual void visit(MatchStmt& node) = 0;
        virtual void visit(ExprStmt& node) = 0;
        virtual void visit(BuiltinStmt& node) = 0;

        virtual void visit(Type& node) = 0;

        virtual void visit(StringPattern& node) = 0;
        virtual void visit(WildcardPattern& node) = 0;
    };
} // namespace ast
