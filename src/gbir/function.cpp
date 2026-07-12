#include <gbir/function.h>

namespace gbir
{
    GbirFunction::GbirFunction(std::string name, std::vector<GbirValue> params,
                               ast::Type return_type,
                               std::vector<std::unique_ptr<GbirBasicBlock>> blocks)
        : name_(std::move(name))
        , params_(std::move(params))
        , return_type_(return_type)
        , blocks_(std::move(blocks))
    {}

    const std::string& GbirFunction::name_get() const
    {
        return name_;
    }

    void GbirFunction::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const std::vector<GbirValue>& GbirFunction::params_get() const
    {
        return params_;
    }

    void GbirFunction::params_set(std::vector<GbirValue> params)
    {
        params_ = std::move(params);
    }

    ast::Type GbirFunction::return_type_get() const
    {
        return return_type_;
    }

    void GbirFunction::return_type_set(ast::Type return_type)
    {
        return_type_ = return_type;
    }

    const std::vector<std::unique_ptr<GbirBasicBlock>>& GbirFunction::blocks_get() const
    {
        return blocks_;
    }

    std::vector<std::unique_ptr<GbirBasicBlock>>& GbirFunction::blocks_get()
    {
        return blocks_;
    }

    void GbirFunction::blocks_set(std::vector<std::unique_ptr<GbirBasicBlock>> blocks)
    {
        blocks_ = std::move(blocks);
    }
} // namespace gbir
