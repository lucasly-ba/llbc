#pragma once
#include <ast/ast.h>
#include <ast/fwd.h>
#include <vector>

namespace ast
{
    class Dec : public Ast
    {
    public:
        Dec(const Location& location, std::string name);
        std::string name_get() const;
        void name_set(std::string name);

    protected:
        std::string name_;
    };

    class VarDec : public Dec
    {
    public:
        VarDec(const Location& location, std::string name, type_ptr type,
               exp_ptr init);
        VarDec(const Location& location, std::string name, exp_ptr init);

        Type* type_get() const;
        void type_set(type_ptr type);

        Exp* init_get() const;
        void init_set(exp_ptr init);

    private:
        type_ptr type_;
        exp_ptr init_;
    };

    class FuncDec : public Dec
    {
    public:
        FuncDec(const Location& location, std::string name,
                std::vector<std::unique_ptr<VarDec>> params, type_ptr type,
                std::vector<stmt_ptr> body);

        FuncDec(const Location& location, std::string name,
                std::vector<std::unique_ptr<VarDec>> params,
                std::vector<stmt_ptr> body);

        const std::vector<std::unique_ptr<VarDec>>& params_get() const;
        std::vector<std::unique_ptr<VarDec>>& params_get();
        void params_set(std::vector<std::unique_ptr<VarDec>> params);

        Type* type_get() const;
        void type_set(type_ptr type);

        const std::vector<stmt_ptr>& body_get() const;
        std::vector<stmt_ptr>& body_get();
        void body_set(std::vector<stmt_ptr> body);

    private:
        std::vector<std::unique_ptr<VarDec>> params_;
        type_ptr type_;
        std::vector<stmt_ptr> body_;
    };

    class SceneDec : public Dec
    {
    public:
        SceneDec(const Location& location, std::string name,
                 exp_ptr precondition, std::vector<stmt_ptr> body);

        SceneDec(const Location& location, std::string name,
                 std::vector<stmt_ptr> body);

        Exp* precondition_get() const;
        void precondition_set(exp_ptr precondition);

        const std::vector<stmt_ptr>& body_get() const;
        std::vector<stmt_ptr>& body_get();
        void body_set(std::vector<stmt_ptr> body);

    private:
        exp_ptr precondition_;
        std::vector<stmt_ptr> body_;
    };

} // namespace ast
