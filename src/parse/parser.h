#pragma once

#include <ast/ast.h>
#include <set>
#include <token.h>
#include <vector>

#include "fwd.h"

namespace parser
{
    using namespace ast;
    struct ParseError
    {
        std::string message;
        std::string value;
        size_t line;
        size_t col;
    };

    class Parser
    {
    public:
        Parser(std::vector<Token> tokens);
        ast::Program parse_program();
        const std::vector<ParseError>& get_errors() const;
        bool has_error() const;

    private:
        std::vector<dec_ptr> parse_dec();
        // decs
        std::unique_ptr<VarDec> parse_var_dec();
        bool parse_function_args(std::vector<std::unique_ptr<VarDec>>& args);
        dec_ptr parse_function_dec();
        dec_ptr parse_scene_dec();
        bool parse_player_field(std::set<TokenKind>& player_fields,
                                TokenKind field, int& val, Location& loc,
                                TokenKind lit);
        dec_ptr parse_player_dec();

        // stmt
        std::vector<stmt_ptr> parse_body();
        stmt_ptr parse_stmt();
        stmt_ptr parse_var_stmt();
        stmt_ptr parse_if_stmt();
        stmt_ptr parse_loop_stmt();
        stmt_ptr parse_break_stmt();
        stmt_ptr parse_return_stmt();
        stmt_ptr parse_enters_stmt();
        stmt_ptr parse_start_stmt();
        stmt_ptr parse_exp_stmt();

        // exp
        exp_ptr parse_exp();
        exp_ptr parse_or_exp();
        exp_ptr parse_and_exp();
        exp_ptr parse_comparison_exp();
        exp_ptr parse_additive_exp();
        exp_ptr parse_multiplicative_exp();
        exp_ptr parse_primary_exp();

        // utils
        void walk();
        const Token& cur() const;
        TokenKind kind() const;
        TokenKind peek_kind() const;
        const std::string& value() const;
        bool is_eof() const;
        bool is_token_start_dec(TokenKind kind) const;
        void emit_error(const std::string& message);
        void synchronize();
        void synchronize_stmt();
        bool emit_and_synchronize(const std::string& message);
        dec_ptr fail_dec(const std::string& message);
        std::unique_ptr<VarDec> fail_var_dec(const std::string& message);
        stmt_ptr fail_stmt(const std::string& message);
        exp_ptr fail_exp(const std::string& message);

        Location get_location() const;

        size_t pos_ = 0;
        std::vector<Token> tokens_;
        std::vector<ParseError> errors_;
    };

} // namespace parser
