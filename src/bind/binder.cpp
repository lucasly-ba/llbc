#include <ast/all.h>
#include <binder.h>
#include <dec.h>
#include <set>
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
                emit_error("Declaration redeclaration at top-level: "
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
            emit_error("Main scene not found", Location{ 0, 0 });
        if (!has_player)
            emit_error("No player declared", Location{ 0, 0 });
    }

    void Binder::visit(VarDec& e)
    {
        if (scope_.get_dec_in_last_scope(e.name_get()) == nullptr)
            scope_.put_dec(e.name_get(), &e);
        else
            emit_error("Variable redeclaration: " + e.name_get(),
                       e.location_get());
        MainVisitor::visit(e);
    }

    void Binder::visit(FuncDec& e)
    {
        scope_.scope_begin();
        MainVisitor::visit(e);
        scope_.scope_end();
    }

    void Binder::visit(SceneDec& e)
    {
        if (e.name_get() == "main")
            has_main_ = true;
        scope_.scope_begin();
        MainVisitor::visit(e);
        scope_.scope_end();
    }

    void Binder::visit(CallExp& e)
    {
        if (auto dec = scope_.get_dec_in_first_scope(e.name_get());
            dec != nullptr)
            e.def_set(dec);
        else
            emit_error("Undefined function: " + e.name_get(), e.location_get());
        MainVisitor::visit(e);
    }

    void Binder::visit(IdentExp& e)
    {
        if (auto dec = scope_.get_dec(e.name_get()); dec != nullptr)
            e.def_set(dec);
        else
            emit_error("Undefined variable: " + e.name_get(), e.location_get());
    }

    void Binder::visit(LoopStmt& e)
    {
        auto saved_loop = loop_;
        loop_ = &e;
        scope_.scope_begin();
        MainVisitor::visit(e);
        scope_.scope_end();
        loop_ = saved_loop;
    }

    void Binder::visit(BreakStmt& e)
    {
        if (loop_ == nullptr)
            emit_error("Break outside loop", e.location_get());
    }

    void Binder::visit(EntersStmt& e)
    {
        if (auto dec = scope_.get_dec_in_first_scope(e.player_name_get());
            dec != nullptr)
            e.player_def_set(dec);
        else
            emit_error("Undefined player: " + e.player_name_get(),
                       e.location_get());
        if (auto dec = scope_.get_dec_in_first_scope(e.scene_name_get());
            dec != nullptr)
            e.scene_def_set(dec);
        else
            emit_error("Undefined scene: " + e.scene_name_get(),
                       e.location_get());
    }

    void Binder::visit(StartStmt& e)
    {
        if (e.scene_name_get() == "main")
        {
            emit_error("Cannot manually start main scene", e.location_get());
            return;
        }
        if (auto dec = scope_.get_dec_in_first_scope(e.scene_name_get());
            dec != nullptr)
            e.scene_def_set(dec);
        else
            emit_error("Undefined scene: " + e.scene_name_get(),
                       e.location_get());
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
