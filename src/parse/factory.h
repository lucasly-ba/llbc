#pragma once
#include <ast/all.h>
#include <ast/ast.h>
#include <ast/type.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace parser
{
    ast::dec_ptr make_VarDec(const ast::Location& location, std::string name,
                             ast::Type type, ast::exp_ptr init);

    ast::dec_ptr make_VarDec(const ast::Location& location, std::string name,
                             ast::exp_ptr init);

    ast::dec_ptr make_FuncDec(const ast::Location& location, std::string name,
                              std::vector<std::unique_ptr<ast::VarDec>> args,
                              ast::Type type, std::vector<ast::stmt_ptr> body);

    ast::dec_ptr make_FuncDec(const ast::Location& location, std::string name,
                              std::vector<std::unique_ptr<ast::VarDec>> args,
                              std::vector<ast::stmt_ptr> body);

    ast::dec_ptr make_SceneDec(const ast::Location& location, std::string name,
                               std::optional<int> max_players,
                               ast::exp_ptr precondition,
                               std::vector<ast::stmt_ptr> body);

    ast::dec_ptr make_PlayerDec(const ast::Location& location, std::string name,
                                ast::exp_ptr dollar, ast::exp_ptr chance,
                                ast::exp_ptr reputation);

    ast::exp_ptr make_OpExp(const ast::Location& location, ast::exp_ptr left,
                            ast::OpExp::Oper oper, ast::exp_ptr right);

    ast::exp_ptr make_IntExp(const ast::Location& location, int value);
    ast::exp_ptr make_FloatExp(const ast::Location& location, float value);

    ast::exp_ptr make_StringExp(const ast::Location& location,

                                std::string value);
    ast::exp_ptr make_BoolExp(const ast::Location& location, bool value);
    ast::exp_ptr make_DollarExp(const ast::Location& location, int value);
    ast::exp_ptr make_ChanceExp(const ast::Location& location, int value);
    ast::exp_ptr make_ReputationExp(const ast::Location& location, int value);

    ast::exp_ptr make_CallExp(const ast::Location& location, std::string name,
                              std::vector<ast::exp_ptr> args);

    ast::exp_ptr make_IdentExp(const ast::Location& location, std::string name);

    ast::stmt_ptr make_LetStmt(const ast::Location& location,
                               std::unique_ptr<ast::VarDec> vardec);

    ast::stmt_ptr make_IfStmt(const ast::Location& location,
                              ast::exp_ptr condition,
                              std::vector<ast::stmt_ptr> then_branch,
                              std::vector<ast::stmt_ptr> else_branch);

    ast::stmt_ptr make_IfStmt(const ast::Location& location,
                              ast::exp_ptr condition,
                              std::vector<ast::stmt_ptr> then_branch);

    ast::stmt_ptr make_LoopStmt(const ast::Location& location,
                                std::vector<ast::stmt_ptr> body);

    ast::stmt_ptr make_BreakStmt(const ast::Location& location);

    ast::stmt_ptr make_ReturnStmt(const ast::Location& location,
                                  ast::exp_ptr value);

    ast::stmt_ptr make_ReturnStmt(const ast::Location& location);

    ast::stmt_ptr make_ExpStmt(const ast::Location& location, ast::exp_ptr exp);
} // namespace parser
