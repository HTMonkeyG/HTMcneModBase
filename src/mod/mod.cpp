#include "mcb_internal.hpp"
#include "includes/htmod.h"

DWORD gMainThreadId = 0;

__declspec(dllexport) HTStatus HTMLAPI HTModOnInit(
  void *reserved
) {
  McbiModInitializer::setupAll(hModuleDll);

  // Save the main thread.
  gMainThreadId = GetCurrentThreadId();
  HTTellText("[htmcb] gMainThreadId = ", gMainThreadId);

  return HT_SUCCESS;
}

__declspec(dllexport) HTStatus HTMLAPI HTModOnEnable(
  void *reserved
) {
  return HT_SUCCESS;
}

__declspec(dllexport) void HTMLAPI HTModRenderGui(
  float timeElapesed,
  void *reserved
) {
  // No GUI.
  ;
}
