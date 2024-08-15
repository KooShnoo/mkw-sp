#include "KartObjectManager.hh"

#include "game/system/RaceConfig.hh"
#include "game/system/RaceManager.hh"

#include <Common.h>
#include <sp/kinoko/TestBuilder.hh>

extern "C" {
#include <revolution.h>
}

namespace Kart {

void KartObjectManager::init() {
    REPLACED(init)();

    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }
    SP::Kinoko::TestData data;
    data.pos = m_objects[0]->pos();
    data.fullRot = m_objects[0]->fullRot();
    data.extVel = m_objects[0]->extVel();
    data.intVel = m_objects[0]->intVel();
    data.speed = m_objects[0]->speed();
    data.acceleration = m_objects[0]->acceleration();
    data.softSpeedLimit = m_objects[0]->softSpeedLimit();
    data.mainRot = m_objects[0]->mainRot();
    data.angVel2 = m_objects[0]->angVel2();
    data.checkpointId = System::RaceManager::Instance()->player()->checkpointId;
    data.raceCompletion = System::RaceManager::Instance()->player()->raceCompletion;
    data.currentLap = System::RaceManager::Instance()->player()->currentLap;
    SP::Kinoko::TestBuilder::Instance()->writeDataNoFrameInc(data);
}

void KartObjectManager::calc() {
    REPLACED(calc)();

    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }

    if (System::RaceManager::Instance()->isStageReached(3)) {
        return;
    }

    SP::Kinoko::TestData data;
    data.pos = m_objects[0]->pos();
    data.fullRot = m_objects[0]->fullRot();
    data.extVel = m_objects[0]->extVel();
    data.intVel = m_objects[0]->intVel();
    data.speed = m_objects[0]->speed();
    data.acceleration = m_objects[0]->acceleration();
    data.softSpeedLimit = m_objects[0]->softSpeedLimit();
    data.mainRot = m_objects[0]->mainRot();
    data.angVel2 = m_objects[0]->angVel2();
    data.checkpointId = System::RaceManager::Instance()->player()->checkpointId;
    data.raceCompletion = System::RaceManager::Instance()->player()->raceCompletion;
    data.currentLap = System::RaceManager::Instance()->player()->currentLap;
    SP::Kinoko::TestBuilder::Instance()->writeData(data);
}

void KartObjectManager::end(u32 playerIdx) {
    REPLACED(end)(playerIdx);
    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }

    auto result = SP::Kinoko::TestBuilder::Instance()->save();
    if (!result) {
        SP_LOG(">> TEST SAVE ERROR: %s", result.error());
    } else {
        SP_LOG(">> TEST SAVED SUCCESSFULLY!");
    }
}

KartObjectManager *KartObjectManager::CreateInstance() {
    if (System::RaceConfig::Instance()->isTimeAttack()) {
        SP::Kinoko::TestBuilder::CreateInstance();
    }

    return REPLACED(CreateInstance)();
}

} // namespace Kart
