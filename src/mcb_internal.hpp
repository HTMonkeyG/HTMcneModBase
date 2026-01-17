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
// [SECTION] TYPE_ALIASES
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

// ----------------------------------------------------------------------------
// [SECTION] MOD
// ----------------------------------------------------------------------------

// Module handle of McneModBase.
extern HMODULE hModuleDll;

// Thread id of the main thread.
extern DWORD gMainThreadId;

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
// [SECTION] GAME/NET/PACKET
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

struct CommandRequestPacket_: Packet {
public:
  std::string command;
};

#endif
