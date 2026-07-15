#include <gbir-opti/dead-block.h>

namespace gbir
{
    void DeadBlockElimination::run(
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks)
    {
        if (blocks.empty())
            return;

        reachable_.clear();
        mark_reachable(blocks.front().get());

        std::erase_if(blocks,
                      [this](const std::unique_ptr<GbirBasicBlock>& block)
                      {
                          if (reachable_.contains(block.get()))
                              return false;
                          block->delete_edges();
                          return true;
                      });
    }

    void DeadBlockElimination::mark_reachable(GbirBasicBlock* block)
    {
        if (reachable_.contains(block))
            return;
        reachable_.insert(block);
        for (auto succ : block->successors_get())
            mark_reachable(succ);
    }
} // namespace gbir
