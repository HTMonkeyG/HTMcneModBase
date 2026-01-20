// ----------------------------------------------------------------------------
// game/net/netStats.cpp
//
// - Listening the game's network stats.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] NET_STATS_INIT
// ----------------------------------------------------------------------------

/* Function declarations. */

static HTStatus fnInit_McbNetStats(
  HMODULE, const McbiModInitializer *);
static McbPacketFilterResult statsListener(
  Packet *, McbPacketFilterType, McbPacketSource);

/* Struct declarations. */

static McbiModInitializer gInit_MessageLoopEventEmitter{
  fnInit_McbNetStats,
  "McbNetStats"
};

/* Functions. */

static HTStatus fnInit_McbNetStats(
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
// [SECTION] NET_STATS
// ----------------------------------------------------------------------------

McbNetStats gNetStats = {0};

static f64 gFirstTimeSend = 0
  , gFirstTimeRecv = 0;

static i32 gSendPackets = 0
  , gRecvPackets = 0;

static McbPacketFilterResult statsListener(
  Packet *pPacket,
  McbPacketFilterType type,
  McbPacketSource source
) {
  f64 deltaTime;

  if (
    type == McbPacketFilterType_Incoming
    && source == McbPacketSource_Server
  ) {
    deltaTime = gFirstTimeRecv - mcbChrono();

    if (deltaTime > 1.0) {
      gNetStats.clientRecvPacketsPerSec = (f32)(gRecvPackets / deltaTime);
      gRecvPackets = 0;
    } else
      gRecvPackets++;

    return McbPacketFilterResult_Passed;
  }

  if (
    type == McbPacketFilterType_Outgoing
    && source == McbPacketSource_Client
  ) {
    deltaTime = gFirstTimeRecv - mcbChrono();

    if (deltaTime > 1.0) {
      gNetStats.clientSendPacketsPerSec = (f32)(gSendPackets / deltaTime);
      gSendPackets = 0;
    } else
      gSendPackets++;

    return McbPacketFilterResult_Passed;
  }

  return McbPacketFilterResult_Passed;
}

// ----------------------------------------------------------------------------
// [SECTION] NET_STATS_EXPORT
// ----------------------------------------------------------------------------

MCB_API_ATTR HTStatus MCB_API mcbNetStatsGet(
  McbNetStats *stats
) {
  if (!stats)
    return HT_FAIL;

  *stats = gNetStats;

  return HT_SUCCESS;
}
