#include <gbir-opti/mem2reg.h>

#include <gbir/inst/binop.h>
#include <gbir/inst/call.h>
#include <gbir/inst/terminator.h>

#include <unordered_set>

namespace gbir
{
    void Mem2Reg::run(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks,
                      int& next_value_id)
    {
        if (blocks.empty())
            return;

        phi_alloca_.clear();
        promoted_ids_.clear();
        stacks_.clear();
        replacement_.clear();
        dom_children_.clear();

        auto allocas = collect_promotable_allocas(blocks);
        if (allocas.empty())
            return;

        for (auto* alloca : allocas)
            promoted_ids_.insert(alloca->result_get().id_get());

        dom_.compute(blocks);

        for (auto& block : blocks)
        {
            GbirBasicBlock* b = block.get();
            GbirBasicBlock* idom = dom_.idom_get(b);
            if (idom != nullptr && idom != b)
                dom_children_[idom].push_back(b);
        }

        insert_phis(blocks, allocas, next_value_id);
        rename(blocks.front().get());
        cleanup(blocks);
    }

    // TODO: need to fix this when we implement ptr for example
    std::vector<AllocaInst*> Mem2Reg::collect_promotable_allocas(
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks)
    {
        std::vector<AllocaInst*> allocas;
        for (auto& block : blocks)
            for (auto& inst : block->instructions_get())
                if (auto* alloca = dynamic_cast<AllocaInst*>(inst.get()))
                    allocas.push_back(alloca);

        return allocas;
    }

    // Cytron and al algorithm
    void Mem2Reg::insert_phis(
        std::vector<std::unique_ptr<GbirBasicBlock>>& blocks,
        const std::vector<AllocaInst*>& allocas, int& next_value_id)
    {
        for (auto* alloca : allocas)
        {
            int alloca_id = alloca->result_get().id_get();
            ast::Type type = alloca->type_get();

            std::vector<GbirBasicBlock*> worklist;
            for (auto& block : blocks)
                for (auto& inst : block->instructions_get())
                    if (auto* store = dynamic_cast<StoreInst*>(inst.get()))
                        if (store->target_get().id_get() == alloca_id)
                        {
                            worklist.push_back(block.get());
                            break;
                        }

            std::unordered_set<GbirBasicBlock*> has_phi;
            while (!worklist.empty())
            {
                GbirBasicBlock* def = worklist.back();
                worklist.pop_back();

                for (auto* front : dom_.frontier_get(def))
                {
                    if (has_phi.contains(front))
                        continue;
                    has_phi.insert(front);

                    GbirValue result(next_value_id++, type);
                    auto phi = std::make_unique<PhiInst>(
                        result,
                        std::vector<std::pair<GbirValue, GbirBasicBlock*>>{});
                    phi_alloca_[phi.get()] = alloca;

                    auto& insts = front->instructions_get();
                    insts.insert(insts.begin(), std::move(phi));

                    worklist.push_back(front);
                }
            }
        }
    }

    // Cytron and al algorithm
    void Mem2Reg::rename(GbirBasicBlock* block)
    {
        std::vector<int> pushed;

        for (auto& inst : block->instructions_get())
        {
            GbirInst* i = inst.get();

            if (auto* phi = dynamic_cast<PhiInst*>(i))
            {
                auto it = phi_alloca_.find(phi);
                if (it != phi_alloca_.end())
                {
                    int aid = it->second->result_get().id_get();
                    stacks_[aid].push_back(phi->result_get());
                    pushed.push_back(aid);
                    continue;
                }
            }

            if (auto* load = dynamic_cast<LoadInst*>(i))
            {
                int aid = load->read_value_get().id_get();
                if (promoted_ids_.contains(aid))
                {
                    replacement_[load->result_get().id_get()] =
                        current_value(aid);
                    continue;
                }
            }

            if (auto* store = dynamic_cast<StoreInst*>(i))
            {
                int aid = store->target_get().id_get();
                if (promoted_ids_.contains(aid))
                {
                    stacks_[aid].push_back(resolve(store->value_get()));
                    pushed.push_back(aid);
                    continue;
                }
            }

            rewrite_uses(i);
        }

        if (block->has_terminator())
            rewrite_uses(&block->terminator_get());

        for (auto* succ : block->successors_get())
            for (auto& inst : succ->instructions_get())
                if (auto* phi = dynamic_cast<PhiInst*>(inst.get()))
                {
                    auto it = phi_alloca_.find(phi);
                    if (it != phi_alloca_.end())
                    {
                        int aid = it->second->result_get().id_get();
                        phi->add_incoming(current_value(aid), block);
                    }
                }

        for (auto* child : dom_children_[block])
            rename(child);

        for (int aid : pushed)
            stacks_[aid].pop_back();
    }

    void Mem2Reg::cleanup(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks)
    {
        for (auto& block : blocks)
        {
            auto& insts = block->instructions_get();
            std::erase_if(
                insts,
                [&](const std::unique_ptr<GbirInst>& up)
                {
                    GbirInst* i = up.get();
                    if (auto* a = dynamic_cast<AllocaInst*>(i))
                        return promoted_ids_.contains(a->result_get().id_get());
                    if (auto* l = dynamic_cast<LoadInst*>(i))
                        return promoted_ids_.contains(
                            l->read_value_get().id_get());
                    if (auto* s = dynamic_cast<StoreInst*>(i))
                        return promoted_ids_.contains(s->target_get().id_get());
                    return false;
                });
        }
    }

    GbirValue Mem2Reg::current_value(int alloca_id)
    {
        return stacks_[alloca_id].back();
    }

    GbirValue Mem2Reg::resolve(GbirValue value)
    {
        auto it = replacement_.find(value.id_get());
        if (it != replacement_.end())
            return it->second;
        return value;
    }

    void Mem2Reg::rewrite_uses(GbirInst* inst)
    {
        if (auto* b = dynamic_cast<BinopInst*>(inst))
        {
            b->left_set(resolve(b->left_get()));
            b->right_set(resolve(b->right_get()));
        }
        else if (auto* c = dynamic_cast<CallInst*>(inst))
        {
            for (auto& arg : c->args_get())
                arg = resolve(arg);
        }
        else if (auto* s = dynamic_cast<StoreInst*>(inst))
            s->value_set(resolve(s->value_get()));
        else if (auto* r = dynamic_cast<ReturnInst*>(inst))
            r->value_set(resolve(r->value_get()));
        else if (auto* cb = dynamic_cast<CondBranchInst*>(inst))
            cb->condition_set(resolve(cb->condition_get()));
    }
} // namespace gbir
