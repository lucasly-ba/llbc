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
        GbirBasicBlock(std::string label,
                       std::vector<std::unique_ptr<GbirInst>> instructions,
                       std::unique_ptr<GbirInst> terminator);

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

    private:
        std::string label_;
        std::vector<std::unique_ptr<GbirInst>> instructions_;
        std::unique_ptr<GbirInst> terminator_;
    };
} // namespace gbir
