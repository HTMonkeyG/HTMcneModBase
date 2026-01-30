// ----------------------------------------------------------------------------
// game/net/sender.cpp
//
// - Packet sender functions and APIs.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] PACKET_SENDER
// ----------------------------------------------------------------------------

/* Type declarations. */

typedef void (__fastcall *PFN_LoopbackPacketSender_send)(
  void *, Packet *);

/* Function declarations. */

static HTStatus fnInit_LoopbackPacketSender(
  HMODULE, const McbiModInitializer *);
static void hook_LoopbackPacketSender_send(
  void *, Packet *);

/* Struct declarations. */

static McbiModInitializer gInit_LoopbackPacketSender{
  fnInit_LoopbackPacketSender,
  "LoopbackPacketSender"
};

static const HTAsmSig sig_LoopbackPacketSender_send{
  .sig =
    "48 83 EC 48 48 0F BE 41 ?  4C 8B C2 48 8D 51 20 "
    "48 83 C0 01 74 2A 48 83 F8 01 49 8B D0 ",
  .indirect = HT_SCAN_DIRECT,
  .offset = 0x00
};

static HTAsmFunction sfn_LoopbackPacketSender_send{
  .name = "LoopbackPacketSender::sendToServer()",
  .fn = nullptr,
  .detour = nullptr,
  .origin = nullptr
};

/* Variables. */

static void *gLoopbackPacketSenderC = nullptr
  , *gLoopbackPacketSenderS = nullptr;

/* Functions. */

static HTStatus fnInit_LoopbackPacketSender(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  sfn_LoopbackPacketSender_send.detour = (LPVOID)hook_LoopbackPacketSender_send;

  return mcbiSigScanAndCreateHook(
    hModuleDll,
    &sig_LoopbackPacketSender_send,
    &sfn_LoopbackPacketSender_send);
}

static inline void savePacketSender(
  void *sender
) {
  if (!sender)
    return;

  if (sender != gLoopbackPacketSenderC && GetCurrentThreadId() == gMainThreadId) {
    gLoopbackPacketSenderC = sender;
    mcbLogI("gLoopbackPacketSenderC = 0x%p", gLoopbackPacketSenderC);
  }

  if (sender != gLoopbackPacketSenderS && GetCurrentThreadId() != gMainThreadId) {
    gLoopbackPacketSenderS = sender;
    mcbLogI("gLoopbackPacketSenderS = 0x%p", gLoopbackPacketSenderC);
  }
}

static void hook_LoopbackPacketSender_send(
  void *pThis,
  Packet *packet
) {
  savePacketSender(pThis);

  McbPacketSource source = pThis == gLoopbackPacketSenderC
    ? McbPacketSource_Client
    : McbPacketSource_Server;
  McbPacketFilterResult filter = mcbiFilterOutgoingPacket(
    source,
    packet);

  if (filter == McbPacketFilterResult_Blocked)
    return;

  ((PFN_LoopbackPacketSender_send)sfn_LoopbackPacketSender_send.origin)(
    pThis,
    packet);
}

// ----------------------------------------------------------------------------
// [SECTION] PACKET_SENDER_EXPORT
// ----------------------------------------------------------------------------

MCB_API_ATTR HTStatus MCB_API mcbPacketSendToServer(
  Packet *packet
) {
  if (!sfn_LoopbackPacketSender_send.fn || !gLoopbackPacketSenderC || !packet)
    return HT_FAIL;

  ((PFN_LoopbackPacketSender_send)sfn_LoopbackPacketSender_send.fn)(
    gLoopbackPacketSenderC,
    packet);

  return HT_SUCCESS;
}

MCB_API_ATTR HTStatus MCB_API mcbPacketSendBroadcast(
  Packet *packet
) {
  if (!sfn_LoopbackPacketSender_send.fn || !gLoopbackPacketSenderS || !packet)
    return HT_FAIL;

  ((PFN_LoopbackPacketSender_send)sfn_LoopbackPacketSender_send.fn)(
    gLoopbackPacketSenderS,
    packet);

  return HT_SUCCESS;
}
