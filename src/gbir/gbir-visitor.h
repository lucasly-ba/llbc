#pragma once
#include <gbir/visitor.h>

namespace gbir
{
    class GbirVisitor : public GbirVisitorBase
    {
    public:
        void visit(ConstIntInst& e) override;
        void visit(ConstFloatInst& e) override;
        void visit(ConstStringInst& e) override;
        void visit(ConstBoolInst& e) override;
        void visit(ConstDollarsInst& e) override;
        void visit(ConstChanceInst& e) override;
        void visit(ConstStreakInst& e) override;

        void visit(AllocaInst& e) override;
        void visit(LoadInst& e) override;
        void visit(StoreInst& e) override;

        void visit(BinopInst& e) override;
        void visit(GlobalAddrInst& e) override;
        void visit(CallInst& e) override;

        void visit(CondBranchInst& e) override;
        void visit(BranchInst& e) override;
        void visit(ReturnInst& e) override;

        void visit(PhiInst& e) override;

        void visit(EnterInst& e) override;
        void visit(StartInst& e) override;

        void visit(GbirScene& e) override;
        void visit(GbirPlayer& e) override;
        void visit(GbirFunction& e) override;
        void visit(GbirGlobalVar& e) override;
    };
} // namespace gbir
