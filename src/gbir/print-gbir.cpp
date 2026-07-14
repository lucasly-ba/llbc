#include <ast/exp.h>
#include <ast/type.h>
#include <gbir/all.h>
#include <gbir/print-gbir.h>

namespace gbir
{
    std::string oper_to_string(ast::OpExp::Oper op)
    {
        switch (op)
        {
        case ast::OpExp::Oper::ADD:
            return "add";
        case ast::OpExp::Oper::SUB:
            return "sub";
        case ast::OpExp::Oper::MUL:
            return "mul";
        case ast::OpExp::Oper::DIV:
            return "div";
        case ast::OpExp::Oper::EQ:
            return "eq";
        case ast::OpExp::Oper::NEQ:
            return "neq";
        case ast::OpExp::Oper::LT:
            return "lt";
        case ast::OpExp::Oper::LEQ:
            return "leq";
        case ast::OpExp::Oper::GT:
            return "gt";
        case ast::OpExp::Oper::GEQ:
            return "geq";
        case ast::OpExp::Oper::AND:
            return "and";
        case ast::OpExp::Oper::OR:
            return "or";
        }
        return "unknown";
    }

    PrintGbir::PrintGbir(std::ostream& ostr)
        : ostr_(ostr)
    {}

    void PrintGbir::print(GbirModule& module)
    {
        for (auto& top_level : module.top_levels_get())
            top_level->accept(*this);
    }

    void PrintGbir::print_value(GbirValue value)
    {
        ostr_ << "%" << value.id_get();
    }

    void PrintGbir::print_type(ast::Type type)
    {
        ostr_ << "$" << ast::to_string(type);
    }

    void PrintGbir::print_block(GbirBasicBlock& block)
    {
        ostr_ << block.label_get() << ":\n";
        for (auto& inst : block.instructions_get())
            inst->accept(*this);
        if (block.has_terminator())
            block.terminator_get().accept(*this);
    }

    void PrintGbir::visit(ConstIntInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_int " << e.raw_value_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstFloatInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_float " << e.raw_value_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstStringInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_string \"" << e.raw_value_get() << "\" : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstBoolInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_bool " << (e.raw_value_get() ? "true" : "false")
              << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstDollarsInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_dollars " << e.raw_value_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstChanceInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_chance " << e.raw_value_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(ConstStreakInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = const_streak " << e.raw_value_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(AllocaInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = alloca ";
        print_type(e.type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(LoadInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = load ";
        print_value(e.read_value_get());
        ostr_ << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(StoreInst& e)
    {
        ostr_ << "  store ";
        print_value(e.value_get());
        ostr_ << " to ";
        print_value(e.target_get());
        ostr_ << " : ";
        print_type(e.value_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(BinopInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = binop " << oper_to_string(e.oper_get()) << " ";
        print_value(e.left_get());
        ostr_ << ", ";
        print_value(e.right_get());
        ostr_ << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(GlobalAddrInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = global_addr @" << e.name_get() << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(CallInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = call @" << e.name_get() << "(";
        const auto& args = e.args_get();
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (i != 0)
                ostr_ << ", ";
            print_value(args.at(i));
        }
        ostr_ << ") : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(CondBranchInst& e)
    {
        ostr_ << "  cond_br ";
        print_value(e.condition_get());
        ostr_ << ", " << e.then_bb_get()->label_get() << ", "
              << e.else_bb_get()->label_get() << "\n";
    }

    void PrintGbir::visit(BranchInst& e)
    {
        ostr_ << "  br " << e.target_bb_get()->label_get() << "\n";
    }

    void PrintGbir::visit(ReturnInst& e)
    {
        ostr_ << "  return ";
        print_value(e.value_get());
        ostr_ << " : ";
        print_type(e.value_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(PhiInst& e)
    {
        ostr_ << "  ";
        print_value(e.result_get());
        ostr_ << " = phi ";
        const auto& incoming = e.incoming_get();
        for (size_t i = 0; i < incoming.size(); ++i)
        {
            if (i != 0)
                ostr_ << ", ";
            ostr_ << "[";
            print_value(incoming.at(i).first);
            ostr_ << ", " << incoming.at(i).second->label_get() << "]";
        }
        ostr_ << " : ";
        print_type(e.result_get().type_get());
        ostr_ << "\n";
    }

    void PrintGbir::visit(EnterInst& e)
    {
        ostr_ << "  enter @" << e.player_name_get() << ", @"
              << e.scene_name_get() << "\n";
    }

    void PrintGbir::visit(StartInst& e)
    {
        ostr_ << "  start @" << e.scene_name_get() << "\n";
    }

    void PrintGbir::visit(GbirFunction& e)
    {
        ostr_ << "gbir @" << e.name_get() << "(";
        const auto& args = e.args_get();
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (i != 0)
                ostr_ << ", ";
            print_value(args.at(i));
            ostr_ << " : ";
            print_type(args.at(i).type_get());
        }
        ostr_ << ") -> ";
        print_type(e.return_type_get());
        ostr_ << " {\n";
        for (auto& block : e.blocks_get())
            print_block(*block);
        ostr_ << "}\n\n";
    }

    void PrintGbir::visit(GbirGlobalVar& e)
    {
        ostr_ << "gbir_global @" << e.name_get() << " : ";
        print_type(e.type_get());
        ostr_ << " = {\n";
        if (e.init_get() != nullptr)
            e.init_get()->accept(*this);
        ostr_ << "}\n\n";
    }

    void PrintGbir::visit(GbirPlayer& e)
    {
        ostr_ << "gbir_player @" << e.name_get() << " { dollars "
              << e.dollar_get() << ", chance " << e.chance_get() << ", streak "
              << e.streak_get() << " }\n\n";
    }

    void PrintGbir::visit(GbirScene& e)
    {
        ostr_ << "gbir_scene @" << e.name_get();
        if (e.max_players_get().has_value())
            ostr_ << " max " << e.max_players_get().value();
        if (e.precondition_result_get().has_value())
        {
            ostr_ << " requires ";
            print_value(e.precondition_result_get().value());
        }
        ostr_ << " {\n";
        for (auto& block : e.precondition_get())
            print_block(*block);
        for (auto& block : e.blocks_get())
            print_block(*block);
        ostr_ << "}\n\n";
    }
} // namespace gbir
