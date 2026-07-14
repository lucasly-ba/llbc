#pragma once

#include <ast/ast-visitor.h>
#include <gbir/all.h>
#include <gbir/module.h>
#include <memory>
#include <unordered_map>

#include "gbir/top-level.h"

namespace gbir
{
    using namespace ast;

    class GbirGen : public AstVisitor
    {
    public:
        GbirGen() = default;
        void generate_gbir(ast::Program& program);

        GbirModule& module_get();

    private:
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

        void visit(AssignStmt& e) override;
        void visit(IfStmt& e) override;
        void visit(LoopStmt& e) override;
        void visit(BreakStmt& e) override;
        void visit(ReturnStmt& e) override;
        void visit(EntersStmt& e) override;
        void visit(StartStmt& e) override;

    private:
        std::unordered_map<VarDec*, GbirValue> map_var_;
        std::unordered_map<VarDec*, std::string> global_map_var_;
        GbirModule module_;
        std::vector<std::unique_ptr<GbirBasicBlock>>* current_blocks_ = nullptr;
        GbirBasicBlock* current_block_ = nullptr;
        std::vector<GbirBasicBlock*> loop_exit_stack_;
        GbirValue current_value_;
        int next_value_id_ = 1;
        int next_bb_label_id_ = 0;
    };

} // namespace gbir
