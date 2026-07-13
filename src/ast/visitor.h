#pragma once
#include <ast/all.h>

namespace ast
{
    class AstVisitorBase
    {
    public:
        virtual ~AstVisitorBase() = default;

        virtual void visit(VarDec& e) = 0;
        virtual void visit(FuncDec& e) = 0;
        virtual void visit(SceneDec& e) = 0;
        virtual void visit(PlayerDec& e) = 0;

        virtual void visit(OpExp& e) = 0;
        virtual void visit(IntExp& e) = 0;
        virtual void visit(FloatExp& e) = 0;
        virtual void visit(StringExp& e) = 0;
        virtual void visit(BoolExp& e) = 0;
        virtual void visit(DollarsExp& e) = 0;
        virtual void visit(ChanceExp& e) = 0;
        virtual void visit(StreakExp& e) = 0;
        virtual void visit(CallExp& e) = 0;
        virtual void visit(IdentExp& e) = 0;

        virtual void visit(VarStmt& e) = 0;
        virtual void visit(AssignStmt& e) = 0;
        virtual void visit(IfStmt& e) = 0;
        virtual void visit(LoopStmt& e) = 0;
        virtual void visit(BreakStmt& e) = 0;
        virtual void visit(ReturnStmt& e) = 0;
        virtual void visit(EntersStmt& e) = 0;
        virtual void visit(StartStmt& e) = 0;
        virtual void visit(ExpStmt& e) = 0;
    };
} // namespace ast
