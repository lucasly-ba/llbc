#pragma once
#include <memory>

namespace ast
{
    class Ast;
    class Program;

    class Dec;
    class VarDec;
    class FuncDec;
    class SceneDec;
    class PlayerDec;

    class Exp;
    class OpExp;
    class IntExp;
    class FloatExp;
    class StringExp;
    class BoolExp;
    class DollarsExp;
    class ChanceExp;
    class StreakExp;
    class CallExp;
    class IdentExp;

    class Stmt;
    class VarStmt;
    class AssignStmt;
    class IfStmt;
    class LoopStmt;
    class BreakStmt;
    class ReturnStmt;
    class EntersStmt;
    class StartStmt;
    class ExpStmt;

    class Visitor;

    using dec_ptr = std::unique_ptr<Dec>;
    using exp_ptr = std::unique_ptr<Exp>;
    using stmt_ptr = std::unique_ptr<Stmt>;

} // namespace ast
