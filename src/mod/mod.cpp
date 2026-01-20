#include "imgui.h"

#include "mcb_internal.hpp"
#include "includes/htmod.h"

DWORD gMainThreadId = 0;
bool gGuiReady = false;

__declspec(dllexport) HTStatus HTMLAPI HTModOnInit(
  void *reserved
) {
  QueryPerformanceFrequency(
    &gPerfFreq);

  McbiModInitializer::setupAll(hModuleDll);

  // Save the main thread.
  gMainThreadId = GetCurrentThreadId();
  HTTellText("[htmcb] gMainThreadId = ", gMainThreadId);

  return HT_SUCCESS;
}

__declspec(dllexport) HTStatus HTMLAPI HTModOnEnable(
  void *reserved
) {
  HTImGuiContexts guiContext;

  HTImGuiDispatch(
    &guiContext);

  ImGui::SetAllocatorFunctions(
    (ImGuiMemAllocFunc)guiContext.pImAllocatorAllocFunc,
    (ImGuiMemFreeFunc)guiContext.pImAllocatorFreeFunc,
    guiContext.pImAllocatorUserData);

  ImGui::SetCurrentContext(
    (ImGuiContext *)guiContext.pImGui);

  gGuiReady = true;

  return HT_SUCCESS;
}

__declspec(dllexport) void HTMLAPI HTModRenderGui(
  float timeElapesed,
  void *reserved
) {
  // No GUI.
  ;
}
