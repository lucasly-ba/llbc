#pragma once
#include <ast/ast.h>
#include <ast/fwd.h>
#include <ast/type.h>
#include <optional>
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
        VarDec(const Location& location, std::string name, Type type,
               exp_ptr init);
        VarDec(const Location& location, std::string name, exp_ptr init);

        void accept(Visitor& v) override;

        std::optional<Type> type_get() const;
        void type_set(Type type);

        Exp* init_get() const;
        void init_set(exp_ptr init);

    private:
        std::optional<Type> type_;
        exp_ptr init_;
    };

    class FuncDec : public Dec
    {
    public:
        FuncDec(const Location& location, std::string name,
                std::vector<std::unique_ptr<VarDec>> args, Type type,
                std::vector<stmt_ptr> body);
        FuncDec(const Location& location, std::string name,
                std::vector<std::unique_ptr<VarDec>> args,
                std::vector<stmt_ptr> body);

        void accept(Visitor& v) override;

        const std::vector<std::unique_ptr<VarDec>>& args_get() const;
        std::vector<std::unique_ptr<VarDec>>& args_get();
        void args_set(std::vector<std::unique_ptr<VarDec>> args);

        std::optional<Type> type_get() const;
        void type_set(Type type);

        const std::vector<stmt_ptr>& body_get() const;
        std::vector<stmt_ptr>& body_get();
        void body_set(std::vector<stmt_ptr> body);

    private:
        std::vector<std::unique_ptr<VarDec>> args_;
        std::optional<Type> type_;
        std::vector<stmt_ptr> body_;
    };

    class SceneDec : public Dec
    {
    public:
        SceneDec(const Location& location, std::string name,
                 std::optional<int> max_players, exp_ptr precondition,
                 std::vector<stmt_ptr> body);

        SceneDec(const Location& location, std::string name,
                 exp_ptr precondition, std::vector<stmt_ptr> body);

        SceneDec(const Location& location, std::string name,
                 std::optional<int> max_players, std::vector<stmt_ptr> body);

        SceneDec(const Location& location, std::string name,
                 std::vector<stmt_ptr> body);

        void accept(Visitor& v) override;

        std::optional<int> max_players_get() const;
        void max_players_set(std::optional<int> max_players);

        Exp* precondition_get() const;
        void precondition_set(exp_ptr precondition);

        const std::vector<stmt_ptr>& body_get() const;
        std::vector<stmt_ptr>& body_get();
        void body_set(std::vector<stmt_ptr> body);

    private:
        std::optional<int> max_players_;
        exp_ptr precondition_;
        std::vector<stmt_ptr> body_;
    };

    class PlayerDec : public Dec
    {
    public:
        PlayerDec(const Location& location, std::string name, exp_ptr dollar,
                  exp_ptr chance, exp_ptr reputation);

        void accept(Visitor& v) override;

        Exp& dollar_get() const;
        void dollar_set(exp_ptr dollar);
        Exp& chance_get() const;
        void chance_set(exp_ptr chance);
        Exp& reputation_get() const;
        void reputation_set(exp_ptr reputation);

    private:
        exp_ptr dollar_;
        exp_ptr chance_;
        exp_ptr reputation_;
    };

} // namespace ast
