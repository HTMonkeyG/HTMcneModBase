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

static PFN_Packet_Packet fn_Packet_Packet = nullptr;

/* Functions. */

static HTStatus fnInit_Packet(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  fn_Packet_Packet = (PFN_Packet_Packet)HTSigScan(
    &sigE8_Packet_Packet);

  return fn_Packet_Packet
    ? HT_SUCCESS
    : HT_FAIL;
}

// ----------------------------------------------------------------------------
// [SECTION] PACKET
// ----------------------------------------------------------------------------

Packet::Packet_() {
  // Proxy to the game's constructor.
  if (fn_Packet_Packet)
    fn_Packet_Packet(this);
}

// We have implemented all the virtual functions of Packet, but we actually do
// nothing. All the virtual functions is overriden by the game's vftable.

Packet::~Packet_() { }

i32 Packet::getId() {
  return 0;
}

std::string Packet::getName() {
  return "";
}

void *Packet::unknown_1() {
  return nullptr;
}

void *Packet::write(
  void *
) {
  return nullptr;
}

void *Packet::read(
  void *
) {
  return nullptr;
}

u08 Packet::unknown_2() {
  return 0;
}

u08 Packet::unknown_3() {
  return 0;
}

void *Packet::_read(
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
