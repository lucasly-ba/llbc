#pragma once

#include <ast/ast.h>
#include <token.h>
#include <vector>

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
        Parser(bool trace, std::vector<Token> tokens);
        ast::Program parse_program();
        const std::vector<ParseError>& get_errors() const;
        bool has_error() const;

    private:
        dec_ptr parse_var_dec();
        dec_ptr parse_function_dec();
        dec_ptr parse_scene_dec();
        dec_ptr parse_player_dec();
        void walk();
        Token cur() const;
        Token peek() const;
        bool is_eof() const;
        bool is_peek_eof() const;
        bool is_token_start_dec(TokenKind kind) const;
        void emit_error(const std::string& message);

        bool trace_;
        size_t pos_ = 0;
        std::vector<Token> tokens_;
        std::vector<ParseError> errors_;
    };

} // namespace parser
