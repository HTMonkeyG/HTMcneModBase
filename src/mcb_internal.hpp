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

// Get time elapsed in seconds by performance counter.
static inline f64 mcbChrono(
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
static inline f64 mcbChrono(
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



/*
// Initializer class especially for packet fields.
class McbiPacketFields {
public:
  using PFN_DoInit = HTStatus (*)(
    HMODULE, const McbiModInitializer *);

  static inline const McbiModInitializer *list() {
    return McbiModInitializer::p;
  }

  static HTStatus setupAll(
    HMODULE hModuleDll);

  // Register a initializer.
  McbiPacketFields(
    const char *packetName,
    McPacketId packetId,
  ) 
    : function(_function)
    , name(_name)
  {
    prev = McbiPacketFields::p;
    McbiPacketFields::p = this;
  }

  ~McbiPacketFields() = default;

  inline const McbiPacketFields *getPrev() const {
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
  static inline McbiPacketFields *p = nullptr;

  McbiPacketFields *prev;
  PFN_DoInit function;
  const char *name;

  void *operator new(size_t) = delete;
  static void* operator new[](size_t) = delete;
  void operator delete(void *) = delete;
  void operator delete[](void *) = delete;

  McbiPacketFields(const McbiPacketFields &) = delete;
  McbiPacketFields &operator=(const McbiPacketFields &) = delete;
};*/

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/PACKET
// ----------------------------------------------------------------------------

// Abstract base class for data packets, copied from the game.
struct Packet_ {
public:
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

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/TEXT_PACKET
// ----------------------------------------------------------------------------

typedef u08 TextPacketMessageType;
enum TextPacketMessageType_ {
  TextPacketMessageType_Chat = 1,
  TextPacketMessageType_Translate = 2,
  TextPacketMessageType_JukeboxPopup = 4,
  TextPacketMessageType_SystemMessage = 6,
  TextPacketMessageType_Announcement = 8,
};

struct TextPacket_: Packet {
public:
  TextPacket_();

  TextPacketMessageType messageType;
  std::string playerName;
  std::string message;
  std::string senderXuid;
  bool localize;
  std::vector<std::string> paramList;
  bool unk_5;
  std::string platformId;
  std::string filteredMessage;
};

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/COMMAND_REQUEST_PACKET
// ----------------------------------------------------------------------------

typedef struct CommandOriginData_ CommandOriginData;
struct CommandOriginData_ {
  i32 commandType;
  u64 uuid[2];
  std::string requestId;
  u64 playerId;
};

struct CommandRequestPacket_: Packet {
public:
  CommandRequestPacket_();

  std::string command;
  CommandOriginData commandOriginData;
  int version;
  bool isInternalSource;
};

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/ADD_PLAYER_PACKET
// ----------------------------------------------------------------------------

struct AddPlayerPacket_: Packet {
public:
  AddPlayerPacket_();

  u64 uuid[2];
  std::string playerName;
  u64 actorRuntimeId;
  std::string platformChatId;
  f32 position[3];
  f32 velocity[3];
  f32 rotation[2];
  f32 yHeadRotation;
};

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET/COMMAND_OUTPUT_PACKET
// ----------------------------------------------------------------------------

#endif
