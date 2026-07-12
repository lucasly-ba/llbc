#pragma once

namespace gbir
{
    class GbirValue;

    class GbirInst;

    class ConstInst;
    class ConstIntInst;
    class ConstFloatInst;
    class ConstStringInst;
    class ConstBoolInst;
    class ConstDollarsInst;
    class ConstChanceInst;
    class ConstStreakInst;

    class MemInst;
    class AllocaInst;
    class LoadInst;
    class StoreInst;

    class BinopInst;

    class CallInst;

    class CondBranchInst;
    class BranchInst;
    class ReturnInst;

    class PhiInst;

    class EnterInst;
    class StartInst;

    class GbirVisitorBase;
    class GbirBasicBlock;
    class GbirFunction;
    class GbirModule;
} // namespace gbir
