#pragma once
#include "version.h"
#define ConfigFile "plugins/PlayerSleepingPercentage/config.json"
#include <iostream>
#include <Global.h>
#include <mc/Player.hpp>
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <ScheduleAPI.h>
extern Logger logger;
extern void RegSleepCommand();
extern void Sleep();
extern void loadConfig();
extern std::unordered_set<std::string> sleepList;
extern void sendSleepMsg(Player* pl);
extern void StopSleep();