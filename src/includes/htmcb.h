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

// Events.
// Fired every cycle of the main thread's message loop.
#define mcbEventMainLoop mcbMakeNamespace("mainLoop")
// Fired when received a chat message.
#define mcbEventOnChatMessage mcbMakeNamespace("onChatMessage")
// Fired when received the return value of a sent command.
#define mcbEventOnCommandOutput mcbMakeNamespace("onCommandOutput")

// ----------------------------------------------------------------------------
// [SECTION] GAME
// ----------------------------------------------------------------------------

typedef union {
  struct {
    UINT64 msb;
    UINT64 lsb;
  };
  char bytes[16];
} McUuid;

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

// Bedrock Protocol types.
#include "htmcb_protocol.h"

// Create a packet object.
MCB_API_ATTR Packet *MCB_API mcbCreatePacket(
  McPacketId id);

// Free a packet object.
MCB_API_ATTR void MCB_API mcbDestroyPacket(
  Packet *packet);

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

// Send a command host, just like sending in the chat menu.
//
// The command request's uuid will be saved in `uuid`.
MCB_API_ATTR HTStatus MCB_API mcbSendCommand(
  LPCSTR message,
  UINT32 maxLen,
  McUuid *uuid);

#ifdef __cplusplus
}
#endif

#endif
