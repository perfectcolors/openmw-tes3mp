#include "PacketCellReset.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketCellReset::PacketCellReset(RakNet::RakPeerInterface *peer) : WorldstatePacket(peer)
{
    packetID = ID_CELL_RESET;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketCellReset::Packet(RakNet::BitStream *bs, bool send)
{
    WorldstatePacket::Packet(bs, send);

    // Placeholder
}
