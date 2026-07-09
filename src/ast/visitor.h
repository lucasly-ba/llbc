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
        virtual void visit(PlayerDec& node) = 0;

        virtual void visit(OpExp& node) = 0;
        virtual void visit(IntExp& node) = 0;
        virtual void visit(FloatExp& node) = 0;
        virtual void visit(StringExp& node) = 0;
        virtual void visit(BoolExp& node) = 0;
        virtual void visit(DollarsExp& node) = 0;
        virtual void visit(ChanceExp& node) = 0;
        virtual void visit(StreakExp& node) = 0;
        virtual void visit(CallExp& node) = 0;
        virtual void visit(IdentExp& node) = 0;

        virtual void visit(VarStmt& node) = 0;
        virtual void visit(IfStmt& node) = 0;
        virtual void visit(LoopStmt& node) = 0;
        virtual void visit(BreakStmt& node) = 0;
        virtual void visit(ReturnStmt& node) = 0;
        virtual void visit(EntersStmt& node) = 0;
        virtual void visit(StartStmt& node) = 0;
        virtual void visit(ExpStmt& node) = 0;
    };
} // namespace ast
