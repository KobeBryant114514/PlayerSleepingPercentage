#include "Global.h"
#include "setting.h"
#include <mc/Level.hpp>
#include <mc/SetTimePacket.hpp>
#include <mc/LoopbackPacketSender.hpp>
#include <mc/SharedAttributes.hpp>
#include <mc/Attribute.hpp>
#include <mc/AttributeInstance.hpp>
#include <mc/Dimension.hpp>
#include <mc/Weather.hpp>
#include <mc/PacketSender.hpp>

static ScheduleTask SleepTask;

bool ifSleep() {
    float sleepNum = sleepList.size();
    float allNum = Global<Level>->getActivePlayerCount();
    auto needNum = (int)ceil(Settings::PlayerSleepingPercentage*allNum/100);
    if (sleepNum >= needNum) {
        auto nmsg = Settings::actionbar2;
        Global<Level>->broadcastText(nmsg, TextType::TIP);
        return true;
    }
    auto emsg = Settings::actionbar1;
    ReplaceStr(emsg, "{1}", std::to_string((int)sleepNum));
    ReplaceStr(emsg, "{2}", std::to_string(needNum));
    Global<Level>->broadcastText(emsg, TextType::TIP);
    return false;
}

void sendSleepMsg(Player* pl) {
    auto smsg = Settings::broadcast;
    ReplaceStr(smsg, "{1}", pl->getRealName());
    auto perc = Settings::PlayerSleepingPercentage;
    ReplaceStr(smsg, "{2}", std::to_string(perc));
    auto uuid = pl->getUuid();
    Global<Level>->forEachPlayer([uuid, smsg](Player& player)->bool {
        if (player.getUuid() != uuid) {
            player.sendTextPacket(smsg, TextType::RAW);
        }
        return true;
    });
}

void Sleep() {
    if (ifSleep()) {
        SleepTask.cancel();
        SleepTask = Schedule::delay([](){
            Global<Level>->forEachPlayer([](Player& pl)->bool {
                if (pl.isSleeping()) {
                    pl.setSleeping(true);
                    auto health = pl.getMutableAttribute(SharedAttributes::HEALTH);
                    health->resetToMaxValue();
                }
                return true;
            });
            Global<Level>->forEachDimension([](Dimension& dim)->bool {
                dim.getWeather().stop();
                return true;
            });
            int newtime = 24000 * ((Global<Level>->getTime() + 24000) / 24000);
            Global<Level>->setTime(newtime);
            try {
                SetTimePacket pkt = SetTimePacket(newtime);
                LoopbackPacketSender* pktSender = (LoopbackPacketSender*)Global<Level>->getPacketSender();
                pktSender->send(pkt);
            }
            catch(...){}
            sleepList.clear();
        }, 95);
    }
}

void StopSleep() {
    if (ifSleep() == false) {
        SleepTask.cancel();
    }
}