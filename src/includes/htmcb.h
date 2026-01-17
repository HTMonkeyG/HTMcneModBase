// ----------------------------------------------------------------------------
// HTSkyModBase
// - A Simple mod developed for exporting in-game funtions of Sky: CotL.
// <https://www.github.com/HTMonkeyG/HTSkyModBase>
//
// MIT License
//
// Copyright (c) 2025 HTMonkeyG
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

// ----------------------------------------------------------------------------
// [SECTION] GAME/NET/PACKET
// ----------------------------------------------------------------------------

// Data packet base class.
typedef struct Packet_ Packet;

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

// Packet filter callback.
typedef McbPacketFilterResult (MCB_API *PFN_mcbPacketFilter)(
  Packet *, McbPacketSource);

// Packet source.
typedef int McbPacketFilterType;
enum McbPacketFilterType_ {
  // Filtering incoming package.
  McbPacketFilterType_Incoming = 1 << 0,
  // Filtering outgoing package.
  McbPacketFilterType_Outgoing = 1 << 1
};

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

typedef struct TextPacket_ TextPacket;

#ifdef __cplusplus
}
#endif

#endif
