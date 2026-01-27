// ----------------------------------------------------------------------------
// game/net/packet/packet.cpp
//
// - Local definitions of struct Packet_.
// - Create packets by id.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

// ----------------------------------------------------------------------------
// [SECTION] PACKET_INIT
// ----------------------------------------------------------------------------

/* Type declarations. */

typedef void (__fastcall *PFN_Packet_Packet)(
  Packet *);
typedef std::shared_ptr<Packet> (__fastcall *PFN_MineraftPackets_createPacket)(
  McPacketId);

/* Function declarations. */

static HTStatus fnInit_Packet(
  HMODULE, const McbiModInitializer *);

/* Struct declarations. */

static McbiModInitializer gInit_Packet{
  fnInit_Packet,
  "Packet"
};

static const HTAsmSig sigE8_Packet_Packet{
  .sig =
    "4C 8B A4 24 ?  ?  ?  ?  4C 8B AC 24 ?  ?  ?  ?  "
    "E8 ?  ?  ?  ?  90 48 8D 05 ",
  .indirect = HT_SCAN_E8,
  .offset = 0x10
};

static const HTAsmSig sigE8_MineraftPackets_createPacket{
  .sig =
    "8B D7 48 8D 8D ?  ?  ?  ?  E8 ?  ?  ?  ?  90 48 "
    "8B 8D ?  ?  ?  ?  48 85 C9 0F 84 ?  ?  ?  ?  48 "
    "8B 01 ",
  .indirect = HT_SCAN_E8,
  .offset = 0x09
};

static PFN_Packet_Packet fn_Packet_Packet = nullptr;
static PFN_MineraftPackets_createPacket fn_MineraftPackets_createPacket = nullptr;

std::unordered_map<McPacketId, McbiSavedPacket> gSavedVftable;

/* Functions. */

static HTStatus fnInit_Packet(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  fn_Packet_Packet = (PFN_Packet_Packet)HTSigScan(
    &sigE8_Packet_Packet);

  if (!fn_Packet_Packet)
    return HT_FAIL;

  fn_MineraftPackets_createPacket = (PFN_MineraftPackets_createPacket)HTSigScan(
    &sigE8_MineraftPackets_createPacket);

  if (!fn_MineraftPackets_createPacket)
    return HT_FAIL;

  // Save the vftable of all packet objects.
  for (McPacketId i = McPacketId_BEGIN; i < McPacketId_END; i++) {
    auto packet = mcCreateMinecraftPacket(i);

    if (packet)
      gSavedVftable[i] = McbiSavedPacket{packet, *RCAST(void **)(packet.get())};
  }

  return HT_SUCCESS;
}

// ----------------------------------------------------------------------------
// [SECTION] PACKET
// ----------------------------------------------------------------------------

std::shared_ptr<Packet> mcCreateMinecraftPacket(
  McPacketId id
) {
  if (!fn_MineraftPackets_createPacket)
    return nullptr;

  return fn_MineraftPackets_createPacket(
    id);
}

Packet_::Packet_() {
  // Proxy to the game's constructor.
  if (fn_Packet_Packet)
    fn_Packet_Packet(this);
}

// We have implemented all the virtual functions of Packet, but we actually do
// nothing. All the virtual functions is overriden by the game's vftable.

Packet_::~Packet_() { }

i32 Packet_::getId() {
  return 0;
}

std::string Packet_::getName() {
  return "";
}

void *Packet_::unknown_1() {
  return nullptr;
}

void *Packet_::write(
  void *
) {
  return nullptr;
}

void *Packet_::read(
  void *
) {
  return nullptr;
}

u08 Packet_::unknown_2() {
  return 0;
}

u08 Packet_::unknown_3() {
  return 0;
}

void *Packet_::_read(
  void *
) {
  return nullptr;
}

// ----------------------------------------------------------------------------
// [SECTION] PACKET_EXPORT
// ----------------------------------------------------------------------------

MCB_API_ATTR Packet *MCB_API mcbCreatePacket(
  McPacketId id
) {
  return nullptr;
}

MCB_API_ATTR void MCB_API mcbDestroyPacket(
  Packet *packet
) {
  ;
}
