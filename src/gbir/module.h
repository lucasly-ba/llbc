#pragma once
#include <gbir/top-level.h>
#include <memory>
#include <vector>

namespace gbir
{
    class GbirModule
    {
    public:
        GbirModule() = default;

        const std::vector<std::unique_ptr<GbirFunction>>& functions_get() const;
        std::vector<std::unique_ptr<GbirFunction>>& functions_get();

    private:
        std::vector<std::unique_ptr<GbirFunction>> functions_;
    };
} // namespace gbir
