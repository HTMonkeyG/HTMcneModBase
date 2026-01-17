#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] TEXT_PACKET_INIT
// ----------------------------------------------------------------------------

/* Type declarations. */

typedef void (__fastcall *PFN_TextPacket_TextPacket)(
  TextPacket *);

/* Function declarations. */

static HTStatus fnInit_TextPacket(
  HMODULE, const McbiModInitializer *);

/* Struct declarations. */

static McbiModInitializer gInit_TextPacket{
  fnInit_TextPacket,
  "TextPacket"
};

static const HTAsmSig sigE8_TextPacket_TextPacket{
  .sig =
    "E8 ?  ?  ?  ?  90 C6 45 F0 05 48 8D 55 98 48 83 "
    "7D ?  ? ",
  .indirect = HT_SCAN_E8,
  .offset = 0x00
};

static PFN_TextPacket_TextPacket fn_TextPacket_TextPacket = nullptr;

/* Functions. */

static HTStatus fnInit_TextPacket(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  fn_TextPacket_TextPacket = (PFN_TextPacket_TextPacket)HTSigScan(
    &sigE8_TextPacket_TextPacket);

  return HT_SUCCESS;
}

// ----------------------------------------------------------------------------
// [SECTION] TEXT_PACKET
// ----------------------------------------------------------------------------

TextPacket::TextPacket_() {
  // Proxy to the game.
  if (fn_TextPacket_TextPacket)
    fn_TextPacket_TextPacket(this);
}
