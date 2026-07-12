#include <parse/lexer.h>
#include <parse/parser.h>

/// Lexer
namespace parser
{
    void Lexer::skip_white_space()
    {
        while (!is_eof() && (cur() == ' ' || cur() == '\t' || cur() == '\r'))
            walk();
    }

    void Lexer::walk()
    {
        pos_++;
        col_++;
    }

    // at eof
    void Lexer::reset()
    {
        line_++;
        pos_++;
        col_ = 0;
    }

    char Lexer::cur() const
    {
        return content_[pos_];
    }

    char Lexer::peek() const
    {
        return content_[pos_ + 1];
    }

    Token Lexer::create_token(TokenKind kind, const std::string& value)
    {
        return Token{ kind, value, line_ + 1, col_ };
    }

    const std::vector<LexError>& Lexer::get_errors() const
    {
        return errors_;
    }

    bool Lexer::has_error() const
    {
        return !errors_.empty();
    }

    bool Lexer::is_eof() const
    {
        return pos_ >= content_.size();
    }

    bool Lexer::is_peek_eof() const
    {
        return pos_ + 1 >= content_.size();
    }

    void Lexer::emit_error(const std::string& message)
    {
        errors_.push_back({ message, line_ + 1, col_ });
    }
} // namespace parser

/// Parser
namespace parser
{

    void Parser::walk()
    {
        pos_++;
    }

    const Token& Parser::cur() const
    {
        return tokens_[pos_];
    }

    TokenKind Parser::kind() const
    {
        return cur().kind;
    }

    TokenKind Parser::peek_kind() const
    {
        if (pos_ + 1 >= tokens_.size())
            return TokenKind::Eof;
        return tokens_[pos_ + 1].kind;
    }

    bool Parser::is_token_start_dec(TokenKind kind) const
    {
        return kind == TokenKind::Var || kind == TokenKind::Function
            || kind == TokenKind::Scene || kind == TokenKind::Player;
    }

    const std::string& Parser::value() const
    {
        return cur().value;
    }

    const std::vector<ParseError>& Parser::get_errors() const
    {
        return errors_;
    }

    bool Parser::has_error() const
    {
        return !errors_.empty();
    }

    bool Parser::is_eof() const
    {
        return cur().kind == TokenKind::Eof;
    }

    void Parser::emit_error(const std::string& message)
    {
        errors_.push_back({ message, cur().value, cur().line, cur().col });
    }

    void Parser::synchronize()
    {
        while (!is_eof() && !is_token_start_dec(cur().kind))
            walk();
    }

    void Parser::synchronize_stmt()
    {
        while (!is_eof() && kind() != TokenKind::RBrace
               && kind() != TokenKind::Var && kind() != TokenKind::If
               && kind() != TokenKind::Loop && kind() != TokenKind::Break
               && kind() != TokenKind::Return && kind() != TokenKind::Start)
            walk();
    }

    bool Parser::emit_and_synchronize(const std::string& message)
    {
        emit_error(message);
        synchronize();
        return false;
    }

    dec_ptr Parser::fail_dec(const std::string& message)
    {
        emit_error(message);
        synchronize();
        return nullptr;
    }

    std::unique_ptr<VarDec> Parser::fail_var_dec(const std::string& message)
    {
        emit_error(message);
        synchronize();
        return nullptr;
    }

    stmt_ptr Parser::fail_stmt(const std::string& message)
    {
        emit_error(message);
        synchronize_stmt();
        return nullptr;
    }

    exp_ptr Parser::fail_exp(const std::string& message)
    {
        emit_error(message);
        synchronize_stmt();
        return nullptr;
    }

    Location Parser::get_location() const
    {
        return Location{ cur().col, cur().line };
    }

} // namespace parser
