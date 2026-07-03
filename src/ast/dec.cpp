#include <ast/dec.h>

namespace ast
{
    Dec::Dec(const Location& location, std::string name)
        : Ast(location)
        , name_(name)
    {}

    std::string Dec::name_get() const
    {
        return name_;
    }

    void Dec::name_set(std::string name)
    {
        name_ = name;
    }

    VarDec::VarDec(const Location& location, std::string name, type_ptr type,
                   exp_ptr init)
        : Dec(location, name)
        , type_(std::move(type))
        , init_(std::move(init))
    {}

    VarDec::VarDec(const Location& location, std::string name, exp_ptr init)
        : Dec(location, name)
        , type_(nullptr)
        , init_(std::move(init))
    {}

    Type* VarDec::type_get() const
    {
        return type_.get();
    }
    void VarDec::type_set(type_ptr type)
    {
        type_ = std::move(type);
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
                     std::vector<std::unique_ptr<VarDec>> params, type_ptr type,
                     std::vector<stmt_ptr> body)
        : Dec(location, name)
        , params_(std::move(params))
        , type_(std::move(type))
        , body_(std::move(body))
    {}

    FuncDec::FuncDec(const Location& location, std::string name,
                     std::vector<std::unique_ptr<VarDec>> params,
                     std::vector<stmt_ptr> body)
        : Dec(location, name)
        , params_(std::move(params))
        , type_(nullptr)
        , body_(std::move(body))

    {}

    const std::vector<std::unique_ptr<VarDec>>& FuncDec::params_get() const
    {
        return params_;
    }

    std::vector<std::unique_ptr<VarDec>>& FuncDec::params_get()
    {
        return params_;
    }

    void FuncDec::params_set(std::vector<std::unique_ptr<VarDec>> params)
    {
        params_ = std::move(params);
    }

    Type* FuncDec::type_get() const
    {
        return type_.get();
    }

    void FuncDec::type_set(type_ptr type)
    {
        type_ = std::move(type);
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
                       exp_ptr precondition, std::vector<stmt_ptr> body)
        : Dec(location, name)
        , precondition_(std::move(precondition))
        , body_(std::move(body))
    {}

    SceneDec::SceneDec(const Location& location, std::string name,
                       std::vector<stmt_ptr> body)
        : Dec(location, name)
        , precondition_(nullptr)
        , body_(std::move(body))
    {}

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

} // namespace ast
