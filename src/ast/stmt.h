#pragma once
#include <ast/ast.h>
#include <string>
#include <vector>

namespace ast
{
    class Stmt : public Ast
    {
    public:
        explicit Stmt(const Location& location);
    };

    class VarStmt : public Stmt
    {
    public:
        VarStmt(const Location& location, std::unique_ptr<VarDec> vardec);

        void accept(AstVisitorBase& v) override;

        VarDec& vardec_get() const;
        void vardec_set(std::unique_ptr<VarDec> vardec);

    private:
        std::unique_ptr<VarDec> vardec_;
    };

    class AssignStmt : public Stmt
    {
    public:
        AssignStmt(const Location& location, std::string name, exp_ptr value);

        void accept(AstVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        Exp& value_get() const;
        void value_set(exp_ptr value);

        Dec* def_get() const;
        void def_set(Dec* def);

    private:
        Dec* def_ = nullptr;
        std::string name_;
        exp_ptr value_;
    };

    class IfStmt : public Stmt
    {
    public:
        IfStmt(const Location& location, exp_ptr condition,
               std::vector<stmt_ptr> then_branch,
               std::vector<stmt_ptr> else_branch);

        IfStmt(const Location& location, exp_ptr condition,
               std::vector<stmt_ptr> then_branch);

        void accept(AstVisitorBase& v) override;

        Exp& condition_get() const;
        void condition_set(exp_ptr condition);

        const std::vector<stmt_ptr>& then_branch_get() const;
        std::vector<stmt_ptr>& then_branch_get();
        void then_branch_set(std::vector<stmt_ptr> then_branch);

        const std::vector<stmt_ptr>& else_branch_get() const;
        std::vector<stmt_ptr>& else_branch_get();
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

        void accept(AstVisitorBase& v) override;

        const std::vector<stmt_ptr>& body_get() const;
        void body_set(std::vector<stmt_ptr> body);

    private:
        std::vector<stmt_ptr> body_;
    };

    class BreakStmt : public Stmt
    {
    public:
        explicit BreakStmt(const Location& location);

        void accept(AstVisitorBase& v) override;
    };

    class ReturnStmt : public Stmt
    {
    public:
        ReturnStmt(const Location& location, exp_ptr value);
        ReturnStmt(const Location& location);

        void accept(AstVisitorBase& v) override;

        Exp* value_get() const;
        void value_set(exp_ptr value);

        bool has_value() const;

    private:
        exp_ptr value_;
    };

    class EntersStmt : public Stmt
    {
    public:
        EntersStmt(const Location& location, std::string player_name,
                   std::string scene_name);

        void accept(AstVisitorBase& v) override;

        const std::string& player_name_get() const;
        void player_name_set(std::string name);

        const std::string& scene_name_get() const;
        void scene_name_set(std::string name);

        Dec* player_def_get() const;
        void player_def_set(Dec* player_def);

        Dec* scene_def_get() const;
        void scene_def_set(Dec* scene_def);

    private:
        Dec* player_def_ = nullptr;
        Dec* scene_def_ = nullptr;
        std::string player_name_;
        std::string scene_name_;
    };

    class StartStmt : public Stmt
    {
    public:
        StartStmt(const Location& location, std::string scene_name);

        void accept(AstVisitorBase& v) override;

        const std::string& scene_name_get() const;
        void scene_name_set(std::string name);

        Dec* scene_def_get() const;
        void scene_def_set(Dec* scene_def);

    private:
        Dec* scene_def_ = nullptr;
        std::string scene_name_;
    };

    class ExpStmt : public Stmt
    {
    public:
        ExpStmt(const Location& location, exp_ptr exp);

        void accept(AstVisitorBase& v) override;

        Exp& exp_get() const;
        void exp_set(exp_ptr exp);

    private:
        exp_ptr exp_;
    };

} // namespace ast
