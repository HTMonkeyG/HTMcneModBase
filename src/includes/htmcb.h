// ----------------------------------------------------------------------------
// HTMcneModBase
// - A Simple mod developed for exporting in-game funtions of Minecraft.
// <https://www.github.com/HTMonkeyG/HTMcneModBase>
//
// MIT License
//
// Copyright (c) 2026 HTMonkeyG
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// ----------------------------------------------------------------------------

#ifndef __HTMCB_H__
#define __HTMCB_H__

#include <windows.h>
#include "includes/htmodloader.h"

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------------
// [SECTION] BASIC_DECL
// ----------------------------------------------------------------------------

// API attributes.
#define MCB_API HTMLAPI

#ifndef MCB_API_ATTR
#define MCB_API_ATTR
#endif

// Namespace prefix.
#define mcbNamespace "htmcb"
#define mcbMakeNamespace(literal) mcbNamespace ":" literal

// Events
#define mcbEventMainLoop mcbMakeNamespace("mainLoop")

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET
// ----------------------------------------------------------------------------

// Net stats.
typedef struct {
  float clientRecvPacketsPerSec;
  float clientSendPacketsPerSec;
} McbNetStats;

MCB_API_ATTR HTStatus MCB_API mcbNetStatsGet(
  McbNetStats *stats);

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET
// ----------------------------------------------------------------------------

// Part of bedrock-protocol 785.

typedef int McPacketId;
enum McPacketId_ {
  McPacketId_BEGIN = 0,

  McPacketId_KeepAlive = McPacketId_BEGIN,
  McPacketId_Login = 1,
  McPacketId_PlayStatus = 2,
  McPacketId_ServerToClientHandshake = 3,
  McPacketId_ClientToServerHandshake = 4,
  McPacketId_Disconnect = 5,
  McPacketId_ResourcePacksInfo = 6,
  McPacketId_ResourcePackStack = 7,
  McPacketId_ResourcePackClientResponse = 8,
  McPacketId_Text = 9,
  McPacketId_SetTime = 10,
  McPacketId_StartGame = 11,
  McPacketId_AddPlayer = 12,
  McPacketId_AddActor = 13,
  McPacketId_RemoveActor = 14,
  McPacketId_AddItemActor = 15,
  McPacketId_ServerPlayerPostMovePosition = 16,
  McPacketId_TakeItemActor = 17,
  McPacketId_MoveAbsoluteActor = 18,
  McPacketId_MovePlayer = 19,
  McPacketId_PassengerJump = 20,
  McPacketId_UpdateBlock = 21,
  McPacketId_AddPainting = 22,
  //McPacketId_TickSync_deprecated = 23,
  McPacketId_LevelSoundEventV1 = 24,
  McPacketId_LevelEvent = 25,
  McPacketId_TileEvent = 26,
  McPacketId_ActorEvent = 27,
  McPacketId_MobEffect = 28,
  McPacketId_UpdateAttributes = 29,
  McPacketId_InventoryTransaction = 30,
  McPacketId_PlayerEquipment = 31,
  McPacketId_MobArmorEquipment = 32,
  McPacketId_Interact = 33,
  McPacketId_BlockPickRequest = 34,
  McPacketId_ActorPickRequest = 35,
  McPacketId_PlayerAction = 36,
  //McPacketId_ActorFall_deprecated = 37,
  McPacketId_HurtArmor = 38,
  McPacketId_SetActorData = 39,
  McPacketId_SetActorMotion = 40,
  McPacketId_SetActorLink = 41,
  McPacketId_SetHealth = 42,
  McPacketId_SetSpawnPosition = 43,
  McPacketId_Animate = 44,
  McPacketId_Respawn = 45,
  McPacketId_ContainerOpen = 46,
  McPacketId_ContainerClose = 47,
  McPacketId_PlayerHotbar = 48,
  McPacketId_InventoryContent = 49,
  McPacketId_InventorySlot = 50,
  McPacketId_ContainerSetData = 51,
  McPacketId_CraftingData = 52,
  //McPacketId_CraftingEvent_Deprecated = 53,
  McPacketId_GuiDataPickItem = 54,
  //McPacketId_AdventureSettings_Deprecated = 55,
  McPacketId_BlockActorData = 56,
  McPacketId_PlayerInput = 57,
  McPacketId_FullChunkData = 58,
  McPacketId_SetCommandsEnabled = 59,
  McPacketId_SetDifficulty = 60,
  McPacketId_ChangeDimension = 61,
  McPacketId_SetPlayerGameType = 62,
  McPacketId_PlayerList = 63,
  McPacketId_SimpleEvent = 64,
  McPacketId_LegacyTelemetryEvent = 65,
  McPacketId_SpawnExperienceOrb = 66,
  McPacketId_MapData = 67,
  McPacketId_MapInfoRequest = 68,
  McPacketId_RequestChunkRadius = 69,
  McPacketId_ChunkRadiusUpdated = 70,
  //McPacketId_ItemFrameDropItem_Deprecated = 71,
  McPacketId_GameRulesChanged = 72,
  McPacketId_Camera = 73,
  McPacketId_BossEvent = 74,
  McPacketId_ShowCredits = 75,
  McPacketId_AvailableCommands = 76,
  McPacketId_CommandRequest = 77,
  McPacketId_CommandBlockUpdate = 78,
  McPacketId_CommandOutput = 79,
  McPacketId_UpdateTrade = 80,
  McPacketId_UpdateEquip = 81,
  McPacketId_ResourcePackDataInfo = 82,
  McPacketId_ResourcePackChunkData = 83,
  McPacketId_ResourcePackChunkRequest = 84,
  McPacketId_Transfer = 85,
  McPacketId_PlaySound = 86,
  McPacketId_StopSound = 87,
  McPacketId_SetTitle = 88,
  McPacketId_AddBehaviorTree = 89,
  McPacketId_StructureBlockUpdate = 90,
  McPacketId_ShowStoreOffer = 91,
  McPacketId_PurchaseReceipt = 92,
  McPacketId_PlayerSkin = 93,
  McPacketId_SubclientLogin = 94,
  McPacketId_AutomationClientConnect = 95,
  McPacketId_SetLastHurtBy = 96,
  McPacketId_BookEdit = 97,
  McPacketId_NPCRequest = 98,
  McPacketId_PhotoTransfer = 99,
  McPacketId_ShowModalForm = 100,
  McPacketId_ModalFormResponse = 101,
  McPacketId_ServerSettingsRequest = 102,
  McPacketId_ServerSettingsResponse = 103,
  McPacketId_ShowProfile = 104,
  McPacketId_SetDefaultGameType = 105,
  McPacketId_RemoveObjective = 106,
  McPacketId_SetDisplayObjective = 107,
  McPacketId_SetScore = 108,
  McPacketId_LabTable = 109,
  McPacketId_UpdateBlockSynced = 110,
  McPacketId_MoveDeltaActor = 111,
  McPacketId_SetScoreboardIdentity = 112,
  McPacketId_SetLocalPlayerAsInit = 113,
  McPacketId_UpdateSoftEnum = 114,
  McPacketId_Ping = 115,
  McPacketId_BlockPalette = 116,
  McPacketId_ScriptCustomEvent = 117,
  McPacketId_SpawnParticleEffect = 118,
  McPacketId_AvailableActorIDList = 119,
  McPacketId_LevelSoundEventV2 = 120,
  McPacketId_NetworkChunkPublisherUpdate = 121,
  McPacketId_BiomeDefinitionList = 122,
  McPacketId_LevelSoundEvent = 123,
  McPacketId_LevelEventGeneric = 124,
  McPacketId_LecternUpdate = 125,
  //McPacketId_VideoStreamConnect_DEPRECATED = 126,
  //McPacketId_AddEntity_DEPRECATED = 127,
  //McPacketId_RemoveEntity_DEPRECATED = 128,
  McPacketId_ClientCacheStatus = 129,
  McPacketId_OnScreenTextureAnimation = 130,
  McPacketId_MapCreateLockedCopy = 131,
  McPacketId_StructureTemplateDataExportRequest = 132,
  McPacketId_StructureTemplateDataExportResponse = 133,
  //McPacketId_UNUSED_PLS_USE_ME = 134,
  McPacketId_ClientCacheBlobStatus = 135,
  McPacketId_ClientCacheMissResponse = 136,
  McPacketId_EducationSettings = 137,
  McPacketId_Emote = 138,
  McPacketId_MultiplayerSettings = 139,
  McPacketId_SettingsCommand = 140,
  McPacketId_AnvilDamage = 141,
  McPacketId_CompletedUsingItem = 142,
  McPacketId_NetworkSettings = 143,
  McPacketId_PlayerAuthInput = 144,
  McPacketId_CreativeContent = 145,
  McPacketId_PlayerEnchantOptions = 146,
  McPacketId_ItemStackRequest = 147,
  McPacketId_ItemStackResponse = 148,
  McPacketId_PlayerArmorDamage = 149,
  McPacketId_CodeBuilder = 150,
  McPacketId_UpdatePlayerGameType = 151,
  McPacketId_EmoteList = 152,
  McPacketId_PositionTrackingDBServerBroadcast = 153,
  McPacketId_PositionTrackingDBClientRequest = 154,
  McPacketId_DebugInfo = 155,
  McPacketId_PacketViolationWarning = 156,
  McPacketId_MotionPredictionHints = 157,
  McPacketId_TriggerAnimation = 158,
  McPacketId_CameraShake = 159,
  McPacketId_PlayerFogSetting = 160,
  McPacketId_CorrectPlayerMovePrediction = 161,
  McPacketId_ItemComponent = 162,
  //McPacketId_FilterTextPacket_DEPRECATED = 163,
  McPacketId_ClientBoundDebugRenderer = 164,
  McPacketId_SyncActorProperty = 165,
  McPacketId_AddVolumeEntity = 166,
  McPacketId_RemoveVolumeEntity = 167,
  McPacketId_SimulationType = 168,
  McPacketId_NpcDialogue = 169,
  McPacketId_EduUriResource = 170,
  McPacketId_CreatePhoto = 171,
  McPacketId_UpdateSubChunkBlocks = 172,
  //McPacketId_PhotoInfoRequest_DEPRECATED = 173,
  McPacketId_SubChunk = 174,
  McPacketId_SubChunkRequest = 175,
  McPacketId_PlayerStartItemCooldown = 176,
  McPacketId_ScriptMessage = 177,
  McPacketId_CodeBuilderSource = 178,
  McPacketId_TickingAreasLoadStatus = 179,
  McPacketId_DimensionData = 180,
  McPacketId_AgentAction = 181,
  McPacketId_ChangeMobProperty = 182,
  McPacketId_LessonProgress = 183,
  McPacketId_RequestAbility = 184,
  McPacketId_RequestPermissions = 185,
  McPacketId_ToastRequest = 186,
  McPacketId_UpdateAbilities = 187,
  McPacketId_UpdateAdventureSettings = 188,
  McPacketId_DeathInfo = 189,
  McPacketId_EditorNetwork = 190,
  McPacketId_FeatureRegistry = 191,
  McPacketId_ServerStats = 192,
  McPacketId_RequestNetworkSettings = 193,
  McPacketId_GameTestRequest = 194,
  McPacketId_GameTestResults = 195,
  McPacketId_PlayerClientInputPermissions = 196,
  //McPacketId_ClientCheatAbilityPacket_Deprecated = 197,
  McPacketId_CameraPresets = 198,
  McPacketId_UnlockedRecipes = 199,
  McPacketId_CameraInstruction = 300,
  McPacketId_CompressedBiomeDefinitionList = 301,
  McPacketId_TrimData = 302,
  McPacketId_OpenSign = 303,
  McPacketId_AgentAnimation = 304,
  McPacketId_RefreshEntitlements = 305,
  McPacketId_PlayerToggleCrafterSlotRequest = 306,
  McPacketId_SetPlayerInventoryOptions = 307,
  McPacketId_SetHud = 308,
  McPacketId_AwardAchievement = 309,

  McPacketId_END = 310
};

// Data packet base class (0).
typedef struct Packet_ Packet;

// Create a packet object.
MCB_API_ATTR Packet *MCB_API mcbCreatePacket(
  McPacketId id);

// Free a packet object.
MCB_API_ATTR void MCB_API mcbDestroyPacket(
  Packet *packet);

// Text packet (9).
//
// Used for commands, messages, and other info printed to the screen. Most of
// which are server->client or server broadcasted to all clients.
typedef struct TextPacket_ TextPacket;

// Add player packet (12).
//
// A new player joins the game; the server sends this packet to the other
// players.
typedef struct AddPlayerPacket_ AddPlayerPacket;

// Command request packet (77).
//
// "slash" command execution, client to server.
typedef struct CommandRequestPacket_ CommandRequestPacket;

// Command output packet (79).
//
// "slash" command execution, server to client.
typedef struct CommandOutputPacket_ CommandOutputPacket;

// Send a packet to the server.
MCB_API_ATTR HTStatus MCB_API mcbPacketSendToServer(
  Packet *packet);

// Send a packet to all clients with internal server. Only avaliable when the
// mod's loaded by the host.
//
// Sending packets cross-thread is not allowed.
MCB_API_ATTR HTStatus MCB_API mcbPacketSendBroadcast(
  Packet *packet);

// Packet source.
typedef int McbPacketSource;
enum McbPacketSource_ {
  // The packet is created by the client.
  McbPacketSource_Client = 0,
  // The packet is created by the server.
  McbPacketSource_Server
};

// Packet filter result.
typedef int McbPacketFilterResult;
enum McbPacketFilterResult_ {
  // Pass to the next filter.
  McbPacketFilterResult_Passed = 0,
  // The packet is modified and accepted. Interrupt the filter chain and
  // pass it to the next stage.
  McbPacketFilterResult_Filtered,
  // The packet is blocked. Interrupt filter chain without passing packets.
  McbPacketFilterResult_Blocked
};

// Packet source.
typedef int McbPacketFilterType;
enum McbPacketFilterType_ {
  // Filtering incoming package.
  McbPacketFilterType_Incoming = 1 << 0,
  // Filtering outgoing package.
  McbPacketFilterType_Outgoing = 1 << 1
};

// Packet filter callback.
typedef McbPacketFilterResult (MCB_API *PFN_mcbPacketFilter)(
  Packet *, McbPacketFilterType, McbPacketSource);

// Register a packet filter (listener).
//
// Registering or deregistering callbacks in callback functions is not allowed.
//
// NOTE: hOwner is reserved for future features. Unregister your callback
// manually before the mod is being unloaded.
MCB_API_ATTR HTStatus MCB_API mcbPacketFilterRegister(
  HMODULE hOwner,
  McbPacketFilterType type,
  PFN_mcbPacketFilter filter);

// Unregister a packet filter (listener).
MCB_API_ATTR HTStatus MCB_API mcbPacketFilterUnregister(
  HMODULE hOwner,
  McbPacketFilterType type,
  PFN_mcbPacketFilter filter);

// ----------------------------------------------------------------------------
// [SECTION] SRC/GAME/TEXT_MESSAGE
// ----------------------------------------------------------------------------

// Send a chat message to the host, just like sending in the chat menu.
//
// Message must not longer than 65535 bytes length. Set maxLen to 0 to allow the
// function to determine the message length by itself.
//
// If the message contains '\0', be sure to set maxlen to the buffer length.
MCB_API_ATTR HTStatus MCB_API mcbSendChatMessage(
  LPCSTR message,
  UINT32 maxLen);

#ifdef __cplusplus
}
#endif

#endif
