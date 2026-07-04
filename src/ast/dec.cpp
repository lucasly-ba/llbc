#include <ast/dec.h>
#include <ast/exp.h>
#include <ast/stmt.h>
#include <ast/type.h>
#include <ast/visitor.h>

namespace ast
{
    Dec::Dec(const Location& location, std::string name)
        : Ast(location)
        , name_(std::move(name))
    {}

    std::string Dec::name_get() const
    {
        return name_;
    }

    void Dec::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    VarDec::VarDec(const Location& location, std::string name, Type type,
                   exp_ptr init)
        : Dec(location, std::move(name))
        , type_(type)
        , init_(std::move(init))
    {}

    VarDec::VarDec(const Location& location, std::string name, exp_ptr init)
        : Dec(location, std::move(name))
        , type_(std::nullopt)
        , init_(std::move(init))
    {}

    void VarDec::accept(Visitor& v)
    {
        v.visit(*this);
    }

    std::optional<Type> VarDec::type_get() const
    {
        return type_;
    }

    void VarDec::type_set(Type type)
    {
        type_ = type;
    }

    Exp* VarDec::init_get() const
    {
        return init_.get();
    }

    void VarDec::init_set(exp_ptr init)
    {
        init_ = std::move(init);
    }

    FuncDec::FuncDec(const Location& location, std::string name,
                     std::vector<std::unique_ptr<VarDec>> args, Type type,
                     std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , args_(std::move(args))
        , type_(type)
        , body_(std::move(body))
    {}

    FuncDec::FuncDec(const Location& location, std::string name,
                     std::vector<std::unique_ptr<VarDec>> args,
                     std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , args_(std::move(args))
        , type_(std::nullopt)
        , body_(std::move(body))
    {}

    void FuncDec::accept(Visitor& v)
    {
        v.visit(*this);
    }

    const std::vector<std::unique_ptr<VarDec>>& FuncDec::args_get() const
    {
        return args_;
    }

    std::vector<std::unique_ptr<VarDec>>& FuncDec::args_get()
    {
        return args_;
    }

    void FuncDec::args_set(std::vector<std::unique_ptr<VarDec>> args)
    {
        args_ = std::move(args);
    }

    std::optional<Type> FuncDec::type_get() const
    {
        return type_;
    }

    void FuncDec::type_set(Type type)
    {
        type_ = type;
    }

    const std::vector<stmt_ptr>& FuncDec::body_get() const
    {
        return body_;
    }

    std::vector<stmt_ptr>& FuncDec::body_get()
    {
        return body_;
    }

    void FuncDec::body_set(std::vector<stmt_ptr> body)
    {
        body_ = std::move(body);
    }

    SceneDec::SceneDec(const Location& location, std::string name,
                       std::optional<int> max_players, exp_ptr precondition,
                       std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , max_players_(max_players)
        , precondition_(std::move(precondition))
        , body_(std::move(body))
    {}

    SceneDec::SceneDec(const Location& location, std::string name,
                       exp_ptr precondition, std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , max_players_(std::nullopt)
        , precondition_(std::move(precondition))
        , body_(std::move(body))
    {}

    SceneDec::SceneDec(const Location& location, std::string name,
                       std::optional<int> max_players,
                       std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , max_players_(max_players)
        , precondition_(nullptr)
        , body_(std::move(body))
    {}

    SceneDec::SceneDec(const Location& location, std::string name,
                       std::vector<stmt_ptr> body)
        : Dec(location, std::move(name))
        , max_players_(std::nullopt)
        , precondition_(nullptr)
        , body_(std::move(body))
    {}

    void SceneDec::accept(Visitor& v)
    {
        v.visit(*this);
    }

    std::optional<int> SceneDec::max_players_get() const
    {
        return max_players_;
    }

    void SceneDec::max_players_set(std::optional<int> max_players)
    {
        max_players_ = max_players;
    }

    Exp* SceneDec::precondition_get() const
    {
        return precondition_.get();
    }

    void SceneDec::precondition_set(exp_ptr precondition)
    {
        precondition_ = std::move(precondition);
    }

    const std::vector<stmt_ptr>& SceneDec::body_get() const
    {
        return body_;
    }

    std::vector<stmt_ptr>& SceneDec::body_get()
    {
        return body_;
    }

    void SceneDec::body_set(std::vector<stmt_ptr> body)
    {
        body_ = std::move(body);
    }

    PlayerDec::PlayerDec(const Location& location, std::string name,
                         exp_ptr dollar, exp_ptr chance, exp_ptr reputation)
        : Dec(location, std::move(name))
        , dollar_(std::move(dollar))
        , chance_(std::move(chance))
        , reputation_(std::move(reputation))
    {}

    void PlayerDec::accept(Visitor& v)
    {
        v.visit(*this);
    }

    Exp& PlayerDec::dollar_get() const
    {
        return *dollar_;
    }

    void PlayerDec::dollar_set(exp_ptr dollar)
    {
        dollar_ = std::move(dollar);
    }

    Exp& PlayerDec::chance_get() const
    {
        return *chance_;
    }

    void PlayerDec::chance_set(exp_ptr chance)
    {
        chance_ = std::move(chance);
    }

    Exp& PlayerDec::reputation_get() const
    {
        return *reputation_;
    }

    void PlayerDec::reputation_set(exp_ptr reputation)
    {
        reputation_ = std::move(reputation);
    }
} // namespace ast
