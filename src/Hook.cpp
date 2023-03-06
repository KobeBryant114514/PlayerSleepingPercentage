#include <HookAPI.h>
#include <mc/Player.hpp>
#include <mc/ServerLevel.hpp>
#include <mc/Level.hpp>
#include "Global.h"

std::unordered_set<std::string> sleepList = {};

TInstanceHook(int64_t, "?startSleepInBed@Player@@UEAA?AW4BedSleepingResult@@AEBVBlockPos@@@Z", Player, int* a1, const char* a2) {
	auto res = original(this, a1, a2);
	if (res == 0) {
		sleepList.insert(getRealName());
		auto onlineNum = Global<Level>->getAllPlayers();
        if (onlineNum.size() <= 1) {
            return res;
        }
        sendSleepMsg(this);
        Sleep();
	}
	return res;
}

TInstanceHook(void, "?stopSleepInBed@Player@@UEAAX_N0@Z", Player, bool a1, char a2) {
	if (isSleeping()) {
		sleepList.erase(getRealName());
		StopSleep();
	}
	original(this, a1, a2);
}

TInstanceHook(void, "?setShouldSendSleepMessage@ServerLevel@@QEAAX_N@Z", ServerLevel, bool a1) {
    return original(this, false);
}
