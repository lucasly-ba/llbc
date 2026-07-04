#include <ast/all.h>
#include <ast/dec.h>
#include <ast/exp.h>
#include <ast/stmt.h>
#include <factory.h>

namespace parser
{

    ast::dec_ptr make_VarDec(const ast::Location& location, std::string name,
                             ast::Type type, ast::exp_ptr init)
    {
        return std::make_unique<ast::VarDec>(location, std::move(name), type,
                                             std::move(init));
    }

    ast::dec_ptr make_VarDec(const ast::Location& location, std::string name,
                             ast::exp_ptr init)
    {
        return std::make_unique<ast::VarDec>(location, std::move(name),
                                             std::move(init));
    }

    ast::dec_ptr make_FuncDec(const ast::Location& location, std::string name,
                              std::vector<std::unique_ptr<ast::VarDec>> args,
                              ast::Type type, std::vector<ast::stmt_ptr> body)
    {
        return std::make_unique<ast::FuncDec>(
            location, std::move(name), std::move(args), type, std::move(body));
    }

    ast::dec_ptr make_FuncDec(const ast::Location& location, std::string name,
                              std::vector<std::unique_ptr<ast::VarDec>> args,
                              std::vector<ast::stmt_ptr> body)
    {
        return std::make_unique<ast::FuncDec>(location, std::move(name),
                                              std::move(args), std::move(body));
    }

    ast::dec_ptr make_SceneDec(const ast::Location& location, std::string name,
                               std::optional<int> max_players,
                               ast::exp_ptr precondition,
                               std::vector<ast::stmt_ptr> body)
    {
        return std::make_unique<ast::SceneDec>(
            location, std::move(name), max_players, std::move(precondition),
            std::move(body));
    }

    ast::dec_ptr make_PlayerDec(const ast::Location& location, std::string name,
                                ast::exp_ptr dollar, ast::exp_ptr chance,
                                ast::exp_ptr reputation)
    {
        return std::make_unique<ast::PlayerDec>(
            location, std::move(name), std::move(dollar), std::move(chance),
            std::move(reputation));
    }

    ast::exp_ptr make_OpExp(const ast::Location& location, ast::exp_ptr left,
                            ast::OpExp::Oper oper, ast::exp_ptr right)
    {
        return std::make_unique<ast::OpExp>(location, std::move(left), oper,
                                            std::move(right));
    }

    ast::exp_ptr make_IntExp(const ast::Location& location, int value)
    {
        return std::make_unique<ast::IntExp>(location, value);
    }

    ast::exp_ptr make_FloatExp(const ast::Location& location, float value)
    {
        return std::make_unique<ast::FloatExp>(location, value);
    }

    ast::exp_ptr make_StringExp(const ast::Location& location,
                                std::string value)
    {
        return std::make_unique<ast::StringExp>(location, std::move(value));
    }

    ast::exp_ptr make_BoolExp(const ast::Location& location, bool value)
    {
        return std::make_unique<ast::BoolExp>(location, value);
    }

    ast::exp_ptr make_DollarExp(const ast::Location& location, int value)
    {
        return std::make_unique<ast::DollarExp>(location, value);
    }

    ast::exp_ptr make_ChanceExp(const ast::Location& location, int value)
    {
        return std::make_unique<ast::ChanceExp>(location, value);
    }

    ast::exp_ptr make_ReputationExp(const ast::Location& location, int value)
    {
        return std::make_unique<ast::ReputationExp>(location, value);
    }

    ast::exp_ptr make_CallExp(const ast::Location& location, std::string name,
                              std::vector<ast::exp_ptr> args)
    {
        return std::make_unique<ast::CallExp>(location, std::move(name),
                                              std::move(args));
    }

    ast::exp_ptr make_IdentExp(const ast::Location& location, std::string name)
    {
        return std::make_unique<ast::IdentExp>(location, std::move(name));
    }

    ast::stmt_ptr make_LetStmt(const ast::Location& location,
                               std::unique_ptr<ast::VarDec> vardec)
    {
        return std::make_unique<ast::LetStmt>(location, std::move(vardec));
    }

    ast::stmt_ptr make_IfStmt(const ast::Location& location,
                              ast::exp_ptr condition,
                              std::vector<ast::stmt_ptr> then_branch,
                              std::vector<ast::stmt_ptr> else_branch)
    {
        return std::make_unique<ast::IfStmt>(location, std::move(condition),
                                             std::move(then_branch),
                                             std::move(else_branch));
    }

    ast::stmt_ptr make_IfStmt(const ast::Location& location,
                              ast::exp_ptr condition,
                              std::vector<ast::stmt_ptr> then_branch)
    {
        return std::make_unique<ast::IfStmt>(location, std::move(condition),
                                             std::move(then_branch));
    }

    ast::stmt_ptr make_LoopStmt(const ast::Location& location,
                                std::vector<ast::stmt_ptr> body)
    {
        return std::make_unique<ast::LoopStmt>(location, std::move(body));
    }

    ast::stmt_ptr make_BreakStmt(const ast::Location& location)
    {
        return std::make_unique<ast::BreakStmt>(location);
    }

    ast::stmt_ptr make_ReturnStmt(const ast::Location& location,
                                  ast::exp_ptr value)
    {
        return std::make_unique<ast::ReturnStmt>(location, std::move(value));
    }

    ast::stmt_ptr make_ReturnStmt(const ast::Location& location)
    {
        return std::make_unique<ast::ReturnStmt>(location);
    }

    ast::stmt_ptr make_ExpStmt(const ast::Location& location, ast::exp_ptr exp)
    {
        return std::make_unique<ast::ExpStmt>(location, std::move(exp));
    }
} // namespace parser
