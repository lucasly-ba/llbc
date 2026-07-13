#include <ast/dec.h>
#include <ast/exp.h>
#include <ast/stmt.h>
#include <ast/type.h>
#include <optional>
#include <type/type-checker.h>

namespace type
{

    void TypeChecker::typecheck_program(ast::Program& program)
    {
        for (auto& dec : program.decs_get())
            dec->accept(*this);
    }

    void TypeChecker::visit(VarDec& e)
    {
        if (Exp* init = e.init_get())
        {
            init->accept(*this);
            if (current_type_ == ast::Type::Void)
            {
                emit_error("cannot assign variable " + e.name_get()
                               + " to void",
                           e.location_get());
                return;
            }

            if (e.has_type())
            {
                if (current_type_ != e.type_get().value())
                    emit_error("declared " + to_string(*e.type_get())
                                   + " but initializer is "
                                   + to_string(current_type_),
                               e.location_get());
            }
            else
                e.type_set(current_type_);
        }
    }
    bool TypeChecker::has_break(const std::vector<stmt_ptr>& stmts)
    {
        for (auto& stmt : stmts)
        {
            if (dynamic_cast<BreakStmt*>(stmt.get()))
                return true;
            if (auto* if_stmt = dynamic_cast<IfStmt*>(stmt.get()))
                if (has_break(if_stmt->then_branch_get())
                    || has_break(if_stmt->else_branch_get()))
                    return true;
        }
        return false;
    }

    bool TypeChecker::check_for_return(const std::vector<stmt_ptr>& stmts)
    {
        for (auto& stmt : stmts)
        {
            if (dynamic_cast<ReturnStmt*>(stmt.get()))
                return true;
            if (auto* loop_stmt = dynamic_cast<LoopStmt*>(stmt.get()))
            {
                if (!has_break(loop_stmt->body_get())
                    && check_for_return(loop_stmt->body_get()))
                    return true;
            }
            if (auto* if_stmt = dynamic_cast<IfStmt*>(stmt.get()))
            {
                if (!if_stmt->else_branch_get().empty()
                    && check_for_return(if_stmt->then_branch_get())
                    && check_for_return(if_stmt->else_branch_get()))
                    return true;
            }
        }
        return false;
    }

    void TypeChecker::visit(FuncDec& e)
    {
        current_return_type_ = e.type_get();
        for (auto& arg : e.args_get())
            arg->accept(*this);
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
        if (current_return_type_ != Type::Void
            && !check_for_return(e.body_get()))
            emit_error("function " + e.name_get() + " must return on all paths",
                       e.location_get());
        current_return_type_ = Type::Void;
    }

    void TypeChecker::visit(SceneDec& e)
    {
        if (auto precond = e.precondition_get())
        {
            precond->accept(*this);
            if (current_type_ != Type::Bool)
                emit_error("scene " + e.name_get()
                               + "'s precondition must be a boolean",
                           precond->location_get());
        }
        for (auto& stmt : e.body_get())
            stmt->accept(*this);
    }

    void TypeChecker::visit(OpExp& e)
    {
        e.left_get().accept(*this);
        auto left_type = current_type_;
        e.right_get().accept(*this);
        auto right_type = current_type_;
        switch (e.oper_get())
        {
        case OpExp::Oper::ADD:
        case OpExp::Oper::SUB:
        case OpExp::Oper::MUL:
        case OpExp::Oper::DIV: {
            auto op_name = e.to_string(e.oper_get());
            if (e.oper_get() == OpExp::Oper::ADD && left_type == Type::String
                && right_type == Type::String)
            {
                current_type_ = Type::String;
                break;
            }
            if (left_type != right_type || left_type == Type::Bool
                || left_type == Type::String)
                emit_error("cannot use '" + op_name + "' between "
                               + to_string(left_type) + " and "
                               + to_string(right_type),
                           e.location_get());
            current_type_ = left_type;
            break;
        }
        case OpExp::Oper::EQ:
        case OpExp::Oper::NEQ:
            if (left_type != right_type)
                emit_error("cannot compare " + to_string(left_type) + " with "
                               + to_string(right_type),
                           e.location_get());
            current_type_ = Type::Bool;
            break;
        case OpExp::Oper::LT:
        case OpExp::Oper::LEQ:
        case OpExp::Oper::GT:
        case OpExp::Oper::GEQ:
            if (left_type == Type::String || left_type == Type::Bool
                || left_type != right_type)
                emit_error("cannot order-compare " + to_string(left_type)
                               + " with " + to_string(right_type),
                           e.location_get());
            current_type_ = Type::Bool;
            break;
        case OpExp::Oper::AND:
        case OpExp::Oper::OR:
            if (left_type != Type::Bool || right_type != Type::Bool)
                emit_error("logical operators require bool operands",
                           e.location_get());
            current_type_ = Type::Bool;
            break;
        }
    }

    void TypeChecker::visit(IntExp& e)
    {
        (void)e;
        current_type_ = Type::Int;
    }

    void TypeChecker::visit(FloatExp& e)
    {
        (void)e;
        current_type_ = Type::Float;
    }
    void TypeChecker::visit(StringExp& e)
    {
        (void)e;
        current_type_ = Type::String;
    }
    void TypeChecker::visit(BoolExp& e)
    {
        (void)e;
        current_type_ = Type::Bool;
    }
    void TypeChecker::visit(DollarsExp& e)
    {
        (void)e;
        current_type_ = Type::Dollars;
    }
    void TypeChecker::visit(ChanceExp& e)
    {
        (void)e;
        current_type_ = Type::Chance;
    }
    void TypeChecker::visit(StreakExp& e)
    {
        (void)e;
        current_type_ = Type::Streak;
    }

    void TypeChecker::visit(CallExp& e)
    {
        auto def = dynamic_cast<const FuncDec*>(e.def_get());
        if (e.args_get().size() < def->args_get().size())
        {
            emit_error("too few arguments to function " + e.name_get(),
                       e.location_get());
            return;
        }
        if (e.args_get().size() > def->args_get().size())
        {
            emit_error("too many arguments to function " + e.name_get(),
                       e.location_get());
            return;
        }
        size_t i = 0;
        for (auto& arg : e.args_get())
        {
            arg->accept(*this);
            auto def_arg = def->args_get()[i].get();
            if (current_type_ != def_arg->type_get())
                emit_error("expected " + to_string(def_arg->type_get().value())
                               + " but argument is of type "
                               + to_string(current_type_),
                           arg->location_get());
            ++i;
        }
        current_type_ = def->type_get();
    }

    void TypeChecker::visit(IdentExp& e)
    {
        if (auto* vardec = dynamic_cast<const VarDec*>(e.def_get()))
        {
            current_type_ = vardec->type_get().value();
            return;
        }
        emit_error(e.name_get()
                       + " is not a variable and cannot be used as a value",
                   e.location_get());
        current_type_ = Type::Int;
    }

    void TypeChecker::visit(AssignStmt& e)
    {
        auto* vardec = dynamic_cast<const VarDec*>(e.def_get());
        if (vardec == nullptr)
        {
            emit_error(e.name_get()
                           + " is not a variable and cannot be assigned to",
                       e.location_get());
            return;
        }
        e.value_get().accept(*this);
        if (current_type_ != vardec->type_get().value())
            emit_error("cannot assign " + to_string(current_type_)
                           + " to variable " + e.name_get() + " of type "
                           + to_string(vardec->type_get().value()),
                       e.location_get());
    }

    void TypeChecker::visit(IfStmt& e)
    {
        e.condition_get().accept(*this);
        if (current_type_ != Type::Bool)
            emit_error("condition in if is not a boolean",
                       e.condition_get().location_get());
        for (auto& stmt : e.then_branch_get())
            stmt->accept(*this);
        for (auto& stmt : e.else_branch_get())
            stmt->accept(*this);
    }

    void TypeChecker::visit(ReturnStmt& e)
    {
        if (!e.has_value() && current_return_type_ == Type::Void)
            return;
        if (!e.has_value() && current_return_type_ != Type::Void)
        {
            emit_error("return with no value, in function returning non-void",
                       e.location_get());
            return;
        }
        if (e.has_value() && current_return_type_ == Type::Void)
        {
            emit_error("returning value, in function returning void",
                       e.location_get());
            return;
        }

        e.value_get()->accept(*this);
        if (current_type_ != current_return_type_)
            emit_error("returning " + to_string(current_type_)
                           + " from a function with return type "
                           + to_string(current_return_type_),
                       e.location_get());
    }

    const std::vector<TypeError>& TypeChecker::get_errors() const
    {
        return errors_;
    }

    bool TypeChecker::has_error() const
    {
        return !errors_.empty();
    }

    void TypeChecker::emit_error(const std::string& message, Location loc)
    {
        errors_.push_back({ message, loc });
    }

} // namespace type
