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
    using namespace ast;
    std::unique_ptr<ast::VarDec> make_VarDec(const ast::Location& location,
                                             std::string name, ast::Type type,
                                             ast::exp_ptr init);
    std::unique_ptr<ast::VarDec> make_VarDec(const ast::Location& location,
                                             std::string name,
                                             ast::exp_ptr init);

    dec_ptr make_FuncDec(const Location& location, std::string name,
                         std::vector<std::unique_ptr<VarDec>> args,
                         std::optional<Type> type, std::vector<stmt_ptr> body);

    ast::dec_ptr make_SceneDec(const ast::Location& location, std::string name,
                               std::optional<int> max_players,
                               ast::exp_ptr precondition,
                               std::vector<ast::stmt_ptr> body);

    dec_ptr make_PlayerDec(const Location& location, std::string name,
                           exp_ptr dollars, exp_ptr chance, exp_ptr streak);

    exp_ptr make_OpExp(const Location& location, exp_ptr left, OpExp::Oper oper,
                       exp_ptr right);

    exp_ptr make_IntExp(const Location& location, int value);
    exp_ptr make_FloatExp(const Location& location, float value);

    exp_ptr make_StringExp(const Location& location,

                           std::string value);
    exp_ptr make_BoolExp(const Location& location, bool value);
    exp_ptr make_DollarsExp(const Location& location, int value);
    exp_ptr make_ChanceExp(const Location& location, int value);
    exp_ptr make_StreakExp(const Location& location, int value);

    exp_ptr make_CallExp(const Location& location, std::string name,
                         std::vector<exp_ptr> args);

    exp_ptr make_IdentExp(const Location& location, std::string name);

    stmt_ptr make_VarStmt(const Location& location,
                          std::unique_ptr<VarDec> vardec);

    stmt_ptr make_IfStmt(const Location& location, exp_ptr condition,
                         std::vector<stmt_ptr> then_branch,
                         std::vector<stmt_ptr> else_branch);

    stmt_ptr make_IfStmt(const Location& location, exp_ptr condition,
                         std::vector<stmt_ptr> then_branch);

    stmt_ptr make_LoopStmt(const Location& location,
                           std::vector<stmt_ptr> body);

    stmt_ptr make_BreakStmt(const Location& location);

    stmt_ptr make_ReturnStmt(const Location& location, exp_ptr value);

    stmt_ptr make_EntersStmt(const Location& location, std::string player_name,
                             std::string scene_name);

    stmt_ptr make_StartStmt(const Location& location, std::string scene_name);

    stmt_ptr make_ExpStmt(const Location& location, exp_ptr exp);
} // namespace parser
