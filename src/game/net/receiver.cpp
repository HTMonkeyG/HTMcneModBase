// ----------------------------------------------------------------------------
// game/net/sender.cpp
//
// - Packet receiver functions and APIs.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] PACKET_RECEIVER
// ----------------------------------------------------------------------------

/* Type declarations. */

typedef void *(__fastcall *PFN_Packet_readNoHeader)(
  Packet *, void *, void *, const void *);

/* Function declarations. */

static HTStatus fnInit_Packetize(
  HMODULE, const McbiModInitializer *);
static void *hook_Packet_readNoHeader(
  Packet *, void *, void *, const void *);

/* Struct declarations. */

static McbiModInitializer gInit_Packetize{
  fnInit_Packetize,
  "Packetize"
};

static const HTAsmSig sigE8_Packet_readNoHeader{
  .sig =
    "4D 8B 46 ?  48 8D 54 24 ?  48 8B 09 E8 ",
  .indirect = HT_SCAN_E8,
  .offset = 0x0C
};

static HTAsmFunction sfn_Packet_readNoHeader{
  .name = "Packet::readNoHeader()",
  .fn = nullptr,
  .detour = nullptr,
  .origin = nullptr
};

/* Variables. */

static void *gLoopbackPacketSenderC = nullptr
  , *gLoopbackPacketSenderS = nullptr;

/* Functions. */

static HTStatus fnInit_Packetize(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  HTSigScanFunc(
    &sigE8_Packet_readNoHeader,
    &sfn_Packet_readNoHeader);

  sfn_Packet_readNoHeader.detour = (LPVOID)hook_Packet_readNoHeader;

  HTAsmHookCreate(
    hModuleDll,
    &sfn_Packet_readNoHeader);
  HTAsmHookEnable(
    hModuleDll,
    sfn_Packet_readNoHeader.fn);

  return HT_SUCCESS;
}

static void *hook_Packet_readNoHeader(
  Packet *pThis,
  void *a2,
  void *stream,
  const void *subClientId
) {
  void *result = ((PFN_Packet_readNoHeader)sfn_Packet_readNoHeader.origin)(
    pThis,
    a2,
    stream,
    subClientId);

  // TOFIX: Need a better way to check the packet source...
  McbPacketSource source = GetCurrentThreadId() == gMainThreadId
    ? McbPacketSource_Server
    : McbPacketSource_Client;
  
  McbPacketFilterResult filter = mcbiFilterIncomingPacket(
    source,
    pThis);

  if (filter == McbPacketFilterResult_Blocked)
    // Reset the handler to block the packet.
    pThis->handler = nullptr;

  return result;
}
