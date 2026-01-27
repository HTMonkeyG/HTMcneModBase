#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] MAP_ITEM_DATA_PACKET
// ----------------------------------------------------------------------------

ClientboundMapItemDataPacket_::ClientboundMapItemDataPacket_() {
  mcbiPacketConstruct<ClientboundMapItemDataPacket_>(this);
}
