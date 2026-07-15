#pragma once
#include <ast/exp.h>
#include <ast/type.h>
#include <gbir/all.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "gbir/inst/global.h"

namespace gbir
{
    GbirValue make_GbirValue(int id, ast::Type type);

    std::unique_ptr<GbirFunction>
    make_GbirFunction(std::string name, std::vector<GbirValue> args,
                      ast::Type return_type,
                      std::vector<std::unique_ptr<GbirBasicBlock>> blocks);

    std::unique_ptr<GbirGlobalVar>
    make_GbirGlobalVar(std::string name, ast::Type type,
                       std::unique_ptr<GbirInst> init);

    std::unique_ptr<GbirPlayer> make_GbirPlayer(std::string name, int dollar,
                                                int chance, int streak);

    std::unique_ptr<GbirScene>
    make_GbirScene(std::string name,
                   std::vector<std::unique_ptr<GbirBasicBlock>> blocks);

    std::unique_ptr<GbirBasicBlock> make_GbirBasicBlock(std::string label);

    std::unique_ptr<GlobalAddrInst> make_GlobalAddrInst(std::string name,
                                                        GbirValue result);
    std::unique_ptr<GbirInst> make_ConstFloatInst(float raw_value,
                                                  GbirValue result);
    std::unique_ptr<GbirInst> make_ConstStringInst(std::string raw_value,
                                                   GbirValue result);
    std::unique_ptr<GbirInst> make_ConstBoolInst(bool raw_value,
                                                 GbirValue result);
    std::unique_ptr<GbirInst> make_ConstDollarsInst(int raw_value,
                                                    GbirValue result);
    std::unique_ptr<GbirInst> make_ConstChanceInst(int raw_value,
                                                   GbirValue result);
    std::unique_ptr<GbirInst> make_ConstStreakInst(int raw_value,
                                                   GbirValue result);
    std::unique_ptr<GbirInst> make_AllocaInst(ast::Type var_type,
                                              GbirValue result);

    std::unique_ptr<GbirInst> make_LoadInst(GbirValue read_value,
                                            GbirValue result);
    std::unique_ptr<GbirInst> make_StoreInst(GbirValue target, GbirValue value);

    std::unique_ptr<GbirInst> make_BinopInst(GbirValue left,
                                             ast::OpExp::Oper oper,
                                             GbirValue right, GbirValue result);
    std::unique_ptr<GbirInst> make_CallInst(std::string name,
                                            std::vector<GbirValue> args,
                                            GbirValue result);

    std::unique_ptr<GbirInst> make_CondBranchInst(GbirValue condition,
                                                  GbirBasicBlock* then_bb,
                                                  GbirBasicBlock* else_bb);
    std::unique_ptr<GbirInst> make_BranchInst(GbirBasicBlock* target_bb);
    std::unique_ptr<GbirInst> make_ReturnInst(GbirValue value);

    std::unique_ptr<GbirInst>
    make_PhiInst(GbirValue result,
                 std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming);

    std::unique_ptr<GbirInst> make_EnterInst(std::string player_name,
                                             std::string scene_name);
    std::unique_ptr<GbirInst> make_StartInst(std::string scene_name);
} // namespace gbir
