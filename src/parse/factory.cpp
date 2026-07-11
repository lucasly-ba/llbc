#include <factory.h>

namespace parser
{
    using namespace ast;

    std::unique_ptr<VarDec> make_VarDec(const Location& location,
                                        std::string name, Type type,
                                        exp_ptr init)
    {
        return std::make_unique<VarDec>(location, std::move(name), type,
                                        std::move(init));
    }

    std::unique_ptr<VarDec> make_VarDec(const Location& location,
                                        std::string name, exp_ptr init)
    {
        return std::make_unique<VarDec>(location, std::move(name),
                                        std::move(init));
    }

    dec_ptr make_FuncDec(const Location& location, std::string name,
                         std::vector<std::unique_ptr<VarDec>> args, Type type,
                         std::vector<stmt_ptr> body)
    {
        return std::make_unique<FuncDec>(
            location, std::move(name), std::move(args), type, std::move(body));
    }

    dec_ptr make_SceneDec(const Location& location, std::string name,
                          std::optional<int> max_players, exp_ptr precondition,
                          std::vector<stmt_ptr> body)
    {
        return std::make_unique<SceneDec>(location, std::move(name),
                                          max_players, std::move(precondition),
                                          std::move(body));
    }

    dec_ptr make_PlayerDec(const Location& location, std::string name,
                           exp_ptr dollars, exp_ptr chance, exp_ptr streak)
    {
        return std::make_unique<PlayerDec>(
            location, std::move(name), std::move(dollars), std::move(chance),
            std::move(streak));
    }

    exp_ptr make_OpExp(const Location& location, exp_ptr left, OpExp::Oper oper,
                       exp_ptr right)
    {
        return std::make_unique<OpExp>(location, std::move(left), oper,
                                       std::move(right));
    }

    exp_ptr make_IntExp(const Location& location, int value)
    {
        return std::make_unique<IntExp>(location, value);
    }

    exp_ptr make_FloatExp(const Location& location, float value)
    {
        return std::make_unique<FloatExp>(location, value);
    }

    exp_ptr make_StringExp(const Location& location, std::string value)
    {
        return std::make_unique<StringExp>(location, std::move(value));
    }

    exp_ptr make_BoolExp(const Location& location, bool value)
    {
        return std::make_unique<BoolExp>(location, value);
    }

    exp_ptr make_DollarsExp(const Location& location, int value)
    {
        return std::make_unique<DollarsExp>(location, value);
    }

    exp_ptr make_ChanceExp(const Location& location, int value)
    {
        return std::make_unique<ChanceExp>(location, value);
    }

    exp_ptr make_StreakExp(const Location& location, int value)
    {
        return std::make_unique<StreakExp>(location, value);
    }

    exp_ptr make_CallExp(const Location& location, std::string name,
                         std::vector<exp_ptr> args)
    {
        return std::make_unique<CallExp>(location, std::move(name),
                                         std::move(args));
    }

    exp_ptr make_IdentExp(const Location& location, std::string name)
    {
        return std::make_unique<IdentExp>(location, std::move(name));
    }

    stmt_ptr make_VarStmt(const Location& location,
                          std::unique_ptr<VarDec> vardec)
    {
        return std::make_unique<VarStmt>(location, std::move(vardec));
    }

    stmt_ptr make_AssignStmt(const Location& location, std::string name,
                             exp_ptr value)
    {
        return std::make_unique<AssignStmt>(location, std::move(name),
                                            std::move(value));
    }

    stmt_ptr make_IfStmt(const Location& location, exp_ptr condition,
                         std::vector<stmt_ptr> then_branch,
                         std::vector<stmt_ptr> else_branch)
    {
        return std::make_unique<IfStmt>(location, std::move(condition),
                                        std::move(then_branch),
                                        std::move(else_branch));
    }

    stmt_ptr make_IfStmt(const Location& location, exp_ptr condition,
                         std::vector<stmt_ptr> then_branch)
    {
        return std::make_unique<IfStmt>(location, std::move(condition),
                                        std::move(then_branch));
    }

    stmt_ptr make_LoopStmt(const Location& location, std::vector<stmt_ptr> body)
    {
        return std::make_unique<LoopStmt>(location, std::move(body));
    }

    stmt_ptr make_BreakStmt(const Location& location)
    {
        return std::make_unique<BreakStmt>(location);
    }

    stmt_ptr make_ReturnStmt(const Location& location, exp_ptr value)
    {
        return std::make_unique<ReturnStmt>(location, std::move(value));
    }

    stmt_ptr make_EntersStmt(const Location& location, std::string player_name,
                             std::string scene_name)
    {
        return std::make_unique<EntersStmt>(location, std::move(player_name),
                                            std::move(scene_name));
    }

    stmt_ptr make_StartStmt(const Location& location, std::string scene_name)
    {
        return std::make_unique<StartStmt>(location, std::move(scene_name));
    }

    stmt_ptr make_ExpStmt(const Location& location, exp_ptr exp)
    {
        return std::make_unique<ExpStmt>(location, std::move(exp));
    }
} // namespace parser
