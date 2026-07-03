#include <ast/all.h>
#include <ast/default-visitor.h>

namespace ast
{
    void DefaultVisitor::visit(VarDec& node)
    {}

    void DefaultVisitor::visit(FuncDec& node)
    {}

    void DefaultVisitor::visit(SceneDec& node)
    {}

    void DefaultVisitor::visit(OpExp& node)
    {}

    void DefaultVisitor::visit(IntLitExp& node)
    {}

    void DefaultVisitor::visit(DollarsLitExp& node)
    {}

    void DefaultVisitor::visit(StringLitExp& node)
    {}

    void DefaultVisitor::visit(CallExp& node)
    {}

    void DefaultVisitor::visit(IdentExp& node)
    {}

    void DefaultVisitor::visit(BuiltinExp& node)
    {}

    void DefaultVisitor::visit(LetStmt& node)
    {}

    void DefaultVisitor::visit(IfStmt& node)
    {}

    void DefaultVisitor::visit(LoopStmt& node)
    {}

    void DefaultVisitor::visit(BreakStmt& node)
    {}

    void DefaultVisitor::visit(ReturnStmt& node)
    {}

    void DefaultVisitor::visit(MatchStmt& node)
    {}

    void DefaultVisitor::visit(ExprStmt& node)
    {}

    void DefaultVisitor::visit(BuiltinStmt& node)
    {}

    void DefaultVisitor::visit(Type& node)
    {}

    void DefaultVisitor::visit(StringPattern& node)
    {}

    void DefaultVisitor::visit(WildcardPattern& node)
    {}
} // namespace ast
