#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] TEXT_PACKET
// ----------------------------------------------------------------------------

TextPacket::TextPacket_() {
  mcbiPacketConstruct<TextPacket>(this);
}
