#pragma once

#include <ast/all.h>
#include <ast/ast-visitor.h>
#include <bind/scope.h>

namespace bind
{
    using namespace ast;

    struct BindError
    {
        std::string message;
        Location location;
    };

    class Binder : public AstVisitor
    {
    public:
        Binder() = default;
        void bind_program(ast::Program& program);
        const std::vector<BindError>& get_errors() const;
        bool has_error() const;

    private:
        void visit(VarDec& e) override;
        void visit(FuncDec& e) override;
        void visit(SceneDec& e) override;

        void visit(CallExp& e) override;
        void visit(IdentExp& e) override;

        void visit(AssignStmt& e) override;
        void visit(LoopStmt& e) override;
        void visit(BreakStmt& e) override;
        void visit(EntersStmt& e) override;
        void visit(StartStmt& e) override;
        void visit(ReturnStmt& e) override;

        void emit_error(const std::string& message, Location loc);

    private:
        bool has_main_ = false;
        LoopStmt* loop_ = nullptr;
        FuncDec* func_ = nullptr;
        Scope scope_;
        std::vector<BindError> errors_;
    };

} // namespace bind
