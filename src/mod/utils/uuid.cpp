#include "mcb_internal.hpp"

#pragma comment(lib, "rpcrt4.lib")

HTStatus mcbiUuidGen(
  McUuid *uuid
) {
  UUID id;
  RPC_STATUS status;

  if (!uuid)
    return HT_FAIL;

  status = UuidCreate(
    &id);
    
  if (status != RPC_S_OK && status != RPC_S_UUID_LOCAL_ONLY)
    return HT_FAIL;
    
  memcpy((void *)uuid, (void *)&id, sizeof(McUuid));

  return HT_SUCCESS;
}
