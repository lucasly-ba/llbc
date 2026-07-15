#include <gbir/basic-block.h>

namespace gbir
{
    GbirBasicBlock::GbirBasicBlock(std::string label)
        : label_(std::move(label))
    {}

    const std::string& GbirBasicBlock::label_get() const
    {
        return label_;
    }

    void GbirBasicBlock::label_set(std::string label)
    {
        label_ = std::move(label);
    }

    const std::vector<std::unique_ptr<GbirInst>>&
    GbirBasicBlock::instructions_get() const
    {
        return instructions_;
    }

    std::vector<std::unique_ptr<GbirInst>>& GbirBasicBlock::instructions_get()
    {
        return instructions_;
    }

    void GbirBasicBlock::instructions_set(
        std::vector<std::unique_ptr<GbirInst>> instructions)
    {
        instructions_ = std::move(instructions);
    }

    void GbirBasicBlock::add_instruction(std::unique_ptr<GbirInst> instruction)
    {
        instructions_.push_back(std::move(instruction));
    }

    bool GbirBasicBlock::has_terminator() const
    {
        return terminator_ != nullptr;
    }

    GbirInst& GbirBasicBlock::terminator_get() const
    {
        return *terminator_;
    }

    void GbirBasicBlock::terminator_set(std::unique_ptr<GbirInst> terminator)
    {
        terminator_ = std::move(terminator);
    }

    const std::vector<GbirBasicBlock*> GbirBasicBlock::predecessors_get() const
    {
        return predecessors_;
    }

    std::vector<GbirBasicBlock*> GbirBasicBlock::predecessors_get()
    {
        return predecessors_;
    }

    void
    GbirBasicBlock::predecessors_set(std::vector<GbirBasicBlock*> predecessors)
    {
        predecessors_ = predecessors;
    }

    void GbirBasicBlock::add_predecessor(GbirBasicBlock* predecessor)
    {
        predecessors_.push_back(predecessor);
    }

    const std::vector<GbirBasicBlock*> GbirBasicBlock::successors_get() const
    {
        return successors_;
    }

    std::vector<GbirBasicBlock*> GbirBasicBlock::successors_get()
    {
        return successors_;
    }

    void GbirBasicBlock::successors_set(std::vector<GbirBasicBlock*> successors)
    {
        successors_ = successors;
    }

    void GbirBasicBlock::add_successor(GbirBasicBlock* successor)
    {
        successors_.push_back(successor);
    }

    bool GbirBasicBlock::has_predecessor()
    {
        return !predecessors_.empty();
    }

    bool GbirBasicBlock::has_successor()
    {
        return !predecessors_.empty();
    }

} // namespace gbir
