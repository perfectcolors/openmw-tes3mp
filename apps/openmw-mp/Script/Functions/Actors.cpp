#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BaseActor.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Utils.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>

#include <components/esm/creaturestats.hpp>

#include "Actors.hpp"

using namespace mwmp;

BaseActorList *readActorList;
BaseActorList writeActorList;

BaseActor tempActor;
const BaseActor emptyActor = {};

static std::string tempCellDescription;

void ActorFunctions::ReadReceivedActorList() noexcept
{
    readActorList = mwmp::Networking::getPtr()->getReceivedActorList();
}

void ActorFunctions::ReadCellActorList(const char* cellDescription) noexcept
{
    ESM::Cell esmCell = Utils::getCellFromDescription(cellDescription);
    Cell *serverCell = CellController::get()->getCell(&esmCell);
    readActorList = serverCell->getActorList();
}

void ActorFunctions::ClearActorList() noexcept
{
    writeActorList.cell.blank();
    writeActorList.baseActors.clear();
}

void ActorFunctions::SetActorListPid(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeActorList.guid = player->guid;
}

void ActorFunctions::CopyReceivedActorListToStore() noexcept
{
    writeActorList = *readActorList;
}

unsigned int ActorFunctions::GetActorListSize() noexcept
{
    return readActorList->count;
}

unsigned char ActorFunctions::GetActorListAction() noexcept
{
    return readActorList->action;
}

const char *ActorFunctions::GetActorCell(unsigned int index) noexcept
{
    tempCellDescription = readActorList->baseActors.at(index).cell.getDescription();
    return tempCellDescription.c_str();
}

const char *ActorFunctions::GetActorRefId(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).refId.c_str();
}

unsigned int ActorFunctions::GetActorRefNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).refNum;
}

unsigned int ActorFunctions::GetActorMpNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).mpNum;
}

double ActorFunctions::GetActorPosX(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[0];
}

double ActorFunctions::GetActorPosY(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[1];
}

double ActorFunctions::GetActorPosZ(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[2];
}

double ActorFunctions::GetActorRotX(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[0];
}

double ActorFunctions::GetActorRotY(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[1];
}

double ActorFunctions::GetActorRotZ(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[2];
}

double ActorFunctions::GetActorHealthBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mBase;
}

double ActorFunctions::GetActorHealthCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mCurrent;
}

double ActorFunctions::GetActorHealthModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mMod;
}

double ActorFunctions::GetActorMagickaBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mBase;
}

double ActorFunctions::GetActorMagickaCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mCurrent;
}

double ActorFunctions::GetActorMagickaModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mMod;
}

double ActorFunctions::GetActorFatigueBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mBase;
}

double ActorFunctions::GetActorFatigueCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mCurrent;
}

double ActorFunctions::GetActorFatigueModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mMod;
}

const char *ActorFunctions::GetActorEquipmentItemRefId(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].refId.c_str();
}

int ActorFunctions::GetActorEquipmentItemCount(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].count;
}

int ActorFunctions::GetActorEquipmentItemCharge(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].charge;
}

double ActorFunctions::GetActorEquipmentItemEnchantmentCharge(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].enchantmentCharge;
}

bool ActorFunctions::DoesActorHavePlayerKiller(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.isPlayer;
}

int ActorFunctions::GetActorKillerPid(unsigned int index) noexcept
{
    Player *player = Players::getPlayer(readActorList->baseActors.at(index).killer.guid);

    if (player != nullptr)
        return player->getId();

    return -1;
}

const char *ActorFunctions::GetActorKillerRefId(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.refId.c_str();
}

unsigned int ActorFunctions::GetActorKillerRefNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.refNum;
}

unsigned int ActorFunctions::GetActorKillerMpNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.mpNum;
}

const char *ActorFunctions::GetActorKillerName(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.name.c_str();
}

bool ActorFunctions::DoesActorHavePosition(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).hasPositionData;
}

bool ActorFunctions::DoesActorHaveStatsDynamic(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).hasStatsDynamicData;
}

void ActorFunctions::SetActorListCell(const char* cellDescription) noexcept
{
    writeActorList.cell = Utils::getCellFromDescription(cellDescription);
}

void ActorFunctions::SetActorListAction(unsigned char action) noexcept
{
    writeActorList.action = action;
}

void ActorFunctions::SetActorCell(const char* cellDescription) noexcept
{
    tempActor.cell = Utils::getCellFromDescription(cellDescription);
}

void ActorFunctions::SetActorRefId(const char* refId) noexcept
{
    tempActor.refId = refId;
}

void ActorFunctions::SetActorRefNum(int refNum) noexcept
{
    tempActor.refNum = refNum;
}

void ActorFunctions::SetActorMpNum(int mpNum) noexcept
{
    tempActor.mpNum = mpNum;
}

void ActorFunctions::SetActorPosition(double x, double y, double z) noexcept
{
    tempActor.position.pos[0] = x;
    tempActor.position.pos[1] = y;
    tempActor.position.pos[2] = z;
}

void ActorFunctions::SetActorRotation(double x, double y, double z) noexcept
{
    tempActor.position.rot[0] = x;
    tempActor.position.rot[1] = y;
    tempActor.position.rot[2] = z;
}

void ActorFunctions::SetActorHealthBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mBase = value;
}

void ActorFunctions::SetActorHealthCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mCurrent = value;
}

void ActorFunctions::SetActorHealthModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mMod = value;
}

void ActorFunctions::SetActorMagickaBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mBase = value;
}

void ActorFunctions::SetActorMagickaCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mCurrent = value;
}

void ActorFunctions::SetActorMagickaModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mMod = value;
}

void ActorFunctions::SetActorFatigueBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mBase = value;
}

void ActorFunctions::SetActorFatigueCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mCurrent = value;
}

void ActorFunctions::SetActorFatigueModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mMod = value;
}

void ActorFunctions::SetActorSound(const char* sound) noexcept
{
    tempActor.sound = sound;
}

void ActorFunctions::SetActorAIAction(unsigned int action) noexcept
{
    tempActor.aiAction = action;
}

void ActorFunctions::SetActorAITargetToPlayer(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    tempActor.hasAiTarget = true;
    tempActor.aiTarget.isPlayer = true;

    tempActor.aiTarget.guid = player->guid;
}

void ActorFunctions::SetActorAITargetToObject(int refNum, int mpNum) noexcept
{
    tempActor.hasAiTarget = true;
    tempActor.aiTarget.isPlayer = false;

    tempActor.aiTarget.refNum = refNum;
    tempActor.aiTarget.mpNum = mpNum;
}

void ActorFunctions::SetActorAICoordinates(double x, double y, double z) noexcept
{
    tempActor.aiCoordinates.pos[0] = x;
    tempActor.aiCoordinates.pos[1] = y;
    tempActor.aiCoordinates.pos[2] = z;
}

void ActorFunctions::SetActorAIDistance(unsigned int distance) noexcept
{
    tempActor.aiDistance = distance;
}

void ActorFunctions::SetActorAIDuration(unsigned int duration) noexcept
{
    tempActor.aiDuration = duration;
}

void ActorFunctions::SetActorAIRepetition(bool shouldRepeat) noexcept
{
    tempActor.aiShouldRepeat = shouldRepeat;
}

void ActorFunctions::EquipActorItem(unsigned short slot, const char *refId, unsigned int count, int charge, double enchantmentCharge) noexcept
{
    tempActor.equipmentItems[slot].refId = refId;
    tempActor.equipmentItems[slot].count = count;
    tempActor.equipmentItems[slot].charge = charge;
    tempActor.equipmentItems[slot].enchantmentCharge = enchantmentCharge;
}

void ActorFunctions::UnequipActorItem(unsigned short slot) noexcept
{
    ActorFunctions::EquipActorItem(slot, "", 0, -1, -1);
}

void ActorFunctions::AddActor() noexcept
{
    writeActorList.baseActors.push_back(tempActor);

    tempActor = emptyActor;
}

void ActorFunctions::SendActorList() noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_LIST);
    actorPacket->setActorList(&writeActorList);
    actorPacket->Send(writeActorList.guid);
}

void ActorFunctions::SendActorAuthority() noexcept
{
    Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

    if (serverCell != nullptr)
    {
        serverCell->setAuthority(writeActorList.guid);

        mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AUTHORITY);
        actorPacket->setActorList(&writeActorList);
        actorPacket->Send(writeActorList.guid);

        // Also send this to everyone else who has the cell loaded
        serverCell->sendToLoaded(actorPacket, &writeActorList);
    }
}

void ActorFunctions::SendActorPosition(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_POSITION);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

void ActorFunctions::SendActorStatsDynamic(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_STATS_DYNAMIC);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

void ActorFunctions::SendActorEquipment(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_EQUIPMENT);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

void ActorFunctions::SendActorSpeech(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_SPEECH);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

void ActorFunctions::SendActorAI(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AI);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

void ActorFunctions::SendActorCellChange(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_CELL_CHANGE);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}


// All methods below are deprecated versions of methods from above

void ActorFunctions::ReadLastActorList() noexcept
{
    ReadReceivedActorList();
}

void ActorFunctions::InitializeActorList(unsigned short pid) noexcept
{
    ClearActorList();
    SetActorListPid(pid);
}

void ActorFunctions::CopyLastActorListToStore() noexcept
{
    CopyReceivedActorListToStore();
}

unsigned int ActorFunctions::GetActorRefNumIndex(unsigned int index) noexcept
{
    return GetActorRefNum(index);
}

unsigned int ActorFunctions::GetActorKillerRefNumIndex(unsigned int index) noexcept
{
    return GetActorKillerRefNum(index);
}

void ActorFunctions::SetActorRefNumIndex(int refNum) noexcept
{
    tempActor.refNum = refNum;
}
