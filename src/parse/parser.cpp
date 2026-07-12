#include <parse/factory.h>
#include <optional>
#include <parse/parser.h>
#include <set>
#include <utility>

#include <ast/type.h>

namespace parser
{
    using namespace ast;

    Parser::Parser(std::vector<Token> tokens)
        : tokens_(std::move(tokens))
    {}

    Program Parser::parse_program()
    {
        return Program(parse_dec());
    }

    std::vector<dec_ptr> Parser::parse_dec()
    {
        std::vector<dec_ptr> decs{};
        while (!is_eof())
        {
            dec_ptr dec;
            switch (cur().kind)
            {
            case TokenKind::Var:
                dec = parse_var_dec();
                break;
            case TokenKind::Function:
                dec = parse_function_dec();
                break;
            case TokenKind::Scene:
                dec = parse_scene_dec();
                break;
            case TokenKind::Player:
                dec = parse_player_dec();
                break;
            default:
                emit_error("Only declarations are allowed in top level");
                walk();
                continue;
            }
            if (dec)
                decs.push_back(std::move(dec));
        }
        return decs;
    }

    std::unique_ptr<VarDec> Parser::parse_var_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        std::optional<Type> type = std::nullopt;
        if (kind() != TokenKind::ID)
            return fail_var_dec("Expected name after `var`");
        name = value();
        walk();
        if (kind() == TokenKind::Colon)
        {
            walk();
            type = get_type(value());
            if (!type.has_value())
                return fail_var_dec("Unexpected type name");
            walk();
        }
        if (kind() == TokenKind::Eq)
        {
            walk();
            exp_ptr init = parse_exp();
            if (kind() != TokenKind::SemiColon)
                return fail_var_dec(
                    "Expected semi colon after var declaration");
            walk();

            if (type.has_value())
                return make_VarDec(location, std::move(name), *type,
                                   std::move(init));
            return make_VarDec(location, std::move(name), std::move(init));
        }
        else
            return fail_var_dec("expected ':' or '=' after var name");
    }

    bool Parser::parse_function_args(std::vector<std::unique_ptr<VarDec>>& args)
    {
        if (kind() != TokenKind::LPar)
            return emit_and_synchronize(
                "Expected left parenthesis after function name");
        walk();
        while (!is_eof() && kind() != TokenKind::RPar)
        {
            if (kind() != TokenKind::ID)
                return emit_and_synchronize("Expected var name");
            std::string name = value();
            Location loc = get_location();
            walk();
            if (kind() != TokenKind::Colon)
                return emit_and_synchronize("Expected colon after var name");
            walk();
            auto type = get_type(value());
            if (!type.has_value())
                return emit_and_synchronize("Unexpected type name");
            args.push_back(make_VarDec(loc, name, *type, nullptr));
            walk();
            if (kind() == TokenKind::Comma)
                walk();
            else if (kind() != TokenKind::RPar)
                return emit_and_synchronize(
                    "Expected ',' or ')' after parameter");
        }
        if (kind() != TokenKind::RPar)
            return emit_and_synchronize("Expected  ')' after parameter");
        walk();

        return true;
    }

    dec_ptr Parser::parse_function_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        Type type = ast::Type::Void;
        std::vector<std::unique_ptr<VarDec>> args;
        std::vector<ast::stmt_ptr> body;

        if (kind() != TokenKind::ID)
            return fail_dec("Expected name after `fn`");
        name = value();
        walk();
        if (parse_function_args(args) == false)
            return nullptr;
        if (kind() == TokenKind::Arrow)
        {
            walk();
            auto t = get_type(value());
            if (!t.has_value())
                return fail_dec("Unexpected type name");
            type = t.value();
            walk();
        }
        if (kind() != TokenKind::LBrace)
            return fail_dec("Expected left bracket in function declaration");
        walk();
        body = parse_body();

        if (kind() != TokenKind::RBrace)
            return fail_dec("Expected right bracket in function declaration");

        walk();
        return make_FuncDec(location, std::move(name), std::move(args), type,
                            std::move(body));
    }

    dec_ptr Parser::parse_scene_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        std::optional<int> max_players = std::nullopt;
        exp_ptr precondition = nullptr;
        std::vector<ast::stmt_ptr> body;

        if (kind() != TokenKind::ID)
            return fail_dec("Expected name after `scene`");
        name = value();
        walk();
        if (kind() == TokenKind::Max)
        {
            walk();
            if (kind() != TokenKind::IntLit)
                return fail_dec("Expected integer after max");
            max_players = std::stoi(value());
            walk();
        }
        if (kind() == TokenKind::Requires)
        {
            walk();
            precondition = parse_exp();
        }
        if (kind() != TokenKind::LBrace)
            return fail_dec("Expected left bracket in scene declaration");
        walk();
        body = parse_body();
        if (kind() != TokenKind::RBrace)
            return fail_dec("Expected right bracket in scene declaration");
        walk();
        return make_SceneDec(location, std::move(name), max_players,
                             std::move(precondition), std::move(body));
    }

    bool Parser::parse_player_field(std::set<TokenKind>& player_fields,
                                    TokenKind field, int& val, Location& loc,
                                    TokenKind lit)
    {
        if (player_fields.find(field) == player_fields.end())
            return emit_and_synchronize("Field specified twice");
        walk();
        if (kind() != TokenKind::Colon)
            return emit_and_synchronize("Expected colon after field");
        walk();
        if (kind() != lit)
            return emit_and_synchronize("Expected value after field");
        loc = get_location();
        val = std::stoi(value());
        player_fields.erase(field);
        return true;
    }

    dec_ptr Parser::parse_player_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        int dollars;
        int chance;
        int streak;
        Location dollars_location;
        Location chance_location;
        Location streak_location;

        if (kind() != TokenKind::ID)
            return fail_dec("Expected name after `player`");
        name = value();
        walk();
        if (kind() != TokenKind::LBrace)
            return fail_dec("Expected left bracket after player name");
        walk();
        std::set player_fields{ TokenKind::Dollars, TokenKind::Chance,
                                TokenKind::Streak };

        while (!player_fields.empty())
        {
            TokenKind field = kind();
            switch (kind())
            {
            case TokenKind::Dollars:
                if (!parse_player_field(player_fields, field, dollars,
                                        dollars_location,
                                        TokenKind::DollarsLit))
                    return nullptr;
                break;
            case TokenKind::Chance:
                if (!parse_player_field(player_fields, field, chance,
                                        chance_location, TokenKind::ChanceLit))
                    return nullptr;
                break;
            case TokenKind::Streak:
                if (!parse_player_field(player_fields, field, streak,
                                        streak_location, TokenKind::StreakLit))
                    return nullptr;
                break;
            default:
                return fail_dec("Unrecognized field");
            }
            walk();
            if (!player_fields.empty())
            {
                if (kind() != TokenKind::Comma)
                    return fail_dec("Expected comma after field");
                walk();
            }
        }

        if (kind() != TokenKind::RBrace)
            return fail_dec("Expected right bracket after player fields");
        walk();
        return make_PlayerDec(location, std::move(name),
                              make_DollarsExp(dollars_location, dollars),
                              make_ChanceExp(chance_location, chance),
                              make_StreakExp(streak_location, streak));
    }

    std::vector<stmt_ptr> Parser::parse_body()
    {
        std::vector<stmt_ptr> stmts;
        while (!is_eof() && kind() != TokenKind::RBrace)
        {
            stmt_ptr stmt = parse_stmt();
            if (stmt)
                stmts.push_back(std::move(stmt));
        }
        return stmts;
    }

    stmt_ptr Parser::parse_stmt()
    {
        switch (cur().kind)
        {
        case TokenKind::Var:
            return parse_var_stmt();
        case TokenKind::If:
            return parse_if_stmt();
        case TokenKind::Loop:
            return parse_loop_stmt();
        case TokenKind::Break:
            return parse_break_stmt();
        case TokenKind::Return:
            return parse_return_stmt();
        case TokenKind::Start:
            return parse_start_stmt();
        case TokenKind::ID:
            if (peek_kind() == TokenKind::Enters)
                return parse_enters_stmt();
            if (peek_kind() == TokenKind::Eq)
                return parse_assign_stmt();
            return parse_exp_stmt();
        default:
            return parse_exp_stmt();
        }
    }

    stmt_ptr Parser::parse_var_stmt()
    {
        Location location = get_location();
        std::unique_ptr<VarDec> vardec = parse_var_dec();
        if (!vardec)
            return nullptr;
        return make_VarStmt(location, std::move(vardec));
    }

    stmt_ptr Parser::parse_assign_stmt()
    {
        Location location = get_location();
        std::string name = value();
        walk();
        walk();
        exp_ptr value = parse_exp();
        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after assignment");
        walk();
        return make_AssignStmt(location, std::move(name), std::move(value));
    }

    stmt_ptr Parser::parse_if_stmt()
    {
        Location location = get_location();
        walk();
        exp_ptr condition = parse_exp();

        if (kind() != TokenKind::LBrace)
            return fail_stmt("Expected left bracket before then branch");
        walk();
        std::vector<stmt_ptr> then_branch = parse_body();
        if (kind() != TokenKind::RBrace)
            return fail_stmt("Expected right bracket after then branch");
        walk();
        if (kind() == TokenKind::Else)
        {
            walk();
            if (kind() != TokenKind::LBrace)
                return fail_stmt("Expected left bracket after else branch");
            walk();
            auto else_branch = parse_body();
            if (kind() != TokenKind::RBrace)
                return fail_stmt("Expected right bracket after else branch");
            walk();
            return make_IfStmt(location, std::move(condition),
                               std::move(then_branch), std::move(else_branch));
        }
        return make_IfStmt(location, std::move(condition),
                           std::move(then_branch));
    }

    stmt_ptr Parser::parse_loop_stmt()
    {
        Location location = get_location();
        walk();

        if (kind() != TokenKind::LBrace)
            return fail_stmt("Expected left bracket after loop");
        walk();
        auto loop_body = parse_body();
        if (kind() != TokenKind::RBrace)
            return fail_stmt("Expected right bracket after loop");
        walk();
        return make_LoopStmt(location, std::move(loop_body));
    }

    stmt_ptr Parser::parse_break_stmt()
    {
        Location location = get_location();
        walk();

        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after break");
        walk();
        return make_BreakStmt(location);
    }

    stmt_ptr Parser::parse_return_stmt()
    {
        Location location = get_location();
        walk();
        exp_ptr value = parse_exp();

        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after return");
        walk();
        return make_ReturnStmt(location, std::move(value));
    }

    stmt_ptr Parser::parse_enters_stmt()
    {
        Location location = get_location();
        std::string player_name = value();
        walk();
        walk();
        if (kind() != TokenKind::ID)
            return fail_stmt("Expected scene name after `enters`");
        std::string scene_name = value();
        walk();
        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after enters statement");
        walk();
        return make_EntersStmt(location, std::move(player_name),
                               std::move(scene_name));
    }

    stmt_ptr Parser::parse_start_stmt()
    {
        Location location = get_location();
        walk();
        if (kind() != TokenKind::ID)
            return fail_stmt("Expected scene name after `start`");
        std::string scene_name = value();
        walk();
        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after start statement");
        walk();
        return make_StartStmt(location, std::move(scene_name));
    }

    stmt_ptr Parser::parse_exp_stmt()
    {
        auto exp_stmt = make_ExpStmt(get_location(), parse_exp());
        if (kind() != TokenKind::SemiColon)
            return fail_stmt("Expected semicolon after exp");
        walk();
        return exp_stmt;
    }

    exp_ptr Parser::parse_exp()
    {
        return parse_or_exp();
    }

    exp_ptr Parser::parse_or_exp()
    {
        auto left = parse_and_exp();
        while (kind() == TokenKind::Or)
        {
            auto location = get_location();
            walk();
            auto right = parse_and_exp();
            left = make_OpExp(location, std::move(left), ast::OpExp::Oper::OR,
                              std::move(right));
        }
        return left;
    }

    exp_ptr Parser::parse_and_exp()
    {
        auto left = parse_comparison_exp();
        while (kind() == TokenKind::And)
        {
            auto location = get_location();
            walk();
            auto right = parse_comparison_exp();
            left = make_OpExp(location, std::move(left), ast::OpExp::Oper::AND,
                              std::move(right));
        }
        return left;
    }

    exp_ptr Parser::parse_comparison_exp()
    {
        auto left = parse_additive_exp();
        while (kind() == TokenKind::EqEq || kind() == TokenKind::Lt
               || kind() == TokenKind::Leq || kind() == TokenKind::Gt
               || kind() == TokenKind::Geq || kind() == TokenKind::Neq)
        {
            ast::OpExp::Oper op;
            switch (kind())
            {
            case TokenKind::EqEq:
                op = ast::OpExp::Oper::EQ;
                break;
            case TokenKind::Lt:
                op = ast::OpExp::Oper::LT;
                break;
            case TokenKind::Leq:
                op = ast::OpExp::Oper::LEQ;
                break;
            case TokenKind::Gt:
                op = ast::OpExp::Oper::GT;
                break;
            case TokenKind::Geq:
                op = ast::OpExp::Oper::GEQ;
                break;
            case TokenKind::Neq:
                op = ast::OpExp::Oper::NEQ;
                break;
            default:
                std::unreachable();
                break;
            }
            auto location = get_location();
            walk();
            auto right = parse_additive_exp();
            left = make_OpExp(location, std::move(left), op, std::move(right));
        }
        return left;
    }

    exp_ptr Parser::parse_additive_exp()
    {
        auto left = parse_multiplicative_exp();
        while (kind() == TokenKind::Plus || kind() == TokenKind::Minus)

        {
            ast::OpExp::Oper op;
            switch (kind())
            {
            case TokenKind::Plus:
                op = ast::OpExp::Oper::ADD;
                break;
            case TokenKind::Minus:
                op = ast::OpExp::Oper::SUB;
                break;
            default:
                std::unreachable();
                break;
            }
            auto location = get_location();
            walk();
            auto right = parse_multiplicative_exp();
            left = make_OpExp(location, std::move(left), op, std::move(right));
        }
        return left;
    }

    exp_ptr Parser::parse_multiplicative_exp()

    {
        auto left = parse_primary_exp();
        while (kind() == TokenKind::Mul || kind() == TokenKind::Div)
        {
            ast::OpExp::Oper op;
            switch (kind())
            {
            case TokenKind::Mul:
                op = ast::OpExp::Oper::MUL;
                break;
            case TokenKind::Div:
                op = ast::OpExp::Oper::DIV;
                break;
            default:
                std::unreachable();
                break;
            }
            auto location = get_location();
            walk();
            auto right = parse_primary_exp();
            left = make_OpExp(location, std::move(left), op, std::move(right));
        }
        return left;
    }

    exp_ptr Parser::parse_primary_exp()
    {
        Location location = get_location();
        switch (kind())
        {
        case TokenKind::IntLit: {
            int val = std::stoi(value());
            walk();
            return make_IntExp(location, val);
        }
        case TokenKind::FloatLit: {
            float val = std::atof(value().c_str());
            walk();
            return make_FloatExp(location, val);
        }
        case TokenKind::StringLit: {
            std::string val = value();
            walk();
            return make_StringExp(location, val);
        }
        case TokenKind::BoolLit: {
            bool val = (value() == "true");
            walk();
            return make_BoolExp(location, val);
        }
        case TokenKind::DollarsLit: {
            int val = std::stoi(value());
            walk();
            return make_DollarsExp(location, val);
        }
        case TokenKind::ChanceLit: {
            int val = std::stoi(value());
            walk();
            return make_ChanceExp(location, val);
        }
        case TokenKind::StreakLit: {
            int val = std::stoi(value());
            walk();
            return make_StreakExp(location, val);
        }
        case TokenKind::ID: {
            auto id = value();
            walk();
            if (kind() == TokenKind::LPar)
            {
                walk();
                std::vector<exp_ptr> args;
                while (!is_eof() && kind() != TokenKind::RPar)
                {
                    args.push_back(parse_exp());
                    if (kind() == TokenKind::Comma)
                        walk();
                    else if (kind() != TokenKind::RPar)
                        return fail_exp("Expected ',' or ')' after call arg");
                }
                if (kind() != TokenKind::RPar)
                    return fail_exp("Expected  ')' after call arg");
                walk();
                return make_CallExp(location, std::move(id), std::move(args));
            }
            return make_IdentExp(location, std::move(id));
        }
        case TokenKind::LPar: {
            walk();
            auto exp = parse_exp();
            if (kind() != TokenKind::RPar)
                return fail_exp("Expected ')' after expression");
            walk();
            return exp;
        }
        default:
            return fail_exp("Expected an expression");
        }
    }
} // namespace parser
