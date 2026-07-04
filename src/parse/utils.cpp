#include <lexer.h>
#include <parser.h>

/// Lexer
namespace parser
{
    void Lexer::skip_white_space()
    {
        while (!is_eof() && (cur() == ' ' || cur() == '\t'))
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
        return Token{ kind, value, line_, col_ };
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
        errors_.push_back({ message, line_, col_ });
    }
} // namespace parser

/// Parser
namespace parser
{

    void Parser::walk()
    {
        pos_++;
    }

    Token Parser::cur() const
    {
        return tokens_[pos_];
    }

    Token Parser::peek() const
    {
        return tokens_[pos_ + 1];
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
        return pos_ >= tokens_.size();
    }

    bool Parser::is_peek_eof() const
    {
        return pos_ + 1 >= tokens_.size();
    }

    void Parser::emit_error(const std::string& message)
    {
        errors_.push_back({ message, cur().value, cur().line, cur().col });
    }

} // namespace parser
