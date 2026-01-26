// ----------------------------------------------------------------------------
// custom/example.cpp
// ----------------------------------------------------------------------------

#include "mcb_internal.hpp"

#if 0

static HTStatus fnInit_McbTestExample(
  HMODULE, const McbiModInitializer *);

/* Struct declarations. */

static McbiModInitializer gInit_McbTestExample{
  fnInit_McbTestExample,
  "McbTestExample"
};

/* Functions. */

static HTStatus fnInit_McbTestExample(
  HMODULE hModuleDll,
  const McbiModInitializer *self
) {
  (void)hModuleDll;
  (void)self;

  HTTellText("aaa");

  return HT_SUCCESS;
}

#endif
