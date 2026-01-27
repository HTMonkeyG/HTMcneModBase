// ----------------------------------------------------------------------------
// mcb_internal.hpp
//
// - Type definitions for Bedrock Protocol 785.
// ----------------------------------------------------------------------------

#ifndef __MCB_PROTOCOL_H__
#define __MCB_PROTOCOL_H__

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] TYPES
// ----------------------------------------------------------------------------

struct CommandOriginData_ {
  // Command type.
  CommandOriginType commandType;

  // Command UUID. The UUID carried in the CommandOutputPacket is the same as
  // when the command is sent.
  McUuid uuid;

  // Unknown.
  std::string requestId;

  // Unknown.
  u64 playerId;
};

struct CommandOutputMessage_ {
  // Whether the command was succeeded.
  bool successful;

  // Output message.
  std::string messageId;

  // Message parameters.
  std::vector<std::string> parameters;
};

struct CommandOutput_ {
  // Command output type.
  CommandOutputType outputType;

  // Unknown.
  void *commandPropertyBag;

  // Output messages.
  std::vector<CommandOutputMessage> messages;

  // The command's success count.
  int successCount;
};

struct MoveActorDeltaData_ {
  u64 actorId;
  MoveActorDeltaHeader flags;
  f32 position[3];
  i08 rotation[2];
  i08 rotateYHead;
};

// ----------------------------------------------------------------------------
// [SECTION] PACKETS
// ----------------------------------------------------------------------------

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

// AddPlayerPacket.
struct AddPlayerPacket_: Packet {
  static constexpr McPacketId id = McPacketId_AddPlayer;

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

// CommandOutputPacket.
struct CommandOutputPacket_: Packet {
  static constexpr McPacketId id = McPacketId_CommandOutput;

  CommandOutputPacket_();

  // Command origin.
  CommandOriginData originData;

  // Command output data collection.
  CommandOutput commandOutput;
};

// CommandRequestPacket.
struct CommandRequestPacket_: Packet {
  static constexpr McPacketId id = McPacketId_CommandRequest;

  CommandRequestPacket_();

  // Requested "slash" command string.
  std::string command;

  // Command origin.
  CommandOriginData commandOriginData;

  // Command version, currently 0x27.
  int version;

  // Unknown.
  bool isInternalSource;
};

struct InteractPacket_: Packet {
  static constexpr McPacketId id = McPacketId_Interact;

  InteractPacket_();

  InteractPacketAction action;
  u64 actorId;
  f32 position[3];
};

// MapInfoRequestPacket.
struct MapInfoRequestPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MapInfoRequest;

  MapInfoRequestPacket_();

  // Map unique id.
  u64 mapUniqueId;

  // Pixels, in 128 * 128 2D array format.
  // These are sent from the client to tell the Server map about terrain pixels
  // it doesn't know about.
  std::vector<COLORREF> clientPixels;
};

// MapCreateLockedCopyPacket.
struct MapCreateLockedCopyPacket_ {
  static constexpr McPacketId id = McPacketId_MapCreateLockedCopy;

  MapCreateLockedCopyPacket_();

  // Map unique id.
  u64 originalMapId;

  // Map unique id.
  u64 newMapId;
};

// MoveActorDeltaPacket.
struct MoveActorDeltaPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MoveDeltaActor;

  MoveActorDeltaPacket_();

  MoveActorDeltaData data;
};

// TextPacket.
struct TextPacket_: Packet {
  static constexpr McPacketId id = McPacketId_Text;

  TextPacket_();

  // Message type.
  TextPacketType messageType;

  // The message sender's name.
  std::string playerName;

  // Message content.
  std::string message;

  // Unknown.
  std::string senderXuid;

  // Check whether using formatted string.
  bool localize;

  // Replacement param list.
  std::vector<std::string> paramList;

  // Unknown.
  bool unk_5;

  // Unknown.
  std::string platformId;

  // Unknown.
  std::string filteredMessage;
};

#endif
