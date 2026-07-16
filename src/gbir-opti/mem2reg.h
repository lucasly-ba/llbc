#pragma once
#include <gbir-opti/dominance.h>
#include <gbir/basic-block.h>
#include <gbir/inst/mem.h>
#include <gbir/inst/phi.h>
#include <gbir/value.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace gbir
{
    class Mem2Reg
    {
    public:
        void run(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks,
                 int& next_value_id);

    private:
        std::vector<AllocaInst*> collect_promotable_allocas(
            std::vector<std::unique_ptr<GbirBasicBlock>>& blocks);

        void insert_phis(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks,
                         const std::vector<AllocaInst*>& allocas,
                         int& next_value_id);

        void rename(GbirBasicBlock* block);

        void cleanup(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks);

        GbirValue current_value(int alloca_id);
        GbirValue resolve(GbirValue value);
        void rewrite_uses(GbirInst* inst);

        Dominance dom_;
        std::unordered_map<PhiInst*, AllocaInst*> phi_alloca_;
        std::unordered_set<int> promoted_ids_;
        std::unordered_map<int, std::vector<GbirValue>> stacks_;
        std::unordered_map<int, GbirValue> replacement_;
        std::unordered_map<GbirBasicBlock*, std::vector<GbirBasicBlock*>>
            dom_children_;
    };
} // namespace gbir
