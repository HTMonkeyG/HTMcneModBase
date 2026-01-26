// ----------------------------------------------------------------------------
// game/messageLoop.cpp
//
// - Emit event on several packets was recieved.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] NET_EVENT_INIT
// ----------------------------------------------------------------------------

static HTStatus fnInit_McbNetEvents(
  HMODULE, const McbiModInitializer *);
static McbPacketFilterResult statsListener(
  Packet *, McbPacketFilterType, McbPacketSource);

/* Struct declarations. */

static McbiModInitializer gInit_NetEvents{
  fnInit_McbNetEvents,
  "McbNetEvents"
};

/* Functions. */

static HTStatus fnInit_McbNetEvents(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  return mcbPacketFilterRegister(
    hModuleDll,
    McbPacketFilterType_Incoming | McbPacketFilterType_Outgoing,
    statsListener);
}

// ----------------------------------------------------------------------------
// [SECTION] MSG_EVENT_CLIENT
// ----------------------------------------------------------------------------

static McbPacketFilterResult statsListener(
  Packet *pPacket,
  McbPacketFilterType type,
  McbPacketSource source
) {
  if (type != McbPacketFilterType_Incoming || source != McbPacketSource_Server)
    return McbPacketFilterResult_Passed;

  if (pPacket->getId() == McPacketId_Text) {
    TextPacket *tp = RCAST(TextPacket *)(pPacket);

    if (tp->messageType == TextPacketType_Chat) {
      McbChatEventData ced;
      ced.message = tp->message.c_str();
      ced.playerName = tp->playerName.c_str();

      HTCommEmitEvent(
        mcbEventOnChatMessage,
        nullptr,
        (void *)&ced);
    }
  }

  return McbPacketFilterResult_Passed;
}
