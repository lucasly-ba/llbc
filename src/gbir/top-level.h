#pragma once
#include <ast/type.h>
#include <gbir/basic-block.h>
#include <gbir/fwd.h>
#include <gbir/value.h>
#include <gbir/visitor.h>
#include <memory>
#include <optional>
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
                     ast::Type return_type,
                     std::vector<std::unique_ptr<GbirBasicBlock>> blocks);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<GbirValue>& args_get() const;
        void args_set(std::vector<GbirValue> args);

        ast::Type return_type_get() const;
        void return_type_set(ast::Type return_type);

        const std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get() const;
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks_get();

        int next_value_id_get() const;
        void next_value_id_set(int next_value_id);

    private:
        std::string name_;
        std::vector<GbirValue> args_;
        ast::Type return_type_;
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks_;
        int next_value_id_ = 0;
    };

    class GbirGlobalVar : public GbirTopLevel
    {
    public:
        GbirGlobalVar(std::string name, ast::Type type,
                      std::unique_ptr<GbirInst> init);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        ast::Type type_get() const;
        void type_set(ast::Type type);

        GbirInst* init_get() const;
        void init_set(std::unique_ptr<GbirInst> init);

    private:
        std::string name_;
        ast::Type type_;
        std::unique_ptr<GbirInst> init_;
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

        int next_value_id_get() const;
        void next_value_id_set(int next_value_id);

        std::optional<int> max_players_get() const;
        void max_players_set(std::optional<int> max_players);

        const std::vector<std::unique_ptr<GbirBasicBlock>>&
        precondition_get() const;
        std::vector<std::unique_ptr<GbirBasicBlock>>& precondition_get();
        std::optional<GbirValue> precondition_result_get() const;
        void precondition_result_set(GbirValue result);

    private:
        std::string name_;
        std::vector<std::unique_ptr<GbirBasicBlock>> blocks_;
        std::optional<int> max_players_;
        std::vector<std::unique_ptr<GbirBasicBlock>> precondition_;
        std::optional<GbirValue> precondition_result_;
        int next_value_id_ = 0;
    };
} // namespace gbir
