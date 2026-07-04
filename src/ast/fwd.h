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
    class IntLitExp;
    class StringLitExp;
    class BoolLitExp;
    class DollarsLitExp;
    class ChanceLitExp;
    class ReputationLitExp;
    class CallExp;
    class IdentExp;

    class Stmt;
    class LetStmt;
    class IfStmt;
    class LoopStmt;
    class BreakStmt;
    class ReturnStmt;
    class ExprStmt;

    class Type;

    class Visitor;

    using type_ptr = std::unique_ptr<Type>;
    using dec_ptr = std::unique_ptr<Dec>;
    using exp_ptr = std::unique_ptr<Exp>;
    using stmt_ptr = std::unique_ptr<Stmt>;

} // namespace ast
