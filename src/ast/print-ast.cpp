#include <ast/all.h>
#include <ast/print-ast.h>

#include "stmt.h"

namespace ast
{

    PrintAst::PrintAst(std::ostream& ostr)
        : ostr_(ostr)
    {}

    std::ostream& operator<<(std::ostream& os, Exp& e)
    {
        PrintAst printer(os);
        e.accept(printer);
        return os;
    }

    void PrintAst::visit(VarDec& e)
    {
        ostr_ << "var " << e.name_get();
        if (e.has_type())
            ostr_ << ": " << to_string(e.type_get().value());
        ostr_ << " = " << *e.init_get() << ";\n";
    }

    void PrintAst::visit(FuncDec& e)
    {
        ostr_ << "fn " << e.name_get() << "(";
        auto size = e.args_get().size();
        size_t i = 0;
        while (i < size - 1)
        {
            const auto& arg = e.args_get().at(i);
            ostr_ << arg->name_get() << ": " << to_string(e.type_get().value())
                  << ", ";
            ++i;
        }
        if (size != 0)
            ostr_ << e.args_get().at(i)->name_get() << ": "
                  << to_string(e.type_get().value());
        ostr_ << ")";
        if (e.has_type())
            ostr_ << " ->" << to_string(e.type_get().value());
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << stmt << "\n";
        ostr_ << "}\n";
    }

    void PrintAst::visit(SceneDec& e)
    {
        ostr_ << "scene " << e.name_get();
        if (e.has_max_players())
            ostr_ << " max " << e.max_players_get().value();
        if (auto precond = e.precondition_get())
            ostr_ << " requires " << precond;
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << stmt << "\n";
        ostr_ << "}\n";
    }

    void PrintAst::visit(PlayerDec& e)
    {
        ostr_ << "player " << e.name_get();
        ostr_ << "\n{\n";
        ostr_ << "\t" << "dollar: " << e.dollar_get() << ",\n";
        ostr_ << "\t" << "chance: " << e.chance_get() << ",\n";
        ostr_ << "\t" << "streak: " << e.streak_get() << ",\n";
        ostr_ << "}\n\n";
    }

    void PrintAst::visit(OpExp& e)
    {}

    void PrintAst::visit(IntExp& e)
    {
        ostr_ << e.value_get();
    }

    void PrintAst::visit(FloatExp& e)
    {
        ostr_ << e.value_get();
    }
    void PrintAst::visit(StringExp& e)
    {
        ostr_ << e.value_get();
    }
    void PrintAst::visit(BoolExp& e)
    {
        ostr_ << e.value_get();
    }
    void PrintAst::visit(DollarsExp& e)
    {
        ostr_ << e.value_get() << "$";
    }
    void PrintAst::visit(ChanceExp& e)
    {
        ostr_ << e.value_get() << "%";
    }
    void PrintAst::visit(StreakExp& e)
    {
        ostr_ << e.value_get() << "x";
    }

    void PrintAst::visit(CallExp& e)
    {
        ostr_ << e.name_get() << "(";
        auto size = e.args_get().size();
        size_t i = 0;
        while (i < size - 1)
        {
            const auto& arg = e.args_get().at(i);
            ostr_ << arg << ", ";
            ++i;
        }
        if (size != 0)
            ostr_ << e.args_get().at(i);
        ostr_ << ");";
    }

    void PrintAst::visit(IdentExp& e)
    {
        ostr_ << e.name_get();
    }

    void PrintAst::visit(VarStmt& e)
    {
        ostr_ << &e.vardec_get() << ";";
    }

    void PrintAst::visit(IfStmt& e)
    {
        ostr_ << "if " << &e.condition_get();
        ostr_ << "\n{\n";
        for (auto& stmt : e.then_branch_get())
            ostr_ << "\t" << stmt << "\n";
        ostr_ << "}";
        if (e.else_branch_get().empty() == false)
        {
            ostr_ << "\n";
            ostr_ << "else";
            ostr_ << "\n{\n";
            for (auto& stmt : e.else_branch_get())
                ostr_ << "\t" << stmt << "\n";
            ostr_ << "}";
        }
    }

    void PrintAst::visit(LoopStmt& e)
    {
        ostr_ << "loop";
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << stmt << "\n";
        ostr_ << "}";
    }

    void PrintAst::visit(BreakStmt& e)
    {
        (void)e;
        ostr_ << "break;";
    }

    void PrintAst::visit(ReturnStmt& e)
    {
        ostr_ << "return " << e.value_get() << ";";
    }

    void PrintAst::visit(ExpStmt& e)
    {
        ostr_ << &e.exp_get() << ";";
    }

} // namespace ast
