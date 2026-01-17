// ----------------------------------------------------------------------------
// game/net/filter.cpp
//
// - Packet filter APIs.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

static std::set<PFN_mcbPacketFilter> gIncomingFilter
  , gOutgoingFilter;
static std::shared_mutex gMutex;

McbPacketFilterResult mcbiFilterOutgoingPacket(
  McbPacketSource source,
  Packet *packet
) {
  std::shared_lock<std::shared_mutex> lock{gMutex};

  for (auto &filter: gOutgoingFilter) {
    McbPacketFilterResult result = filter(packet, source);

    if (result == McbPacketFilterResult_Blocked)
      return McbPacketFilterResult_Blocked;
    else if (result == McbPacketFilterResult_Filtered)
      return McbPacketFilterResult_Filtered;
  }

  return McbPacketFilterResult_Filtered;
}

McbPacketFilterResult mcbiFilterIncomingPacket(
  McbPacketSource source,
  Packet *packet
) {
  std::shared_lock<std::shared_mutex> lock{gMutex};

  for (auto &filter: gIncomingFilter) {
    McbPacketFilterResult result = filter(packet, source);

    if (result == McbPacketFilterResult_Blocked)
      return McbPacketFilterResult_Blocked;
    else if (result == McbPacketFilterResult_Filtered)
      return McbPacketFilterResult_Filtered;
  }

  return McbPacketFilterResult_Filtered;
}

MCB_API_ATTR HTStatus MCB_API mcbPacketFilterRegister(
  HMODULE hOwner,
  McbPacketFilterType type,
  PFN_mcbPacketFilter filter
) {
  std::lock_guard<std::shared_mutex> lock{gMutex};
  bool success = false;
  (void)hOwner;

  if (!filter)
    return HT_FAIL;

  if (type == McbPacketFilterType_Incoming)
    success = gIncomingFilter.insert(filter).second;
  else if (type == McbPacketFilterType_Outgoing)
    success = gOutgoingFilter.insert(filter).second;

  return success ? HT_SUCCESS : HT_FAIL;
}
