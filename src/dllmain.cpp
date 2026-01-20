#include <windows.h>

HMODULE hModuleDll = NULL;
LARGE_INTEGER gPerfFreq = {0};

BOOL APIENTRY DllMain(
  HMODULE hModule,
  DWORD dwReason,
  LPVOID lpReserved
) {
  if (dwReason == DLL_PROCESS_ATTACH)
    hModuleDll = hModule;
  return TRUE;
}
