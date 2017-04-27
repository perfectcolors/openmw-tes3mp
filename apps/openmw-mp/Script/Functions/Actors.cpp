#include <regex>

#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BaseActor.hpp>
#include "Actors.hpp"

using namespace mwmp;

BaseActorList scriptActorList;

BaseActor tempActor;
const BaseActor emptyActor = {};

void ActorFunctions::InitScriptActorList(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    scriptActorList.cell.blank();
    scriptActorList.baseActors.clear();
    scriptActorList.guid = player->guid;
}

unsigned int ActorFunctions::GetActorListSize() noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->count;
}

unsigned char ActorFunctions::GetLastActorListAction() noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->action;
}

const char *ActorFunctions::GetActorCell(unsigned int i) noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->baseActors.at(i).cell.getDescription().c_str();
}

const char *ActorFunctions::GetActorRefId(unsigned int i) noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->baseActors.at(i).refId.c_str();
}

int ActorFunctions::GetActorRefNumIndex(unsigned int i) noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->baseActors.at(i).refNumIndex;
}

int ActorFunctions::GetActorMpNum(unsigned int i) noexcept
{
    return mwmp::Networking::getPtr()->getLastActorList()->baseActors.at(i).mpNum;
}

void ActorFunctions::SetScriptActorListCell(const char* cellDescription) noexcept
{
    static std::regex exteriorCellPattern("^(-?\\d+), (-?\\d+)$");
    std::string description = cellDescription;
    std::smatch baseMatch;

    if (std::regex_match(description, baseMatch, exteriorCellPattern))
    {
        scriptActorList.cell.mData.mFlags &= ~ESM::Cell::Interior;

        // The first sub match is the whole string, so check for a length of 3
        if (baseMatch.size() == 3)
        {
            scriptActorList.cell.mData.mX = stoi(baseMatch[1].str());
            scriptActorList.cell.mData.mY = stoi(baseMatch[2].str());
        }
    }
    else
    {
        scriptActorList.cell.mData.mFlags |= ESM::Cell::Interior;
        scriptActorList.cell.mName = description;
    }
}

void ActorFunctions::SetScriptActorListAction(unsigned char action) noexcept
{
    scriptActorList.action = action;
}

void ActorFunctions::SetActorRefId(const char* refId) noexcept
{
    tempActor.refId = refId;
}

void ActorFunctions::SetActorRefNumIndex(int refNumIndex) noexcept
{
    tempActor.refNumIndex = refNumIndex;
}

void ActorFunctions::SetActorMpNum(int mpNum) noexcept
{
    tempActor.mpNum = mpNum;
}

void ActorFunctions::AddActor() noexcept
{
    scriptActorList.baseActors.push_back(tempActor);

    tempActor = emptyActor;
}

void ActorFunctions::SendActorList() noexcept
{
    mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_LIST)->setActorList(&scriptActorList);
    mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_LIST)->Send(scriptActorList.guid);
}

void ActorFunctions::SendActorAuthority() noexcept
{
    mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AUTHORITY)->setActorList(&scriptActorList);
    mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AUTHORITY)->Send(scriptActorList.guid);
}

