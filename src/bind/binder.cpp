#include <bind/binder.h>
#include <set>

#include <ast/stmt.h>
namespace bind
{

    void Binder::bind_program(ast::Program& program)
    {
        scope_.scope_begin();
        std::set<std::string> names;
        bool has_player = false;
        for (auto& dec : program.decs_get())
        {
            if (!names.insert(dec->name_get()).second)
                emit_error("declaration redeclaration at top-level: "
                               + dec->name_get(),
                           dec->location_get());

            if (dynamic_cast<PlayerDec*>(dec.get()))
                has_player = true;
            if (!dynamic_cast<VarDec*>(dec.get()))
                scope_.put_dec(dec->name_get(), dec.get());
        }
        for (auto& dec : program.decs_get())
            dec->accept(*this);
        if (!has_main_)
            emit_error("main scene not found", Location{ 0, 0 });
        if (!has_player)
            emit_error("no player declared", Location{ 0, 0 });
    }

    void Binder::visit(VarDec& e)
    {
        if (scope_.get_dec_in_last_scope(e.name_get()) == nullptr)
            scope_.put_dec(e.name_get(), &e);
        else
            emit_error("variable redeclaration: " + e.name_get(),
                       e.location_get());
        AstVisitor::visit(e);
    }

    void Binder::visit(FuncDec& e)
    {
        func_ = &e;
        scope_.scope_begin();
        AstVisitor::visit(e);
        scope_.scope_end();
        func_ = nullptr;
    }

    void Binder::visit(SceneDec& e)
    {
        if (e.name_get() == "main")
            has_main_ = true;
        scope_.scope_begin();
        AstVisitor::visit(e);
        scope_.scope_end();
    }

    void Binder::visit(CallExp& e)
    {
        if (auto dec = scope_.get_dec_in_first_scope(e.name_get());
            dec == nullptr)
            emit_error("undefined function: " + e.name_get(), e.location_get());
        else if (dynamic_cast<FuncDec*>(dec) == nullptr)
            emit_error(e.name_get() + " is not a function", e.location_get());
        else
            e.def_set(dec);
        AstVisitor::visit(e);
    }

    void Binder::visit(IdentExp& e)
    {
        if (auto dec = scope_.get_dec(e.name_get()); dec != nullptr)
            e.def_set(dec);
        else
            emit_error("undefined variable: " + e.name_get(), e.location_get());
    }

    void Binder::visit(AssignStmt& e)
    {
        if (auto dec = scope_.get_dec(e.name_get()); dec == nullptr)
            emit_error("undefined variable: " + e.name_get(), e.location_get());
        else if (dynamic_cast<VarDec*>(dec) == nullptr)
            emit_error(e.name_get() + " is not a variable", e.location_get());
        else
            e.def_set(dec);
        AstVisitor::visit(e);
    }

    void Binder::visit(LoopStmt& e)
    {
        auto saved_loop = loop_;
        loop_ = &e;
        scope_.scope_begin();
        AstVisitor::visit(e);
        scope_.scope_end();
        loop_ = saved_loop;
    }

    void Binder::visit(BreakStmt& e)
    {
        if (loop_ == nullptr)
            emit_error("break outside loop", e.location_get());
    }

    void Binder::visit(EntersStmt& e)
    {
        if (auto dec = scope_.get_dec_in_first_scope(e.player_name_get());
            dec != nullptr)
            e.player_def_set(dec);
        else
            emit_error("undefined player: " + e.player_name_get(),
                       e.location_get());
        if (auto dec = scope_.get_dec_in_first_scope(e.scene_name_get());
            dec != nullptr)
            e.scene_def_set(dec);
        else
            emit_error("undefined scene: " + e.scene_name_get(),
                       e.location_get());
    }

    void Binder::visit(StartStmt& e)
    {
        if (e.scene_name_get() == "main")
        {
            emit_error("cannot manually start main scene", e.location_get());
            return;
        }
        if (auto dec = scope_.get_dec_in_first_scope(e.scene_name_get());
            dec != nullptr)
            e.scene_def_set(dec);
        else
            emit_error("undefined scene: " + e.scene_name_get(),
                       e.location_get());
    }

    void Binder::visit(ReturnStmt& e)
    {
        if (func_ == nullptr)
            emit_error("return outside function", e.location_get());
        AstVisitor::visit(e);
    }

    const std::vector<BindError>& Binder::get_errors() const
    {
        return errors_;
    }

    bool Binder::has_error() const
    {
        return !errors_.empty();
    }

    void Binder::emit_error(const std::string& message, Location loc)
    {
        errors_.push_back({ message, loc });
    }

} // namespace bind
