#pragma once
#include <gbir/inst/inst.h>
#include <gbir/inst/terminator.h>
#include <memory>
#include <string>
#include <vector>

namespace gbir
{
    class GbirBasicBlock
    {
    public:
        GbirBasicBlock(std::string label);

        const std::string& label_get() const;
        void label_set(std::string label);

        const std::vector<std::unique_ptr<GbirInst>>& instructions_get() const;
        std::vector<std::unique_ptr<GbirInst>>& instructions_get();
        void
        instructions_set(std::vector<std::unique_ptr<GbirInst>> instructions);
        void add_instruction(std::unique_ptr<GbirInst> instruction);

        bool has_terminator() const;
        GbirInst& terminator_get() const;
        void terminator_set(std::unique_ptr<GbirInst> terminator);

        const std::vector<GbirBasicBlock*> predecessors_get() const;
        std::vector<GbirBasicBlock*> predecessors_get();
        void predecessors_set(std::vector<GbirBasicBlock*> predecessors);
        void add_predecessor(GbirBasicBlock* predecessor);
        void remove_predecessor(GbirBasicBlock* predecessor);
        bool has_predecessor();

        const std::vector<GbirBasicBlock*> successors_get() const;
        std::vector<GbirBasicBlock*> successors_get();
        void successors_set(std::vector<GbirBasicBlock*> successors);
        void add_successor(GbirBasicBlock* successor);
        void remove_successor(GbirBasicBlock* successor);
        bool has_successor();

        void delete_edges();

    private:
        std::vector<GbirBasicBlock*> predecessors_;
        std::vector<GbirBasicBlock*> successors_;
        std::string label_;
        std::vector<std::unique_ptr<GbirInst>> instructions_;
        std::unique_ptr<GbirInst> terminator_;
    };
} // namespace gbir
