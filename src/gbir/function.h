#pragma once
#include <ast/type.h>
#include <gbir/basic-block.h>
#include <gbir/value.h>
#include <memory>

namespace gbir
{
    class GbirFunction
    {
    public:
        GbirFunction(std::string name, std::vector<GbirValue> params,
                     ast::Type return_type,
                     std::vector<std::unique_ptr<GbirBasicBlock>> blocks);

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<GbirValue>& params_get() const;
        void params_set(std::vector<GbirValue> params);

        ast::Type return_type_get() const;
        void return_type_set(ast::Type return_type);

        const std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get() const;
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get();
        void blocks_set(std::vector<std::unique_ptr<GbirBasicBlock>> blocks);

    private:
        std::string name_;
        std::vector<GbirValue> params_;
        ast::Type return_type_;
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks_;
    };
} // namespace gbir
