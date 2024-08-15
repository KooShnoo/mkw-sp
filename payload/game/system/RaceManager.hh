#pragma once

#include <Common.hh>

namespace System {

class RaceManagerPlayer {
    public:
    u8 _0a[0xa - 0x00];
    u16 checkpointId;
    f32 raceCompletion;
    u8 _24[0x24-0x010];
    u16 currentLap;

};

class RaceManager {
public:
    bool isStageReached(int) const;

    static RaceManager *Instance();
    const RaceManagerPlayer *player() const {
        return *m_player;
    }

private:
    u8 _00[0xc - 0x00];
    RaceManagerPlayer **m_player;

    static RaceManager *s_instance;
};

} // namespace System
