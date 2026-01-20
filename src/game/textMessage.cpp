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

  tp.messageType = TextPacketMessageType_Chat;

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
  UINT32 maxLen
) {
  return HT_FAIL;
}
