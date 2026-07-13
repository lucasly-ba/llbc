#pragma once
#include <ast/type.h>
#include <gbir/basic-block.h>
#include <gbir/fwd.h>
#include <gbir/value.h>
#include <gbir/visitor.h>
#include <memory>
#include <string>
#include <vector>

namespace gbir
{
    class GbirTopLevel
    {
    public:
        virtual ~GbirTopLevel() = default;
        virtual void accept(GbirVisitorBase& v) = 0;
    };

    class GbirFunction : public GbirTopLevel
    {
    public:
        GbirFunction(std::string name, std::vector<GbirValue> args,
                     ast::Type return_type);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<GbirValue>& args_get() const;
        void args_set(std::vector<GbirValue> args);

        ast::Type return_type_get() const;
        void return_type_set(ast::Type return_type);

        const std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get() const;
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get();
        void add_block(std::unique_ptr<GbirBasicBlock> block);

    private:
        std::string name_;
        std::vector<GbirValue> args_;
        ast::Type return_type_;
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks_;
    };

    class GbirGlobalVar : public GbirTopLevel
    {
    public:
        GbirGlobalVar(std::string name, ast::Type type, int init_value);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        ast::Type type_get() const;
        void type_set(ast::Type type);

        int init_value_get() const;
        void init_value_set(int init_value);

    private:
        std::string name_;
        ast::Type type_;
        int init_value_;
    };

    class GbirPlayer : public GbirTopLevel
    {
    public:
        GbirPlayer(std::string name, int dollar, int chance, int streak);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        int dollar_get() const;
        void dollar_set(int dollar);

        int chance_get() const;
        void chance_set(int chance);

        int streak_get() const;
        void streak_set(int streak);

    private:
        std::string name_;
        int dollar_;
        int chance_;
        int streak_;
    };

    class GbirScene : public GbirTopLevel
    {
    public:
        GbirScene(std::string name,
                  std::vector<std::unique_ptr<GbirBasicBlock>> blocks);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get() const;
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get();
        void add_block(std::unique_ptr<GbirBasicBlock> block);

    private:
        std::string name_;
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks_;
    };
} // namespace gbir
