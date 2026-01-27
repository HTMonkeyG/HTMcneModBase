#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] ADD_PLAYER_PACKET
// ----------------------------------------------------------------------------

AddPlayerPacket::AddPlayerPacket_() {
  mcbiPacketConstruct<AddPlayerPacket>(this);
}
