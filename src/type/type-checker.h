#pragma once

#include <all.h>
#include <main-visitor.h>

namespace type
{
    using namespace ast;

    struct TypeError
    {
        std::string message;
        Location location;
    };

    class TypeChecker : public MainVisitor
    {
    public:
        TypeChecker() = default;
        void typecheck_program(ast::Program& program);
        const std::vector<TypeError>& get_errors() const;
        bool has_error() const;

    private:
        void visit(VarDec& e) override;
        bool has_break(const std::vector<stmt_ptr>& stmts);
        bool check_for_return(const std::vector<stmt_ptr>& stmts);
        void visit(FuncDec& e) override;
        void visit(SceneDec& e) override;

        void visit(OpExp& e) override;
        void visit(IntExp& e) override;
        void visit(FloatExp& e) override;
        void visit(StringExp& e) override;
        void visit(BoolExp& e) override;
        void visit(DollarsExp& e) override;
        void visit(ChanceExp& e) override;
        void visit(StreakExp& e) override;
        void visit(CallExp& e) override;
        void visit(IdentExp& e) override;

        void visit(IfStmt& e) override;
        void visit(ReturnStmt& e) override;

    private:
        void emit_error(const std::string& message, Location loc);

    private:
        Type current_type_;
        Type current_return_type_ = Type::Void;
        std::vector<TypeError> errors_;
    };

} // namespace type
