#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] MAP_CREATE_LOCKED_PACKET
// ----------------------------------------------------------------------------

MapCreateLockedCopyPacket::MapCreateLockedCopyPacket_() {
  mcbiPacketConstruct<MapCreateLockedCopyPacket>(this);
}
