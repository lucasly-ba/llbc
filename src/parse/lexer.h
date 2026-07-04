#pragma once

#include <token.h>
#include <vector>

namespace parser
{
    struct LexError
    {
        std::string message;
        size_t line;
        size_t col;
    };

    class Lexer
    {
    public:
        Lexer(bool trace, std::string content);
        std::vector<Token> make_tokens();
        const std::vector<LexError>& get_errors() const;
        bool has_error() const;

    private:
        Token make_token();
        Token make_keyword_token();
        Token make_number_token();
        Token make_newline_token();
        Token make_stringlit_token();
        Token make_symbol_token(TokenKind kind);
        Token make_double_symbol_token(TokenKind kind);
        Token make_token_comment();
        Token make_eof_token();
        Token make_error_token(const std::string& message);

        Token create_token(TokenKind kind, const std::string& value = "");

        void emit_error(const std::string& message);
        void debug_lexer(const std::vector<Token>& tokens) const;
        void skip_white_space();
        void walk();
        void reset();

        char cur() const;
        char peek() const;

        bool is_eof() const;
        bool is_peek_eof() const;

        std::string content_;
        bool trace_ = false;
        size_t pos_ = 0;
        size_t col_ = 0;
        size_t line_ = 0;
        std::vector<LexError> errors_;
    };

} // namespace parser
