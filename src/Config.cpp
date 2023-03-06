#include "setting.h"
#include "Global.h"
#include <llapi/LoggerAPI.h>

void loadConfig() {
    if (!std::filesystem::exists("plugins/PlayerSleepingPercentage"))
        std::filesystem::create_directories("plugins/PlayerSleepingPercentage");	
    if (std::filesystem::exists(ConfigFile)) {
        Settings::LoadConfigFromJson(ConfigFile);
    }
    else {
        logger.warn("配置文件不存在，已自动创建");
        Settings::WriteDefaultConfig(ConfigFile);
    }
    if(Settings::PlayerSleepingPercentage < 0){
        logger.warn("睡觉玩家百分比不能低于0％");
        Settings::PlayerSleepingPercentage = 0;
        Settings::reloadJson(ConfigFile);
    }
    if(Settings::PlayerSleepingPercentage > 100){
        logger.warn("睡觉玩家百分比不能高于100％");
        Settings::PlayerSleepingPercentage = 100;
        Settings::reloadJson(ConfigFile);
    }
}