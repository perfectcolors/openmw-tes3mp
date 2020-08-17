//
// Created by koncord on 02.01.16.
//

#ifndef OPENMW_DEDICATEDPLAYER_HPP
#define OPENMW_DEDICATEDPLAYER_HPP

#include <components/esm/custommarkerstate.hpp>
#include <components/esm/loadcrea.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

#include "../mwclass/npc.hpp"

#include "../mwmechanics/aisequence.hpp"

#include "../mwworld/manualref.hpp"

#include <map>
#include <RakNetTypes.h>

namespace MWMechanics
{
    class Actor;
}

namespace mwmp
{
    struct DedicatedPlayer;

    class DedicatedPlayer : public BasePlayer
    {
        friend class PlayerList;

    public:

        void update(float dt);

        void move(float dt);
        void setBaseInfo();
        void setShapeshift();
        void setAnimFlags();
        void setAttributes();
        void setSkills();
        void setEquipment();
        void setCell();

        void updateMarker();
        void removeMarker();
        void setMarkerState(bool state);

        void playAnimation();
        void playSpeech();

        void createReference(const std::string& recId);
        void deleteReference();

        MWWorld::Ptr getPtr();
        MWWorld::ManualRef* getRef();

        void setPtr(const MWWorld::Ptr& newPtr);
        void reloadPtr();

    private:

        DedicatedPlayer(RakNet::RakNetGUID guid);
        virtual ~DedicatedPlayer();

        MWWorld::ManualRef* reference;

        MWWorld::Ptr ptr;

        ESM::CustomMarker marker;
        bool markerEnabled;

        std::string previousRace;
        std::string previousCreatureRefId;
        bool previousDisplayCreatureName;

        std::string creatureRecordId;

        bool hasFinishedInitialTeleportation;
    };
}
#endif //OPENMW_DEDICATEDPLAYER_HPP
