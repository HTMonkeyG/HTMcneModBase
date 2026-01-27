#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] COMMAND_OUTPUT_PACKET
// ----------------------------------------------------------------------------

CommandOutputPacket::CommandOutputPacket_() {
  mcbiPacketConstruct<CommandOutputPacket>(this);
}
