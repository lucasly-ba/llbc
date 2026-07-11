#include <dec.h>
#include <exp.h>
#include <stmt.h>
#include <type.h>
#include <visitor.h>

namespace ast
{
    Stmt::Stmt(const Location& location)
        : Ast(location)
    {}

    VarStmt::VarStmt(const Location& location, std::unique_ptr<VarDec> vardec)
        : Stmt(location)
        , vardec_(std::move(vardec))
    {}

    void VarStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    VarDec& VarStmt::vardec_get() const
    {
        return *vardec_;
    }

    void VarStmt::vardec_set(std::unique_ptr<VarDec> vardec)
    {
        vardec_ = std::move(vardec);
    }

    IfStmt::IfStmt(const Location& location, exp_ptr condition,
                   std::vector<stmt_ptr> then_branch,
                   std::vector<stmt_ptr> else_branch)
        : Stmt(location)
        , condition_(std::move(condition))
        , then_branch_(std::move(then_branch))
        , else_branch_(std::move(else_branch))
    {}

    IfStmt::IfStmt(const Location& location, exp_ptr condition,
                   std::vector<stmt_ptr> then_branch)
        : Stmt(location)
        , condition_(std::move(condition))
        , then_branch_(std::move(then_branch))
        , else_branch_()
    {}

    void IfStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    Exp& IfStmt::condition_get() const
    {
        return *condition_;
    }

    void IfStmt::condition_set(exp_ptr condition)
    {
        condition_ = std::move(condition);
    }

    const std::vector<stmt_ptr>& IfStmt::then_branch_get() const
    {
        return then_branch_;
    }

    std::vector<stmt_ptr>& IfStmt::then_branch_get()
    {
        return then_branch_;
    }

    void IfStmt::then_branch_set(std::vector<stmt_ptr> then_branch)
    {
        then_branch_ = std::move(then_branch);
    }

    const std::vector<stmt_ptr>& IfStmt::else_branch_get() const
    {
        return else_branch_;
    }

    std::vector<stmt_ptr>& IfStmt::else_branch_get()
    {
        return else_branch_;
    }

    void IfStmt::else_branch_set(std::vector<stmt_ptr> else_branch)
    {
        else_branch_ = std::move(else_branch);
    }

    LoopStmt::LoopStmt(const Location& location, std::vector<stmt_ptr> body)
        : Stmt(location)
        , body_(std::move(body))
    {}

    void LoopStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    const std::vector<stmt_ptr>& LoopStmt::body_get() const
    {
        return body_;
    }

    void LoopStmt::body_set(std::vector<stmt_ptr> body)
    {
        body_ = std::move(body);
    }

    BreakStmt::BreakStmt(const Location& location)
        : Stmt(location)
    {}

    void BreakStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    ReturnStmt::ReturnStmt(const Location& location, exp_ptr value)
        : Stmt(location)
        , value_(std::move(value))
    {}

    ReturnStmt::ReturnStmt(const Location& location)
        : Stmt(location)
        , value_(nullptr)
    {}

    void ReturnStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    Exp* ReturnStmt::value_get() const
    {
        return value_.get();
    }

    void ReturnStmt::value_set(exp_ptr value)
    {
        value_ = std::move(value);
    }

    bool ReturnStmt::has_value() const
    {
        return value_ != nullptr;
    }

    EntersStmt::EntersStmt(const Location& location, std::string player_name,
                           std::string scene_name)
        : Stmt(location)
        , player_name_(std::move(player_name))
        , scene_name_(std::move(scene_name))
    {}

    void EntersStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    const std::string& EntersStmt::player_name_get() const
    {
        return player_name_;
    }

    void EntersStmt::player_name_set(std::string player_name)
    {
        player_name_ = player_name;
    }

    const std::string& EntersStmt::scene_name_get() const
    {
        return scene_name_;
    }

    void EntersStmt::scene_name_set(std::string scene_name)
    {
        scene_name_ = scene_name;
    }

    Dec* EntersStmt::player_def_get() const
    {
        return player_def_;
    }

    void EntersStmt::player_def_set(Dec* player_def)
    {
        player_def_ = player_def;
    }

    Dec* EntersStmt::scene_def_get() const
    {
        return scene_def_;
    }

    void EntersStmt::scene_def_set(Dec* scene_def)
    {
        scene_def_ = scene_def;
    }

    StartStmt::StartStmt(const Location& location, std::string scene_name)
        : Stmt(location)
        , scene_name_(std::move(scene_name))
    {}

    void StartStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    void StartStmt::scene_name_set(std::string scene_name)
    {
        scene_name_ = scene_name;
    }

    const std::string& StartStmt::scene_name_get() const
    {
        return scene_name_;
    }

    Dec* StartStmt::scene_def_get() const
    {
        return scene_def_;
    }

    void StartStmt::scene_def_set(Dec* scene_def)
    {
        scene_def_ = scene_def;
    }

    ExpStmt::ExpStmt(const Location& location, exp_ptr exp)
        : Stmt(location)
        , exp_(std::move(exp))
    {}

    void ExpStmt::accept(Visitor& v)
    {
        v.visit(*this);
    }

    Exp& ExpStmt::exp_get() const
    {
        return *exp_;
    }

    void ExpStmt::exp_set(exp_ptr exp)
    {
        exp_ = std::move(exp);
    }
} // namespace ast
