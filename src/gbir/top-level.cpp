#include <gbir/top-level.h>
#include <memory>
#include <vector>

#include "gbir/basic-block.h"

namespace gbir
{
    GbirFunction::GbirFunction(
        std::string name, std::vector<GbirValue> args, ast::Type return_type,
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks)
        : name_(std::move(name))
        , args_(std::move(args))
        , return_type_(return_type)
        , blocks_(std::move(blocks))
    {}

    void GbirFunction::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& GbirFunction::name_get() const
    {
        return name_;
    }

    void GbirFunction::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const std::vector<GbirValue>& GbirFunction::args_get() const
    {
        return args_;
    }

    void GbirFunction::args_set(std::vector<GbirValue> args)
    {
        args_ = std::move(args);
    }

    ast::Type GbirFunction::return_type_get() const
    {
        return return_type_;
    }

    void GbirFunction::return_type_set(ast::Type return_type)
    {
        return_type_ = return_type;
    }

    const std::vector<std::unique_ptr<GbirBasicBlock>>&
    GbirFunction::blocks_get() const
    {
        return blocks_;
    }

    std::vector<std::unique_ptr<GbirBasicBlock>>& GbirFunction::blocks_get()
    {
        return blocks_;
    }

    int GbirFunction::next_value_id_get() const
    {
        return next_value_id_;
    }

    void GbirFunction::next_value_id_set(int next_value_id)
    {
        next_value_id_ = next_value_id;
    }

    GbirGlobalVar::GbirGlobalVar(std::string name, ast::Type type,
                                 std::unique_ptr<GbirInst> init)
        : name_(std::move(name))
        , type_(type)
        , init_(std::move(init))
    {}

    void GbirGlobalVar::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& GbirGlobalVar::name_get() const
    {
        return name_;
    }

    void GbirGlobalVar::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    ast::Type GbirGlobalVar::type_get() const
    {
        return type_;
    }

    void GbirGlobalVar::type_set(ast::Type type)
    {
        type_ = type;
    }

    GbirInst* GbirGlobalVar::init_get() const
    {
        return init_.get();
    }

    void GbirGlobalVar::init_set(std::unique_ptr<GbirInst> init)
    {
        init_ = std::move(init);
    }

    GbirPlayer::GbirPlayer(std::string name, int dollar, int chance, int streak)
        : name_(std::move(name))
        , dollar_(dollar)
        , chance_(chance)
        , streak_(streak)
    {}

    void GbirPlayer::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& GbirPlayer::name_get() const
    {
        return name_;
    }

    void GbirPlayer::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    int GbirPlayer::dollar_get() const
    {
        return dollar_;
    }

    void GbirPlayer::dollar_set(int dollar)
    {
        dollar_ = dollar;
    }

    int GbirPlayer::chance_get() const
    {
        return chance_;
    }

    void GbirPlayer::chance_set(int chance)
    {
        chance_ = chance;
    }

    int GbirPlayer::streak_get() const
    {
        return streak_;
    }

    void GbirPlayer::streak_set(int streak)
    {
        streak_ = streak;
    }

    GbirScene::GbirScene(std::string name,
                         std::vector<std::unique_ptr<GbirBasicBlock>> blocks)
        : name_(std::move(name))
        , blocks_(std::move(blocks))
    {}

    void GbirScene::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& GbirScene::name_get() const
    {
        return name_;
    }

    void GbirScene::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const std::vector<std::unique_ptr<GbirBasicBlock>>&
    GbirScene::blocks_get() const
    {
        return blocks_;
    }

    std::vector<std::unique_ptr<GbirBasicBlock>>& GbirScene::blocks_get()
    {
        return blocks_;
    }

    void GbirScene::add_block(std::unique_ptr<GbirBasicBlock> block)
    {
        blocks_.push_back(std::move(block));
    }

    int GbirScene::next_value_id_get() const
    {
        return next_value_id_;
    }

    void GbirScene::next_value_id_set(int next_value_id)
    {
        next_value_id_ = next_value_id;
    }

    std::optional<int> GbirScene::max_players_get() const
    {
        return max_players_;
    }

    void GbirScene::max_players_set(std::optional<int> max_players)
    {
        max_players_ = max_players;
    }

    const std::vector<std::unique_ptr<GbirBasicBlock>>&
    GbirScene::precondition_get() const
    {
        return precondition_;
    }

    std::vector<std::unique_ptr<GbirBasicBlock>>& GbirScene::precondition_get()
    {
        return precondition_;
    }

    std::optional<GbirValue> GbirScene::precondition_result_get() const
    {
        return precondition_result_;
    }

    void GbirScene::precondition_result_set(GbirValue result)
    {
        precondition_result_ = result;
    }
} // namespace gbir
