#pragma once
#include <gbir/basic-block.h>
#include <memory>
#include <unordered_set>
#include <vector>

namespace gbir
{
    class DeadBlockElimination
    {
    public:
        void run(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks);

    private:
        void mark_reachable(GbirBasicBlock* block);

        std::unordered_set<GbirBasicBlock*> reachable_;
    };
} // namespace gbir
