#pragma once

#include <ast/ast-visitor.h>

namespace ast
{
    class PrintAst : public AstVisitor
    {
    public:
        PrintAst(std::ostream& ostr);
        PrintAst(std::ostream& ostr, bool bindings);

        void visit(VarDec& e) override;
        void visit(FuncDec& e) override;
        void visit(SceneDec& e) override;
        void visit(PlayerDec& e) override;

        void visit(OpExp& e) override;
        void visit(IntExp& e) override;
        void visit(FloatExp& e) override;
        void visit(StringExp& e) override;
        void visit(BoolExp& e) override;
        void visit(DollarsExp& e) override;
        void visit(ChanceExp& e) override;
        void visit(StreakExp& e) override;
        void visit(CallExp& e) override;
        void visit(IdentExp& e) override;

        void visit(VarStmt& e) override;
        void visit(AssignStmt& e) override;
        void visit(IfStmt& e) override;
        void visit(LoopStmt& e) override;
        void visit(BreakStmt& e) override;
        void visit(ReturnStmt& e) override;
        void visit(EntersStmt& e) override;
        void visit(StartStmt& e) override;
        void visit(ExpStmt& e) override;

    private:
        bool bindings() const;
        void print_def(const Dec& dec);
        void print_binding(const Dec* def);

        std::ostream& ostr_;
    };

    std::ostream& operator<<(std::ostream& os, Exp& e);
    std::ostream& operator<<(std::ostream& os, Stmt& e);
    std::ostream& operator<<(std::ostream& os, Dec& e);
} // namespace ast
