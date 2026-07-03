#include <cctype>
#include <format>
#include <iostream>
#include <lexer.h>

#include "token.h"

namespace lexer
{
    Lexer::Lexer(bool trace, std::string content)
        : content_(content)
        , trace_(trace)
    {}

    // Entry function
    std::vector<Token> Lexer::make_tokens()
    {
        std::vector<Token> tokens{};
        Token tok = make_token();
        bool skip_newline = false;
        while (tok.kind != TokenKind::Eof)
        {
            if (tok.kind == TokenKind::Newline)
                skip_newline = true;
            if (tok.kind != TokenKind::Comment && tok.kind != TokenKind::Error)
                tokens.push_back(tok);
            tok = make_token();
            // Avoid having multiple newlines in a row
            if (skip_newline)
            {
                while (tok.kind == TokenKind::Newline)
                    tok = make_token();
                skip_newline = false;
            }
        }
        if (trace_)
            debug_lexer(tokens);

        return tokens;
    }

    Token Lexer::make_token()
    {
        skip_white_space();

        if (is_eof())
            return make_eof_token();

        switch (cur())
        {
        case '\n':
            return make_newline_token();
        case '#':
            return make_token_comment();
        case '"':
            return make_stringlit_token();
        case '(':
            return make_symbol_token(TokenKind::LPar);
        case ')':
            return make_symbol_token(TokenKind::RPar);
        case '{':
            return make_symbol_token(TokenKind::LBrack);
        case '}':
            return make_symbol_token(TokenKind::RBrack);
        case ':':
            return make_symbol_token(TokenKind::Colon);
        case ',':
            return make_symbol_token(TokenKind::Comma);
        case '=':
            if (!is_peek_eof() && peek() == '=')
                return make_double_symbol_token(TokenKind::EqEq);
            return make_symbol_token(TokenKind::Eq);
        case '!':
            if (!is_peek_eof() && peek() == '=')
                return make_double_symbol_token(TokenKind::Neq);
            if (is_peek_eof())
            {
                emit_error("Unexpected end of file");
                return make_eof_token();
            }
            return make_error_token(
                std::format("Unexpected character: {}", cur()));
        case '<':
            if (!is_peek_eof() && peek() == '=')
                return make_double_symbol_token(TokenKind::Leq);
            return make_symbol_token(TokenKind::Lt);
        case '>':
            if (!is_peek_eof() && peek() == '=')
                return make_double_symbol_token(TokenKind::Geq);
            return make_symbol_token(TokenKind::Gt);
        case '+':
            return make_symbol_token(TokenKind::Plus);
        case '*':
            return make_symbol_token(TokenKind::Mul);
        case '/':
            return make_symbol_token(TokenKind::Div);
        case '-':
            if (!is_peek_eof() && peek() == '>')
                return make_double_symbol_token(TokenKind::Arrow);
            return make_symbol_token(TokenKind::Minus);
        default:
            if (std::isdigit(cur()))
                return make_number_token();
            if (std::isalpha(cur()) || cur() == '_')
                return make_keyword_token();
            return make_error_token(
                std::format("Unrecognized character: {}", cur()));
        }
    }

    Token Lexer::make_number_token()
    {
        std::string val = std::string(1, cur());
        walk();
        while (!is_eof() && std::isdigit(cur()))
        {
            val += cur();
            walk();
        }
        if (cur() == '$' || cur() == '%' || cur() == '*')
        {
            auto c = cur();
            val += c;
            walk();
            return create_token(player_info_kind(c), val);
        }
        return create_token(TokenKind::IntLit, val);
    }

    Token Lexer::make_keyword_token()
    {
        std::string val = std::string(1, cur());
        walk();
        while (!is_eof()
               && (std::isalpha(cur()) || std::isdigit(cur()) || cur() == '_'))
        {
            val += cur();
            walk();
        }
        auto it = keywords.find(val);
        if (it != keywords.end())
            return create_token(it->second, val);
        return create_token(TokenKind::ID, val);
    }

    Token Lexer::make_stringlit_token()
    {
        std::string val = "";
        walk();

        while (!is_eof() && cur() != '"')
        {
            if (cur() == '\\' && !is_peek_eof())
            {
                walk();
                switch (cur())
                {
                case '"':
                    val += '"';
                    break;
                case 'n':
                    val += '\n';
                    break;
                case 't':
                    val += '\t';
                    break;
                case '\\':
                    val += '\\';
                    break;
                default:
                    emit_error(
                        std::format("Unknown escape sequence: \\{}", cur()));
                    val += cur();
                    break;
                }
            }
            else
                val += cur();
            walk();
        }
        if (is_eof())
        {
            emit_error("Unexpected end of file");
            return make_eof_token();
        }
        walk();
        return create_token(TokenKind::StringLit, val);
    }

    Token Lexer::make_symbol_token(TokenKind kind)
    {
        walk();
        return create_token(kind);
    }

    Token Lexer::make_double_symbol_token(TokenKind kind)
    {
        walk();
        walk();
        return create_token(kind);
    }

    Token Lexer::make_error_token(const std::string& message)
    {
        walk();
        errors_.push_back({ message, line_, col_ });
        return create_token(TokenKind::Error);
    }

    void Lexer::emit_error(const std::string& message)
    {
        errors_.push_back({ message, line_, col_ });
    }

    Token Lexer::make_eof_token()
    {
        return create_token(TokenKind::Eof);
    }

    Token Lexer::make_newline_token()
    {
        reset();
        return create_token(TokenKind::Newline);
    }

    Token Lexer::make_token_comment()

    {
        while (!is_eof() && cur() != '\n')
            pos_++;
        if (!is_eof())
            reset();
        return create_token(TokenKind::Comment);
    }

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

    void Lexer::debug_lexer(const std::vector<Token>& tokens) const
    {
        int count = 1;
        for (auto tok : tokens)
        {
            std::cout << count << ":" << std::endl
                      << "\t Kind: " << to_string(tok.kind) << std::endl
                      << "\t Value: " << tok.value << std::endl
                      << "\t Col, Line: " << tok.col << ", " << tok.line
                      << std::endl;
            count++;
        }
    }

} // namespace lexer
