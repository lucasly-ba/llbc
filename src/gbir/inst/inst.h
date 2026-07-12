#pragma once
#include <gbir/visitor.h>

namespace gbir
{
    class GbirInst
    {
    public:
        virtual ~GbirInst() = default;
        virtual void accept(GbirVisitorBase& v) = 0;
    };

} // namespace gbir
