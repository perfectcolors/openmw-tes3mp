#ifndef OPENMW_LOCALPLAYER_HPP
#define OPENMW_LOCALPLAYER_HPP

#include <components/openmw-mp/Base/BasePlayer.hpp>
#include "../mwworld/ptr.hpp"
#include <RakNetTypes.h>

namespace mwmp
{
    class Networking;
    class LocalPlayer : public BasePlayer
    {
    public:

        LocalPlayer();
        virtual ~LocalPlayer();

        time_t deathTime;
        bool receivedCharacter;

        bool isReceivingInventory;
        bool isReceivingQuickKeys;
        bool isPlayingAnimation;
        bool diedSinceArrestAttempt;

        void update();

        bool processCharGen();
        bool isLoggedIn();

        void updateStatsDynamic(bool forceUpdate = false);
        void updateAttributes(bool forceUpdate = false);
        void updateSkills(bool forceUpdate = false);
        void updateLevel(bool forceUpdate = false);
        void updateBounty(bool forceUpdate = false);
        void updateReputation(bool forceUpdate = false);
        void updatePosition(bool forceUpdate = false);
        void updateCell(bool forceUpdate = false);
        void updateEquipment(bool forceUpdate = false);
        void updateInventory(bool forceUpdate = false);
        void updateAttack();
        void updateAnimFlags(bool forceUpdate = false);

        void addItems();
        void addSpells();
        void addJournalItems();
        void addTopics();

        void removeItems();
        void removeSpells();

        void resurrect();

        void closeInventoryWindows();
        void updateInventoryWindow();

        void setCharacter();
        void setDynamicStats();
        void setAttributes();
        void setSkills();
        void setLevel();
        void setBounty();
        void setReputation();
        void setPosition();
        void setMomentum();
        void setCell();
        void setClass();
        void setEquipment();
        void setInventory();
        void setSpellbook();
        void setQuickKeys();
        void setFactions();
        void setKills();
        void setBooks();
        void setShapeshift();
        void setMarkLocation();
        void setSelectedSpell();

        void sendClass();
        void sendInventory();
        void sendItemChange(const mwmp::Item& item, unsigned int action);
        void sendItemChange(const MWWorld::Ptr& itemPtr, int count, unsigned int action);
        void sendItemChange(const std::string& refId, int count, unsigned int action);
        void sendSpellbook();
        void sendSpellChange(std::string id, unsigned int action);
        void sendQuickKey(unsigned short slot, int type, const std::string& itemId = "");
        void sendJournalEntry(const std::string& quest, int index, const MWWorld::Ptr& actor);
        void sendJournalIndex(const std::string& quest, int index);
        void sendFactionRank(const std::string& factionId, int rank);
        void sendFactionExpulsionState(const std::string& factionId, bool isExpelled);
        void sendFactionReputation(const std::string& factionId, int reputation);
        void sendTopic(const std::string& topic);
        void sendKill(const std::string& refId, int number);
        void sendBook(const std::string& bookId);
        void sendWerewolfState(bool isWerewolf);
        void sendMarkLocation(const ESM::Cell& newMarkCell, const ESM::Position& newMarkPosition);
        void sendSelectedSpell(const std::string& newSelectedSpellId);
        void sendItemUse(const MWWorld::Ptr& itemPtr);
        void sendCellStates();

        void clearCellStates();
        void clearCurrentContainer();

        void storeCellState(const ESM::Cell& cell, int stateType);
        void storeCurrentContainer(const MWWorld::Ptr& container);

        void playAnimation();
        void playSpeech();

        MWWorld::Ptr getPlayerPtr();

    private:
        Networking *getNetworking();

    };
}

#endif //OPENMW_LOCALPLAYER_HPP
