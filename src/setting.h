#pragma once

#include <llapi/utils/FileHelper.h>
#include <Nlohmann/json.hpp>

namespace Settings {
    extern int PlayerSleepingPercentage;
    extern string command;
    extern string broadcast;
    extern string actionbar1;
    extern string actionbar2;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void WriteDefaultConfig(const std::string& fileName);
    void LoadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
}