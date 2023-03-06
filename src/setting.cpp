#include <llapi/utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "Global.h"

#define TRJ(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \

namespace Settings {
    int PlayerSleepingPercentage = 100;
    string broadcast = "{1}正在床上睡觉。要快进到黎明，需要{2}％的玩家同时在床上睡觉。";
    string actionbar1 = "{1}/{2}名玩家正在睡觉。";
    string actionbar2 = "今晚将在睡梦中度过";
    string command = "playersleepingpercentage";
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["Config"]["PlayerSleepingPercentage"] = PlayerSleepingPercentage;
        json["Config"]["Command"] = command;
        json["Message"]["SleepBroadcast"] = broadcast;
        json["Message"]["SleepCount"] = actionbar1;
        json["Message"]["SleepEnough"] = actionbar2;
        return json;
    }

    void initjson(nlohmann::json json) {
        TRJ("Config", "PlayerSleepingPercentage", PlayerSleepingPercentage);
        TRJ("Config", "Command", command);
        TRJ("Message", "SleepBroadcast", broadcast);
        TRJ("Message", "SleepCount", actionbar1);
        TRJ("Message", "SleepEnough", actionbar2);
    }

    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "无法打开配置文件" << fileName << std::endl;
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "无法打开配置文件" << fileName << std::endl;
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }
    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file){
            file << globaljson().dump(4);
        }
        else{
            Logger("PlayerSleepingPercentge").error("配置文件异常！");
        }
        file.close();
    }
}