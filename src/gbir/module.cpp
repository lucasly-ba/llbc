#include <gbir/module.h>

namespace gbir
{
    const std::vector<std::unique_ptr<GbirFunction>>&
    GbirModule::functions_get() const
    {
        return functions_;
    }

    std::vector<std::unique_ptr<GbirFunction>>& GbirModule::functions_get()
    {
        return functions_;
    }

} // namespace gbir
