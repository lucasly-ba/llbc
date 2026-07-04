#pragma once
#include <ast/ast.h>
#include <ast/fwd.h>
#include <vector>

namespace ast
{
    class Stmt : public Ast
    {
    public:
        explicit Stmt(const Location& location);
    };

    class LetStmt : public Stmt
    {
    public:
        LetStmt(const Location& location, std::unique_ptr<VarDec> vardec);

        VarDec& vardec_get() const;
        void vardec_set(std::unique_ptr<VarDec> vardec);

    private:
        std::unique_ptr<VarDec> vardec_;
    };

    class IfStmt : public Stmt
    {
    public:
        IfStmt(const Location& location, exp_ptr condition,
               std::vector<stmt_ptr> then_branch,
               std::vector<stmt_ptr> else_branch);

        IfStmt(const Location& location, exp_ptr condition,
               std::vector<stmt_ptr> then_branch);

        Exp& condition_get() const;
        void condition_set(exp_ptr condition);

        const std::vector<stmt_ptr>& then_branch_get() const;
        void then_branch_set(std::vector<stmt_ptr> then_branch);

        const std::vector<stmt_ptr>& else_branch_get() const;
        void else_branch_set(std::vector<stmt_ptr> else_branch);

    private:
        exp_ptr condition_;
        std::vector<stmt_ptr> then_branch_;
        std::vector<stmt_ptr> else_branch_;
    };

    class LoopStmt : public Stmt
    {
    public:
        LoopStmt(const Location& location, std::vector<stmt_ptr> body);

        const std::vector<stmt_ptr>& body_get() const;
        void body_set(std::vector<stmt_ptr> body);

    private:
        std::vector<stmt_ptr> body_;
    };

    class BreakStmt : public Stmt
    {
    public:
        explicit BreakStmt(const Location& location);
    };

    class ReturnStmt : public Stmt
    {
    public:
        ReturnStmt(const Location& location, exp_ptr value);
        ReturnStmt(const Location& location);

        Exp* value_get() const;
        void value_set(exp_ptr value);

    private:
        exp_ptr value_;
    };

    class ExpStmt : public Stmt
    {
    public:
        ExpStmt(const Location& location, exp_ptr exp);

        Exp& exp_get() const;

    private:
        exp_ptr exp_;
    };

} // namespace ast
