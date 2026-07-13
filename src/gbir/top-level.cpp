#include <gbir/top-level.h>

namespace gbir
{
    GbirFunction::GbirFunction(std::string name, std::vector<GbirValue> args,
                               ast::Type return_type)
        : name_(std::move(name))
        , args_(std::move(args))
        , return_type_(return_type)
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

    void GbirFunction::add_block(std::unique_ptr<GbirBasicBlock> block)
    {
        blocks_.push_back(std::move(block));
    }

    GbirGlobalVar::GbirGlobalVar(std::string name, ast::Type type,
                                 int init_value)
        : name_(std::move(name))
        , type_(type)
        , init_value_(init_value)
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

    int GbirGlobalVar::init_value_get() const
    {
        return init_value_;
    }

    void GbirGlobalVar::init_value_set(int init_value)
    {
        init_value_ = init_value;
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
} // namespace gbir
