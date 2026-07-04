#include <CLI/CLI.hpp>
#include <fstream>
#include <iostream>
#include <lexer.h>
#include <sstream>

int main(int argc, char* argv[])
{
    CLI::App app{ "gblc compiler" };

    std::string input_file;
    bool lex_trace = false;
    bool parse_trace = false;

    app.add_option("file", input_file, "Input .gblc file")->required();
    app.add_flag("--lex-trace", lex_trace, "Trace the lexer");
    app.add_flag("--parse-trace", parse_trace, "Trace the parser");

    CLI11_PARSE(app, argc, argv);

    std::ifstream f(input_file);
    std::ostringstream ss;
    ss << f.rdbuf();
    std::string content = ss.str();

    parser::Lexer lex(lex_trace, content);
    auto tokens = lex.lex_tokens();

    if (lex.has_error())
    {
        for (auto& err : lex.get_errors())
            std::cerr << "error: " << err.message << " at " << err.line << ":"
                      << err.col << "\n";
        return 1;
    }
}
