// ----------------------------------------------------------------------------
// mcb_internal.hpp
//
// - HTMcneModbase internal declarations.
// ----------------------------------------------------------------------------

#ifndef __MCB_INTERNAL_H__
#define __MCB_INTERNAL_H__

#include <windows.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <algorithm>

#include "htmcb.h"

// ----------------------------------------------------------------------------
// [SECTION] DEFINES
// ----------------------------------------------------------------------------

#define i08 char
#define u08 unsigned char
#define i16 short
#define u16 unsigned short
#define i32 int
#define u32 unsigned int
#define i64 long long
#define u64 unsigned long long
#define f32 float
#define f64 double
#define nil void

#define SCAST(type) static_cast<type>
#define DCAST(type) dynamic_cast<type>
#define RCAST(type) reinterpret_cast<type>

#define mcbLogP(prefix, text, ...) HTTellText("[htmcb]" prefix " " text, ##__VA_ARGS__)
#define mcbLogI(text, ...) HTTellText("[htmcb]§f[INFO] " text, ##__VA_ARGS__)
#define mcbLogW(text, ...) HTTellText("[htmcb]§e[WARN] " text, ##__VA_ARGS__)
#define mcbLogE(text, ...) HTTellText("[htmcb]§c[ERR] " text, ##__VA_ARGS__)

// ----------------------------------------------------------------------------
// [SECTION] MOD
// ----------------------------------------------------------------------------

// Module handle of McneModBase.
extern HMODULE hModuleDll;

// Thread id of the main thread.
extern DWORD gMainThreadId;

// ImGui ready flag.
extern bool gGuiReady;

// Performance frequency.
extern LARGE_INTEGER gPerfFreq;

// Initializer class.
class McbiModInitializer {
public:
  using PFN_DoInit = HTStatus (*)(
    HMODULE, const McbiModInitializer *);

  static inline const McbiModInitializer *list() {
    return McbiModInitializer::p;
  }

  static HTStatus setupAll(
    HMODULE hModuleDll);

  // Register a initializer.
  McbiModInitializer(
    PFN_DoInit _function,
    const char *_name
  ) 
    : function(_function)
    , name(_name)
  {
    prev = McbiModInitializer::p;
    McbiModInitializer::p = this;
  }

  ~McbiModInitializer() = default;

  inline const McbiModInitializer *getPrev() const {
    return prev;
  }

  inline const char *getName() const {
    return name;
  }

  HTStatus operator()(
    HMODULE hModuleDll
  ) const {
    if (function)
      return function(hModuleDll, this);
    else
      return HT_FAIL;
  }

private:
  static inline McbiModInitializer *p = nullptr;

  McbiModInitializer *prev;
  PFN_DoInit function;
  const char *name;

  void *operator new(size_t) = delete;
  static void* operator new[](size_t) = delete;
  void operator delete(void *) = delete;
  void operator delete[](void *) = delete;

  McbiModInitializer(const McbiModInitializer &) = delete;
  McbiModInitializer &operator=(const McbiModInitializer &) = delete;
};

// Scan and create hook.
static inline HTStatus mcbiSigScanAndCreateHook(
  HMODULE hModuleDll,
  const HTAsmSig *sigXX,
  HTAsmFunction *sfn
) {
  HTStatus s;

  if (!HTSigScanFunc(sigXX, sfn))
    return HT_FAIL;

  s = HTAsmHookCreate(
    hModuleDll,
    sfn);
  if (!s)
    return HT_FAIL;

  s = HTAsmHookEnable(
    hModuleDll,
    sfn->fn);

  return s;
}

// ----------------------------------------------------------------------------
// [SECTION] UTILS
// ----------------------------------------------------------------------------

// Generate a McUuid struct.
HTStatus mcbiUuidGen(
  McUuid *uuid);

// Get time elapsed in seconds by performance counter.
static inline f64 mcbiChrono(
  f64 *lastTime
) {
  LARGE_INTEGER qpc;
  f64 sec, result;

  if (!lastTime)
    return 0;

  QueryPerformanceCounter(
    &qpc);    

  sec = (f64)qpc.QuadPart / (f64)gPerfFreq.QuadPart;

  if (!*lastTime) {
    *lastTime = sec;
    return 0;
  }

  result = sec - *lastTime;
  *lastTime = sec;

  return result;
}

// Get time elapsed in seconds by performance counter.
static inline f64 mcbiChrono(
  f64 lastTime = 0
) {
  LARGE_INTEGER qpc;
  f64 sec;

  QueryPerformanceCounter(
    &qpc);    

  sec = (f64)qpc.QuadPart / (f64)gPerfFreq.QuadPart;

  return sec - lastTime;
}

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET
// ----------------------------------------------------------------------------

// Create a packet with MineraftPackets::createPacket().
std::shared_ptr<Packet> mcCreateMinecraftPacket(
  McPacketId id);

// Create a packet with MineraftPackets::createPacket().
template<typename T>
std::shared_ptr<T> mcCreateMinecraftPacket() {
  auto ptr = mcCreateMinecraftPacket(T::id);

  return std::static_pointer_cast<T>(ptr);
}

// Filter packets.
McbPacketFilterResult mcbiFilterOutgoingPacket(
  McbPacketSource source,
  Packet *packet);

McbPacketFilterResult mcbiFilterIncomingPacket(
  McbPacketSource source,
  Packet *packet);

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/FIELDS
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET
// ----------------------------------------------------------------------------

using McbiSavedPacket = std::pair<std::shared_ptr<Packet>, void *>;

// Pre-saved vftable.
extern std::unordered_map<McPacketId, McbiSavedPacket> gSavedVftable;

// Construct from a pre-saved Packet object.
// The template type passed in must be a subclass of the packet object.
template<typename T>
void mcbiPacketConstruct(
  T *pPacket
) {
  auto it = gSavedVftable.find(T::id);

  if (it != gSavedVftable.end()) {
    // Copy the Packet object (virtual function and handler) constructed
    // by the game.
    // To prevent resource ownership conflicts, members of subclasses are
    // not copied.
    memcpy(
      RCAST(void *)(pPacket),
      RCAST(void *)(it->second.first.get()),
      sizeof(Packet));
  }
}

// Abstract base class for data packets, copied from the game.
struct Packet_ {
  static constexpr McPacketId id = McPacketId_END;

  Packet_();

  // Destructor.
  virtual ~Packet_();

  // Get packet id.
  virtual i32 getId();

  // Get packet name.
  virtual std::string getName();

  virtual void *unknown_1();

  // Serialize the packet to binary.
  virtual void *write(void *);

  // Deserialize the common part of the packet from binary.
  virtual void *read(void *);

  virtual u08 unknown_2();
  virtual u08 unknown_3();

  // Deserialize the rest of the packet from binary.
  virtual void *_read(void *);

  u64 unk_1;
  char subClientId;
  u64 unk_2;
  void *handler;
  u64 unk_3;
};

// Bedrock Protocol.
#include "mcb_protocol.hpp"

#endif
