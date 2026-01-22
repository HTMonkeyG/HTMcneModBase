// ----------------------------------------------------------------------------
// game/net/textMessage.cpp
//
// - Text message sender APIs.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

// ----------------------------------------------------------------------------
// [SECTION] MSG_SENDER_CLIENT
// ----------------------------------------------------------------------------

MCB_API_ATTR HTStatus MCB_API mcbSendChatMessage(
  LPCSTR message,
  UINT32 maxLen
) {
  if (!message || maxLen >= 0x10000)
    return HT_FAIL;

  TextPacket tp;

  tp.messageType = TextPacketType_Chat;

  if (!maxLen) {
    if (strlen(message) >= 0x10000)
      return HT_FAIL;

    tp.message = message;
  } else {
    tp.message.resize(maxLen + 1);
    memcpy(tp.message.data(), message, maxLen);
    tp.message.data()[maxLen] = 0;
  }

  return mcbPacketSendToServer(
    &tp);
}

MCB_API_ATTR HTStatus MCB_API mcbSendCommand(
  LPCSTR command,
  UINT32 maxLen,
  McUuid *uuid
) {
  if (!command || maxLen >= 0x10000)
    return HT_FAIL;

  CommandRequestPacket crp;
  McUuid id;

  if (!maxLen) {
    if (strlen(command) >= 0x10000)
      return HT_FAIL;

    crp.command = command;
  } else {
    crp.command.resize(maxLen + 1);
    memcpy(crp.command.data(), command, maxLen);
    crp.command.data()[maxLen] = 0;
  }

  if (!mcbiUuidGen(&id))
    return HT_FAIL;

  crp.version = 0x27;
  crp.commandOriginData.uuid = id;
  crp.commandOriginData.commandType = CommandOriginType_Player;

  if (uuid)
    *uuid = id;

  return mcbPacketSendToServer(
    &crp);
}
