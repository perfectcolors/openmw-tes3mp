#ifndef OPENMW_PROCESSORWORLDKILLCOUNT_HPP
#define OPENMW_PROCESSORWORLDKILLCOUNT_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorWorldKillCount : public PlayerProcessor
    {
    public:
        ProcessorWorldKillCount()
        {
            BPP_INIT(ID_WORLD_KILL_COUNT)
        }

        void Do(PlayerPacket &packet, Player &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Script::Call<Script::CallbackIdentity("OnWorldKillCount")>(player.getId());
        }
    };
}

#endif //OPENMW_PROCESSORWORLDKILLCOUNT_HPP
