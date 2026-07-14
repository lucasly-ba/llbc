#include <gbir/basic-block.h>

#include "gbir/inst/terminator.h"

namespace gbir
{
    GbirBasicBlock::GbirBasicBlock(
        std::string label, std::vector<std::unique_ptr<GbirInst>> instructions,
        std::unique_ptr<GbirInst> terminator)
        : label_(std::move(label))
        , instructions_(std::move(instructions))
        , terminator_(std::move(terminator))
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
} // namespace gbir
