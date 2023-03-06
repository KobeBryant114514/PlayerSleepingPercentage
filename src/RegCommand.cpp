#include <llapi/RegCommandAPI.h>
#include <llapi/DynamicCommandAPI.h>
#include "Global.h"
#include "setting.h"

using namespace RegisterCommandHelper;

void RegSleepCommand(){
    using ParamType = DynamicCommand::ParameterType;
    auto command = DynamicCommand::createCommand(Settings::command, "设置睡觉玩家百分比", CommandPermissionLevel::GameMasters);
    command->mandatory("Percentage", ParamType::Int);
    command->addOverload({"Percentage"});
    command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
        int per = results["Percentage"].get<int>();
        if(per > 100){
            return output.error("睡觉玩家百分比不能超过100％！");
        }
        else if(per < 0){
            return output.error("睡觉玩家百分比不能小于0％！");
        }
        else{
            Settings::PlayerSleepingPercentage = per;
            Settings::reloadJson(ConfigFile);
            return output.success("设置成功！");
        };
    });
    DynamicCommand::setup(std::move(command));
}

