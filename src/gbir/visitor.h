#pragma once
#include <gbir/fwd.h>

namespace gbir
{
    class GbirVisitorBase
    {
    public:
        virtual ~GbirVisitorBase() = default;

        virtual void visit(ConstIntInst& e) = 0;
        virtual void visit(ConstFloatInst& e) = 0;
        virtual void visit(ConstStringInst& e) = 0;
        virtual void visit(ConstBoolInst& e) = 0;
        virtual void visit(ConstDollarsInst& e) = 0;
        virtual void visit(ConstChanceInst& e) = 0;
        virtual void visit(ConstStreakInst& e) = 0;

        virtual void visit(AllocaInst& e) = 0;
        virtual void visit(LoadInst& e) = 0;
        virtual void visit(StoreInst& e) = 0;

        virtual void visit(BinopInst& e) = 0;
        virtual void visit(GlobalAddrInst& e) = 0;
        virtual void visit(CallInst& e) = 0;

        virtual void visit(CondBranchInst& e) = 0;
        virtual void visit(BranchInst& e) = 0;
        virtual void visit(ReturnInst& e) = 0;

        virtual void visit(PhiInst& e) = 0;

        virtual void visit(EnterInst& e) = 0;
        virtual void visit(StartInst& e) = 0;

        virtual void visit(GbirScene& e) = 0;
        virtual void visit(GbirPlayer& e) = 0;
        virtual void visit(GbirFunction& e) = 0;
        virtual void visit(GbirGlobalVar& e) = 0;
    };
} // namespace gbir
