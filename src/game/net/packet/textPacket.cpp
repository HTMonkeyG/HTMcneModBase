#include "mcb_internal.hpp"

#pragma warning(disable: 26495)

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
    "41 B8 00 01 00 00 48 8D 4D ?  E8 ?  ?  ?  ?  48 "
    "8D 4D ?  E8 ",
  .indirect = HT_SCAN_E8,
  .offset = 0x13
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

  return fn_TextPacket_TextPacket
    ? HT_SUCCESS
    : HT_FAIL;
}

// ----------------------------------------------------------------------------
// [SECTION] TEXT_PACKET
// ----------------------------------------------------------------------------

TextPacket::TextPacket_() {
  // Proxy to the game.
  if (fn_TextPacket_TextPacket)
    fn_TextPacket_TextPacket(this);
}
