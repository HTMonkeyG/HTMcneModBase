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
    if (!(*p)(hModuleDll))
      s = HT_FAIL;
  }

  return s;
}
