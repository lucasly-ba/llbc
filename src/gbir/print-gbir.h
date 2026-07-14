#pragma once
#include <ast/type.h>
#include <gbir/fwd.h>
#include <gbir/value.h>
#include <gbir/visitor.h>
#include <ostream>

namespace gbir
{
    class PrintGbir : public GbirVisitorBase
    {
    public:
        explicit PrintGbir(std::ostream& ostr);

        void print(GbirModule& module);

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

    private:
        void print_value(GbirValue value);
        void print_type(ast::Type type);
        void print_block(GbirBasicBlock& block);

        std::ostream& ostr_;
    };
} // namespace gbir
