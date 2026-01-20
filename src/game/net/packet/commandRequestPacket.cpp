#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] COMMAND_REQUEST_PACKET_INIT
// ----------------------------------------------------------------------------

/* Type declarations. */

typedef void (__fastcall *PFN_CmdReqPacket_CmdReqPacket)(
  CommandRequestPacket *);

/* Function declarations. */

static HTStatus fnInit_CmdReqPacket(
  HMODULE, const McbiModInitializer *);

/* Struct declarations. */

static McbiModInitializer gInit_CommandRequestPacket{
  fnInit_CmdReqPacket,
  "CommandRequestPacket"
};

static const HTAsmSig sigE8_CmdReqPacket_CmdReqPacket{
  .sig =
    "48 89 4C 24 ?  53 48 83 EC 20 48 8B D9 E8 ?  ?  "
    "?  ?  90 48 8D 05 ?  ?  ?  ?  48 89 03 0F 57 C0 "
    "0F 11 43 30 48 C7 43 ",
  .indirect = HT_SCAN_DIRECT,
  .offset = 0x00
};

static PFN_CmdReqPacket_CmdReqPacket fn_CmdReqPacket_CmdReqPacket = nullptr;

/* Functions. */

static HTStatus fnInit_CmdReqPacket(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  fn_CmdReqPacket_CmdReqPacket = (PFN_CmdReqPacket_CmdReqPacket)HTSigScan(
    &sigE8_CmdReqPacket_CmdReqPacket);

  return HT_SUCCESS;
}

// ----------------------------------------------------------------------------
// [SECTION] COMMAND_REQUEST_PACKET
// ----------------------------------------------------------------------------

CommandRequestPacket::CommandRequestPacket_() {
  // Proxy to the game.
  if (fn_CmdReqPacket_CmdReqPacket)
    fn_CmdReqPacket_CmdReqPacket(this);
}