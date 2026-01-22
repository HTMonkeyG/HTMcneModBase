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

// ----------------------------------------------------------------------------
// [SECTION] PACKETS
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

// AddPlayerPacket.
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

// TextPacket.
struct TextPacket_: Packet {
public:
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

// CommandOutputPacket.
struct CommandOutputPacket_: Packet {
public:
  CommandOutputPacket_();

  // Command origin.
  CommandOriginData originData;

  // Command output type.
  CommandOutputType outputType;

  // The command's success count.
  u32 successCount;

  // Output messages.
  std::vector<CommandOutputMessage> outputMessages;

  // Unknown.
  std::string dataSet;
};

// CommandRequestPacket.
struct CommandRequestPacket_: Packet {
public:
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

#endif
