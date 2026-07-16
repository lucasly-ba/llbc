#include <ast/dec.h>
#include <ast/exp.h>
#include <ast/type.h>
#include <gbir-gen/factory.h>
#include <gbir-gen/gbir-gen.h>
#include <gbir/basic-block.h>
#include <gbir/inst/terminator.h>
#include <gbir/value.h>
#include <memory>
#include <string>

namespace gbir
{
    void GbirGen::generate_gbir(ast::Program& program)
    {
        for (auto& dec : program.decs_get())
            dec->accept(*this);
    }

    GbirModule& GbirGen::module_get()
    {
        return module_;
    }

    void GbirGen::visit(VarDec& e)
    {
        if (e.is_top_level_get())
        {
            next_value_id_ = 0;
            auto scratch = make_GbirBasicBlock("global_init");
            auto* saved_block = current_block_;
            current_block_ = scratch.get();
            e.init_get()->accept(*this);
            current_block_ = saved_block;

            module_.add_top_level(make_GbirGlobalVar(
                e.name_get(), e.type_get().value(),
                std::move(scratch->instructions_get().back())));
            global_map_var_[&e] = e.name_get();
        }
        else
        {
            auto value = GbirValue(next_value_id_++, e.type_get().value());
            current_block_->add_instruction(
                make_AllocaInst(e.type_get().value(), value));

            e.init_get()->accept(*this);
            current_block_->add_instruction(
                make_StoreInst(value, current_value_));
            map_var_[&e] = value;
        }
    }

    void GbirGen::visit(FuncDec& e)
    {
        next_value_id_ = 0;
        map_var_.clear();

        std::vector<GbirValue> args;
        for (auto& arg : e.args_get())
            args.push_back({ next_value_id_++, arg->type_get().value() });

        auto func = make_GbirFunction(e.name_get(), args, e.type_get(), {});
        current_blocks_ = &func->blocks_get();

        auto entry =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        current_block_ = entry.get();
        current_blocks_->push_back(std::move(entry));

        const auto& params = e.args_get();
        for (size_t i = 0; i < params.size(); ++i)
        {
            GbirValue slot(next_value_id_++, params.at(i)->type_get().value());
            current_block_->add_instruction(
                make_AllocaInst(params.at(i)->type_get().value(), slot));
            current_block_->add_instruction(make_StoreInst(slot, args.at(i)));
            map_var_[params.at(i).get()] = slot;
        }

        for (auto& stmt : e.body_get())
            stmt->accept(*this);

        if (!current_block_->has_terminator())
        {
            GbirValue void_value(next_value_id_++, ast::Type::Void);
            current_block_->terminator_set(
                std::make_unique<ReturnInst>(void_value));
        }

        next_bb_label_id_ = 0;
        func->next_value_id_set(next_value_id_);
        module_.add_top_level(std::move(func));
        current_blocks_ = nullptr;
        current_block_ = nullptr;
    }

    void GbirGen::visit(SceneDec& e)
    {
        next_value_id_ = 0;
        map_var_.clear();

        auto scene = make_GbirScene(e.name_get(), {});
        scene->max_players_set(e.max_players_get());

        if (auto precond = e.precondition_get())
        {
            current_blocks_ = &scene->precondition_get();
            auto pre = make_GbirBasicBlock("pre0");
            current_block_ = pre.get();
            current_blocks_->push_back(std::move(pre));
            precond->accept(*this);
            scene->precondition_result_set(current_value_);
        }

        current_blocks_ = &scene->blocks_get();
        auto entry =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        current_block_ = entry.get();
        current_blocks_->push_back(std::move(entry));

        for (auto& stmt : e.body_get())
            stmt->accept(*this);

        if (!current_block_->has_terminator())
        {
            GbirValue void_value(next_value_id_++, ast::Type::Void);
            current_block_->terminator_set(
                std::make_unique<ReturnInst>(void_value));
        }

        next_bb_label_id_ = 0;
        scene->next_value_id_set(next_value_id_);
        module_.add_top_level(std::move(scene));
        current_blocks_ = nullptr;
        current_block_ = nullptr;
    }

    void GbirGen::visit(PlayerDec& e)
    {
        auto dollar = dynamic_cast<DollarsExp*>(&e.dollar_get())->value_get();
        auto chance = dynamic_cast<ChanceExp*>(&e.chance_get())->value_get();
        auto streak = dynamic_cast<StreakExp*>(&e.streak_get())->value_get();
        module_.add_top_level(
            make_GbirPlayer(e.name_get(), dollar, chance, streak));
    }

    void GbirGen::visit(OpExp& e)
    {
        e.left_get().accept(*this);
        auto left = current_value_;
        e.right_get().accept(*this);
        auto right = current_value_;

        ast::Type result_type;
        switch (e.oper_get())
        {
        case OpExp::Oper::ADD:
            if (left.type_get() == ast::Type::String)
                result_type = ast::Type::String;
            else
                result_type = left.type_get();
            break;
        case OpExp::Oper::SUB:
        case OpExp::Oper::MUL:
        case OpExp::Oper::DIV:
            result_type = left.type_get();
            break;
        case OpExp::Oper::EQ:
        case OpExp::Oper::NEQ:
        case OpExp::Oper::LT:
        case OpExp::Oper::LEQ:
        case OpExp::Oper::GT:
        case OpExp::Oper::GEQ:
        case OpExp::Oper::AND:
        case OpExp::Oper::OR:
            result_type = ast::Type::Bool;
            break;
        }

        GbirValue result(next_value_id_++, result_type);
        current_block_->add_instruction(
            make_BinopInst(left, e.oper_get(), right, result));
        current_value_ = result;
    }

    void GbirGen::visit(IntExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Int);
        current_block_->add_instruction(
            std::make_unique<ConstIntInst>(e.value_get(), result));
        current_value_ = result;
    }

    void GbirGen::visit(FloatExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Float);
        current_block_->add_instruction(
            std::make_unique<ConstFloatInst>(e.value_get(), result));
        current_value_ = result;
    }
    void GbirGen::visit(StringExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::String);
        current_block_->add_instruction(
            std::make_unique<ConstStringInst>(e.value_get(), result));
        current_value_ = result;
    }
    void GbirGen::visit(BoolExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Bool);
        current_block_->add_instruction(
            std::make_unique<ConstBoolInst>(e.value_get(), result));
        current_value_ = result;
    }
    void GbirGen::visit(DollarsExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Dollars);
        current_block_->add_instruction(
            std::make_unique<ConstDollarsInst>(e.value_get(), result));
        current_value_ = result;
    }
    void GbirGen::visit(ChanceExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Chance);
        current_block_->add_instruction(
            std::make_unique<ConstChanceInst>(e.value_get(), result));
        current_value_ = result;
    }
    void GbirGen::visit(StreakExp& e)
    {
        GbirValue result(next_value_id_++, ast::Type::Streak);
        current_block_->add_instruction(
            std::make_unique<ConstStreakInst>(e.value_get(), result));
        current_value_ = result;
    }

    void GbirGen::visit(CallExp& e)
    {
        std::vector<GbirValue> args;
        for (auto& arg : e.args_get())
        {
            arg->accept(*this);
            args.push_back(current_value_);
        }

        ast::Type return_type = dynamic_cast<FuncDec*>(e.def_get())->type_get();
        GbirValue result(next_value_id_++, return_type);

        auto inst = make_CallInst(e.name_get(), args, result);
        current_block_->add_instruction(std::move(inst));
        current_value_ = result;
    }

    void GbirGen::visit(IdentExp& e)
    {
        auto def = dynamic_cast<VarDec*>(e.def_get());
        if (auto value = map_var_.find(def); value != map_var_.end())
        {
            GbirValue result(next_value_id_++, def->type_get().value());
            current_block_->add_instruction(
                make_LoadInst(value->second, result));
            current_value_ = result;
        }
        else
        {
            GbirValue addr(next_value_id_++, def->type_get().value());
            current_block_->add_instruction(
                make_GlobalAddrInst(def->name_get(), addr));
            GbirValue result(next_value_id_++, def->type_get().value());
            current_block_->add_instruction(make_LoadInst(addr, result));
            current_value_ = result;
        }
    }

    void GbirGen::visit(AssignStmt& e)
    {
        auto value = map_var_.find(dynamic_cast<VarDec*>(e.def_get()));
        e.value_get().accept(*this);
        current_block_->add_instruction(
            make_StoreInst(value->second, current_value_));
    }

    void GbirGen::visit(IfStmt& e)
    {
        e.condition_get().accept(*this);
        auto cond = current_value_;

        auto bb_then =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        auto bb_else =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        auto bb_merge =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));

        auto then_ptr = bb_then.get();
        auto else_ptr = bb_else.get();
        auto merge_ptr = bb_merge.get();

        add_edge(current_block_, then_ptr);
        add_edge(current_block_, else_ptr);

        current_block_->terminator_set(
            std::make_unique<CondBranchInst>(cond, then_ptr, else_ptr));

        current_blocks_->push_back(std::move(bb_then));
        current_block_ = then_ptr;
        for (auto& stmt : e.then_branch_get())
            stmt->accept(*this);
        if (!current_block_->has_terminator())
        {
            add_edge(current_block_, merge_ptr);
            current_block_->terminator_set(
                std::make_unique<BranchInst>(merge_ptr));
        }
        current_blocks_->push_back(std::move(bb_else));
        current_block_ = else_ptr;
        for (auto& stmt : e.else_branch_get())
            stmt->accept(*this);
        if (!current_block_->has_terminator())
        {
            add_edge(current_block_, merge_ptr);
            current_block_->terminator_set(
                std::make_unique<BranchInst>(merge_ptr));
        }
        current_blocks_->push_back(std::move(bb_merge));
        current_block_ = merge_ptr;
    }

    void GbirGen::visit(LoopStmt& e)
    {
        auto bb_loop =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        auto bb_after =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        auto loop_ptr = bb_loop.get();
        auto after_ptr = bb_after.get();
        add_edge(current_block_, loop_ptr);
        current_block_->terminator_set(std::make_unique<BranchInst>(loop_ptr));

        current_blocks_->push_back(std::move(bb_loop));
        current_block_ = loop_ptr;
        loop_exit_stack_.push_back(after_ptr);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
        loop_exit_stack_.pop_back();
        if (!current_block_->has_terminator())
        {
            add_edge(current_block_, loop_ptr);
            current_block_->terminator_set(
                std::make_unique<BranchInst>(loop_ptr));
        }

        current_blocks_->push_back(std::move(bb_after));
        current_block_ = after_ptr;
    }

    void GbirGen::visit(BreakStmt& e)
    {
        (void)e;
        add_edge(current_block_, loop_exit_stack_.back());
        current_block_->terminator_set(
            std::make_unique<BranchInst>(loop_exit_stack_.back()));

        auto bb_dead =
            make_GbirBasicBlock("bb" + std::to_string(next_bb_label_id_++));
        auto dead_ptr = bb_dead.get();
        current_blocks_->push_back(std::move(bb_dead));
        current_block_ = dead_ptr;
    }

    void GbirGen::visit(ReturnStmt& e)
    {
        if (e.value_get())
        {
            e.value_get()->accept(*this);
            current_block_->terminator_set(
                std::make_unique<ReturnInst>(current_value_));
        }
        else
        {
            GbirValue void_value(next_value_id_++, ast::Type::Void);
            current_block_->terminator_set(
                std::make_unique<ReturnInst>(void_value));
        }
    }

    void GbirGen::visit(EntersStmt& e)
    {
        auto inst = make_EnterInst(e.player_name_get(), e.scene_name_get());
        current_block_->add_instruction(std::move(inst));
    }

    void GbirGen::visit(StartStmt& e)
    {
        auto inst = make_StartInst(e.scene_name_get());
        current_block_->add_instruction(std::move(inst));
    }

    void GbirGen::add_edge(GbirBasicBlock* from, GbirBasicBlock* to)
    {
        from->add_successor(to);
        to->add_predecessor(from);
    }

} // namespace gbir
