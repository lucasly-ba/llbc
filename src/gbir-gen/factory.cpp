#include <gbir-gen/factory.h>

namespace gbir
{
    GbirValue make_GbirValue(int id, ast::Type type)
    {
        return GbirValue(id, type);
    }

    std::unique_ptr<GbirFunction>
    make_GbirFunction(std::string name, std::vector<GbirValue> args,
                      ast::Type return_type)
    {
        return std::make_unique<GbirFunction>(std::move(name), std::move(args),
                                              return_type);
    }

    std::unique_ptr<GbirGlobalVar>
    make_GbirGlobalVar(std::string name, ast::Type type, int init_value)
    {
        return std::make_unique<GbirGlobalVar>(std::move(name), type,
                                               init_value);
    }

    std::unique_ptr<GbirPlayer> make_GbirPlayer(std::string name, int dollar,
                                                int chance, int streak)
    {
        return std::make_unique<GbirPlayer>(std::move(name), dollar, chance,
                                            streak);
    }

    std::unique_ptr<GbirScene>
    make_GbirScene(std::string name,
                   std::vector<std::unique_ptr<GbirBasicBlock>> blocks)
    {
        return std::make_unique<GbirScene>(std::move(name), std::move(blocks));
    }

    std::unique_ptr<GbirBasicBlock>
    make_GbirBasicBlock(std::string label,
                        std::vector<std::unique_ptr<GbirInst>> instructions,
                        std::unique_ptr<GbirInst> terminator)
    {
        return std::make_unique<GbirBasicBlock>(std::move(label),
                                                std::move(instructions),
                                                std::move(terminator));
    }

    std::unique_ptr<GbirInst> make_ConstIntInst(int raw_value, GbirValue result)
    {
        return std::make_unique<ConstIntInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_ConstFloatInst(float raw_value,
                                                  GbirValue result)
    {
        return std::make_unique<ConstFloatInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_ConstStringInst(std::string raw_value,
                                                   GbirValue result)
    {
        return std::make_unique<ConstStringInst>(std::move(raw_value), result);
    }

    std::unique_ptr<GbirInst> make_ConstBoolInst(bool raw_value,
                                                 GbirValue result)
    {
        return std::make_unique<ConstBoolInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_ConstDollarsInst(int raw_value,
                                                    GbirValue result)
    {
        return std::make_unique<ConstDollarsInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_ConstChanceInst(int raw_value,
                                                   GbirValue result)
    {
        return std::make_unique<ConstChanceInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_ConstStreakInst(int raw_value,
                                                   GbirValue result)
    {
        return std::make_unique<ConstStreakInst>(raw_value, result);
    }

    std::unique_ptr<GbirInst> make_AllocaInst(ast::Type var_type,
                                              GbirValue result)
    {
        return std::make_unique<AllocaInst>(var_type, result);
    }

    std::unique_ptr<GbirInst> make_LoadInst(GbirValue read_value,
                                            GbirValue result)
    {
        return std::make_unique<LoadInst>(read_value, result);
    }

    std::unique_ptr<GbirInst> make_StoreInst(GbirValue target, GbirValue value)
    {
        return std::make_unique<StoreInst>(target, value);
    }

    std::unique_ptr<GbirInst> make_BinopInst(GbirValue left,
                                             ast::OpExp::Oper oper,
                                             GbirValue right, GbirValue result)
    {
        return std::make_unique<BinopInst>(left, oper, right, result);
    }

    std::unique_ptr<GbirInst> make_CallInst(std::string name,
                                            std::vector<GbirValue> args,
                                            GbirValue result)
    {
        return std::make_unique<CallInst>(std::move(name), std::move(args),
                                          result);
    }

    std::unique_ptr<GbirInst> make_CondBranchInst(GbirValue condition,
                                                  GbirBasicBlock* then_bb,
                                                  GbirBasicBlock* else_bb)
    {
        return std::make_unique<CondBranchInst>(condition, then_bb, else_bb);
    }

    std::unique_ptr<GbirInst> make_BranchInst(GbirBasicBlock* target_bb)
    {
        return std::make_unique<BranchInst>(target_bb);
    }

    std::unique_ptr<GbirInst> make_ReturnInst(GbirValue value)
    {
        return std::make_unique<ReturnInst>(value);
    }

    std::unique_ptr<GbirInst> make_PhiInst(
        GbirValue result,
        std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming)
    {
        return std::make_unique<PhiInst>(result, std::move(incoming));
    }

    std::unique_ptr<GbirInst> make_EnterInst(std::string player_name,
                                             std::string scene_name)
    {
        return std::make_unique<EnterInst>(std::move(player_name),
                                           std::move(scene_name));
    }

    std::unique_ptr<GbirInst> make_StartInst(std::string scene_name)
    {
        return std::make_unique<StartInst>(std::move(scene_name));
    }
} // namespace gbir
