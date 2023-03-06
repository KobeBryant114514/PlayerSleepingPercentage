#include "version.h"
#include <EventAPI.h>
#include <LoggerAPI.h>
#include "Global.h"
#include "setting.h"
#include <mc/ServerLevel.hpp>
#include <mc/Dimension.hpp>
#include <mc/Level.hpp>

void PluginInit(){
    logger.info("当前版本 2.1.1");
    logger.info("插件作者 Tsubasa6848");
    loadConfig();
    Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent) {
        RegSleepCommand();
        return true;
    });
    Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent) {
        Global<ServerLevel>->setShouldSendSleepMessage(false);
        sleepList.clear();
        return true;
    });
    Schedule::repeat([] {
        if (((Dimension*)Global<Level>->getOrCreateDimension(0).mHandle.lock().get())->isDay()) {
            sleepList.clear();
        }
    },10*60*20);
}
