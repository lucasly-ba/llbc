#include <ast/all.h>
#include <factory.h>
#include <parser.h>

#include "token.h"

namespace parser
{
    using namespace ast;

    Parser::Parser(bool trace, std::vector<Token> tokens)
        : trace_(trace)
        , tokens_(tokens)
    {}

    Program Parser::parse_program()
    {
        std::vector<dec_ptr> decs{};
        while (!is_eof())
        {
            switch (cur().kind)
            {
            case TokenKind::Var:
                decs.push_back(parse_var_dec());
                break;
            case TokenKind::Function:
                decs.push_back(parse_function_dec());
                break;
            case TokenKind::Scene:
                decs.push_back(parse_scene_dec());
                break;
            case TokenKind::Player:
                decs.push_back(parse_player_dec());
                break;
            default:
                emit_error("Only declarations are allowed in top level");
                walk();
            }
        }
        return Program(std::move(decs));
    }

    dec_ptr Parser::parse_var_dec()
    {}

    dec_ptr Parser::parse_function_dec()
    {}

    dec_ptr Parser::parse_scene_dec()
    {}

    dec_ptr Parser::parse_player_dec()
    {}

    dec_ptr parse_Var_dec()
    {}

} // namespace parser
