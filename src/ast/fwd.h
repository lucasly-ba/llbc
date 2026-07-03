#pragma once
#include <memory>

namespace ast
{
    class Ast;

    class Dec;
    class VarDec;
    class FuncDec;
    class SceneDec;

    class Exp;
    class OpExp;
    class IntLitExp;
    class DollarsLitExp;
    class StringLitExp;
    class CallExp;
    class IdentExp;
    class BuiltinExp;

    class Stmt;
    class LetStmt;
    class IfStmt;
    class LoopStmt;
    class BreakStmt;
    class ReturnStmt;
    class MatchStmt;
    class ExprStmt;
    class BuiltinStmt;

    class Pattern;
    class StringPattern;
    class WildcardPattern;

    class Type;

    class Visitor;

    using type_ptr = std::unique_ptr<Type>;
    using dec_ptr = std::unique_ptr<Dec>;
    using exp_ptr = std::unique_ptr<Exp>;
    using stmt_ptr = std::unique_ptr<Stmt>;
    using pattern_ptr = std::unique_ptr<Pattern>;

} // namespace ast
