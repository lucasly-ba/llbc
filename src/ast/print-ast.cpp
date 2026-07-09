#include <ast/all.h>
#include <ast/print-ast.h>
#include <exp.h>
#include <stmt.h>

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

    std::ostream& operator<<(std::ostream& os, Stmt& stmt)
    {
        PrintAst printer(os);
        stmt.accept(printer);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Dec& dec)
    {
        PrintAst printer(os);
        dec.accept(printer);
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
        const auto& args = e.args_get();
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (i != 0)
                ostr_ << ", ";
            ostr_ << args.at(i)->name_get() << ": "
                  << to_string(args.at(i)->type_get().value());
        }
        ostr_ << ")";
        if (e.has_type())
            ostr_ << " ->" << to_string(e.type_get().value());
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << *stmt;
        ostr_ << "}\n";
    }

    void PrintAst::visit(SceneDec& e)
    {
        ostr_ << "scene " << e.name_get();
        if (e.has_max_players())
            ostr_ << " max " << e.max_players_get().value();
        if (auto precond = e.precondition_get())
            ostr_ << " requires " << *precond;
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << *stmt;
        ostr_ << "}\n";
    }

    void PrintAst::visit(PlayerDec& e)
    {
        ostr_ << "player " << e.name_get();
        ostr_ << "\n{\n";
        ostr_ << "\t" << "dollars: " << e.dollar_get() << ",\n";
        ostr_ << "\t" << "chance: " << e.chance_get() << ",\n";
        ostr_ << "\t" << "streak: " << e.streak_get() << "\n";
        ostr_ << "}\n\n";
    }

    void PrintAst::visit(OpExp& e)
    {
        ostr_ << "(" << e.left_get() << e.to_string(e.oper_get())
              << e.right_get() << ")";
    }

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
        const auto& args = e.args_get();
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (i != 0)
                ostr_ << ", ";
            ostr_ << *args.at(i);
        }
        ostr_ << ")";
    }

    void PrintAst::visit(IdentExp& e)
    {
        ostr_ << e.name_get();
    }

    void PrintAst::visit(VarStmt& e)
    {
        ostr_ << e.vardec_get();
    }

    void PrintAst::visit(IfStmt& e)
    {
        ostr_ << "if " << e.condition_get();
        ostr_ << "\n{\n";
        for (auto& stmt : e.then_branch_get())
            ostr_ << "\t" << *stmt;
        ostr_ << "}";
        if (e.else_branch_get().empty() == false)
        {
            ostr_ << "\n";
            ostr_ << "else";
            ostr_ << "\n{\n";
            for (auto& stmt : e.else_branch_get())
                ostr_ << "\t" << *stmt;
            ostr_ << "}";
        }
        ostr_ << "\n";
    }

    void PrintAst::visit(LoopStmt& e)
    {
        ostr_ << "loop";
        ostr_ << "\n{\n";
        for (auto& stmt : e.body_get())
            ostr_ << "\t" << *stmt;
        ostr_ << "}\n";
    }

    void PrintAst::visit(BreakStmt& e)
    {
        (void)e;
        ostr_ << "break;\n";
    }

    void PrintAst::visit(ReturnStmt& e)
    {
        ostr_ << "return";
        if (e.value_get())
            ostr_ << " " << *e.value_get();
        ostr_ << ";\n";
    }

    void PrintAst::visit(EntersStmt& e)
    {
        ostr_ << e.player_name_get() << " enters " << e.scene_name_get()
              << ";\n";
    }

    void PrintAst::visit(StartStmt& e)
    {
        ostr_ << "start " << e.scene_name_get() << ";\n";
    }

    void PrintAst::visit(ExpStmt& e)
    {
        ostr_ << e.exp_get() << ";\n";
    }

} // namespace ast
