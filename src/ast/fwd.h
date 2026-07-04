#pragma once
#include <memory>

namespace ast
{
    class Ast;

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
    class DollarExp;
    class ChanceExp;
    class ReputationExp;
    class CallExp;
    class IdentExp;

    class Stmt;
    class LetStmt;
    class IfStmt;
    class LoopStmt;
    class BreakStmt;
    class ReturnStmt;
    class ExpStmt;

    class Visitor;

    using dec_ptr = std::unique_ptr<Dec>;
    using exp_ptr = std::unique_ptr<Exp>;
    using stmt_ptr = std::unique_ptr<Stmt>;

} // namespace ast
