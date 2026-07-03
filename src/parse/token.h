#pragma once
#include <string>
#include <unordered_map>

enum class TokenKind
{

    // Key words
    Let,
    Function,
    Requires,
    Scene,
    Entry,
    If,
    Else,
    Loop,
    Break,
    Return,
    Match,
    Player,

    // Types
    Int,
    Float,
    String,
    Bool,
    Dollar,
    Chance,
    Reputation,

    // Builtins
    Say,
    Ask,
    Roll,
    Flip,
    Draw,
    Gain,
    Lose,
    Enter,

    // Arithmetic ops
    Plus,
    Minus,
    Mul,
    Div,

    // Compare ops
    Eq,
    EqEq,
    Neq,
    Lt,
    Gt,
    Leq,
    Geq,

    // Symbols
    LPar,
    RPar,
    Colon,
    Arrow,
    Comma,
    Newline,

    // Lits
    IntLit,
    FloatLit,
    StringLit,
    BoolLit,
    DollarsLit,
    ChanceLit,
    ReputationLit,

    // Others
    ID,
    Eof,
    Comment,
    Error,
};

struct Token
{
    TokenKind kind;
    std::string value;
    size_t line;
    size_t col;
};

inline const std::unordered_map<std::string, TokenKind> keywords = {
    { "let", TokenKind::Let },
    { "fn", TokenKind::Function },
    { "requires", TokenKind::Requires },
    { "scene", TokenKind::Scene },
    { "if", TokenKind::If },
    { "else", TokenKind::Else },
    { "loop", TokenKind::Loop },
    { "break", TokenKind::Break },
    { "return", TokenKind::Return },
    { "match", TokenKind::Match },
    { "int", TokenKind::Int },
    { "float", TokenKind::Float },
    { "string", TokenKind::String },
    { "bool", TokenKind::Bool },
    { "dollar", TokenKind::Dollar },
    { "chance", TokenKind::Chance },
    { "reputation", TokenKind::Reputation },
    { "true", TokenKind::BoolLit },
    { "false", TokenKind::BoolLit },
    { "dollar", TokenKind::Dollar },
    { "chance", TokenKind::Chance },
    { "say", TokenKind::Say },
    { "ask", TokenKind::Ask },
    { "roll", TokenKind::Roll },
    { "flip", TokenKind::Flip },
    { "draw", TokenKind::Draw },
    { "gain", TokenKind::Gain },
    { "lose", TokenKind::Lose },
    { "enter", TokenKind::Enter },
};

inline TokenKind player_info_kind(char c)
{
    switch (c)
    {
    case '$':
        return TokenKind::DollarsLit;
    case '%':
        return TokenKind::ChanceLit;
    case '*':
        return TokenKind::ReputationLit;
    default:
        return TokenKind::Error;
    }
}

inline std::string to_string(TokenKind kind)
{
    switch (kind)
    {
    case TokenKind::Let:
        return "Let";
    case TokenKind::Function:
        return "Function";
    case TokenKind::Requires:
        return "Requires";
    case TokenKind::Scene:
        return "Scene";
    case TokenKind::If:
        return "If";
    case TokenKind::Else:
        return "Else";
    case TokenKind::Loop:
        return "Loop";
    case TokenKind::Break:
        return "Break";
    case TokenKind::Return:
        return "Return";
    case TokenKind::Match:
        return "Match";
    case TokenKind::Int:
        return "Int";
    case TokenKind::Float:
        return "Float";
    case TokenKind::String:
        return "String";
    case TokenKind::Bool:
        return "Bool";
    case TokenKind::Dollar:
        return "Dollar";
    case TokenKind::Chance:
        return "Chance";
    case TokenKind::Reputation:
        return "Reputation";
    case TokenKind::Say:
        return "Say";
    case TokenKind::Ask:
        return "Ask";
    case TokenKind::Roll:
        return "Roll";
    case TokenKind::Flip:
        return "Flip";
    case TokenKind::Draw:
        return "Draw";
    case TokenKind::Gain:
        return "Gain";
    case TokenKind::Lose:
        return "Lose";
    case TokenKind::Enter:
        return "Enter";
    case TokenKind::Plus:
        return "Plus";
    case TokenKind::Minus:
        return "Minus";
    case TokenKind::Mul:
        return "Mul";
    case TokenKind::Div:
        return "Div";
    case TokenKind::Eq:
        return "Eq";
    case TokenKind::EqEq:
        return "EqEq";
    case TokenKind::Neq:
        return "Neq";
    case TokenKind::Lt:
        return "Lt";
    case TokenKind::Gt:
        return "Gt";
    case TokenKind::Leq:
        return "Leq";
    case TokenKind::Geq:
        return "Geq";
    case TokenKind::LPar:
        return "LPar";
    case TokenKind::RPar:
        return "RPar";
    case TokenKind::Colon:
        return "Colon";
    case TokenKind::Arrow:
        return "Arrow";
    case TokenKind::Comma:
        return "Comma";
    case TokenKind::Newline:
        return "Newline";
    case TokenKind::IntLit:
        return "IntLit";
    case TokenKind::StringLit:
        return "StringLit";
    case TokenKind::FloatLit:
        return "FloatLit";
    case TokenKind::BoolLit:
        return "BoolLit";
    case TokenKind::DollarsLit:
        return "DollarsLit";
    case TokenKind::ChanceLit:
        return "ChanceLit";
    case TokenKind::ReputationLit:
        return "ReputationLit";
    case TokenKind::ID:
        return "ID";
    case TokenKind::Eof:
        return "Eof";
    case TokenKind::Comment:
        return "Comment";
    case TokenKind::Error:
        return "Error";
    default:
        return "Unknown";
    }
}
