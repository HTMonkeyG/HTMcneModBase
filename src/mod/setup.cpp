// ----------------------------------------------------------------------------
// mod/setup.cpp
//
// - Mod initializer.
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

HTStatus McbiModInitializer::setupAll(
  HMODULE hModuleDll
) {
  HTStatus s = HT_SUCCESS;

  for (
    const McbiModInitializer *p = McbiModInitializer::list();
    p;
    p = p->getPrev()
  ) {
    HTStatus r = (*p)(hModuleDll);

    if (!r) {
      mcbLogE("Failed to initialize %s", p->getName());
      s = HT_FAIL;
    }
  }

  return s;
}
