#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] MAP_INFO_REQUEST_PACKET
// ----------------------------------------------------------------------------

MapInfoRequestPacket::MapInfoRequestPacket_() {
  mcbiPacketConstruct<MapInfoRequestPacket>(this);
}
