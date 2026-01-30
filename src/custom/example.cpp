// ----------------------------------------------------------------------------
// custom/example.cpp
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

#if 0

static HTStatus fnInit_McbTestExample(
  HMODULE, const McbiModInitializer *);
static McbPacketFilterResult statsListener(
  Packet *, McbPacketFilterType, McbPacketSource);

/* Struct declarations. */

static McbiModInitializer gInit_McbTestExample{
  fnInit_McbTestExample,
  "McbTestExample"
};

/* Functions. */

static HTStatus fnInit_McbTestExample(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  mcbPacketFilterRegister(
    hModuleDll,
    McbPacketFilterType_Outgoing | McbPacketFilterType_Incoming,
    statsListener);

  return HT_SUCCESS;
}

static McbPacketFilterResult statsListener(
  Packet *pPacket,
  McbPacketFilterType type,
  McbPacketSource source
) {
  if (type == McbPacketFilterType_Outgoing && source == McbPacketSource_Server)
    return McbPacketFilterResult_Passed;
  if (type == McbPacketFilterType_Incoming && source == McbPacketSource_Client)
    return McbPacketFilterResult_Passed;

  if (source == McbPacketSource_Client)
    mcbLogI("Sent: %s", pPacket->getName().c_str());
  if (source == McbPacketSource_Server)
    mcbLogI("Recv: %s", pPacket->getName().c_str());

  return McbPacketFilterResult_Passed;
}

#endif
