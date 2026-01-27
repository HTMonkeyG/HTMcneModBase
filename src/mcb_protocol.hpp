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

struct MapDecoration_ {
  MapDecorationType type;
  u08 rotation;
  u08 x;
  u08 y;
  std::string label;
  COLORREF color;
};

struct MapTrackedActor_ {
  MapItemTrackedActorType type;
  u64 uniqueId;
  i32 blockX;
  u32 blockY;
  i32 blockZ;
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

// AddPlayerPacket.
struct AddPlayerPacket_: Packet {
  static constexpr McPacketId id = McPacketId_AddPlayer;

  AddPlayerPacket_() {
    mcbiPacketConstruct<AddPlayerPacket_>(this);
  }

  u64 uuid[2];
  std::string playerName;
  u64 actorRuntimeId;
  std::string platformChatId;
  f32 position[3];
  f32 velocity[3];
  f32 rotation[2];
  f32 yHeadRotation;
};

// ClientboundMapItemDataPacket, also MapItemDataPacket.
struct ClientboundMapItemDataPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MapData;

  ClientboundMapItemDataPacket_() {
    mcbiPacketConstruct<ClientboundMapItemDataPacket_>(this);
  }

  // Map unique id list.
  std::vector<u64> mapIdList;

  // Map scale.
  char scale;

  // Map decorations.
  std::vector<MapDecoration> mapDecorations;

  // Map tracked actor ids.
  std::vector<MapTrackedActor> mapTrackedActor;

  // Texture coords.
  i64 xCoord;
  i64 yCoord;

  // Map origin coords.
  i64 mapOrigin[3];

  // Map dimension.
  i08 dimension;

  // Updated texture size.
  int textureWidth;
  int textureHeight;

  // Type flags.
  MapItemDataFlags typeFlags;

  // Updated pixels.
  std::vector<COLORREF> pixels;

  // Is locked.
  bool isLockedMap;
};

// CommandRequestPacket.
struct CommandBlockUpdatePacket_: Packet {
  static constexpr McPacketId id = McPacketId_CommandBlockUpdate;

  CommandBlockUpdatePacket_() {
    mcbiPacketConstruct<CommandBlockUpdatePacket_>(this);
  }

  // Command block position.
  BlockPos pos;

  // Command block mode.
  i32 commandBlockMode;

  // Is redstone if true.
  bool redstoneMode;

  // Is conditional if true.
  bool isConditional;

  // Command block minecart id.
  u64 actorId;

  // Command in the command block.
  std::string commmand;

  // The last output string.
  std::string lastOutput;

  // Command block name.
  std::string name;

  // Tick delay.
  u32 tickDelay;

  // Do track output if true.
  bool trackOutput;

  // Execute on the first tick.
  bool executeOnFirstTick;
};

// CommandOutputPacket.
struct CommandOutputPacket_: Packet {
  static constexpr McPacketId id = McPacketId_CommandOutput;

  CommandOutputPacket_() {
    mcbiPacketConstruct<CommandOutputPacket_>(this);
  };

  // Command origin.
  CommandOriginData originData;

  // Command output data collection.
  CommandOutput commandOutput;
};

// CommandRequestPacket.
struct CommandRequestPacket_: Packet {
  static constexpr McPacketId id = McPacketId_CommandRequest;

  CommandRequestPacket_() {
    mcbiPacketConstruct<CommandRequestPacket_>(this);
  };

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

  InteractPacket_() {
    mcbiPacketConstruct<InteractPacket_>(this);
  }

  InteractPacketAction action;
  u64 actorId;
  f32 position[3];
};

// MapInfoRequestPacket.
struct MapInfoRequestPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MapInfoRequest;

  MapInfoRequestPacket_() {
    mcbiPacketConstruct<MapInfoRequestPacket_>(this);
  }

  // Map unique id.
  u64 mapUniqueId;

  // Pixels, in 128 * 128 2D array format.
  // These are sent from the client to tell the Server map about terrain pixels
  // it doesn't know about.
  std::vector<COLORREF> clientPixels;
};

// MapCreateLockedCopyPacket.
struct MapCreateLockedCopyPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MapCreateLockedCopy;

  MapCreateLockedCopyPacket_() {
    mcbiPacketConstruct<MapCreateLockedCopyPacket_>(this);
  }

  // Map unique id.
  u64 originalMapId;

  // Map unique id.
  u64 newMapId;
};

// MoveActorDeltaPacket.
struct MoveActorDeltaPacket_: Packet {
  static constexpr McPacketId id = McPacketId_MoveDeltaActor;

  MoveActorDeltaPacket_() {
    mcbiPacketConstruct<MoveActorDeltaPacket_>(this);
  }

  MoveActorDeltaData data;
};

// TextPacket.
struct TextPacket_: Packet {
  static constexpr McPacketId id = McPacketId_Text;

  TextPacket_() {
    mcbiPacketConstruct<TextPacket_>(this);
  }

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
