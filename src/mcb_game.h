// ----------------------------------------------------------------------------
// mcb_game.hpp
//
// - Type definitions for in-game types.
// ----------------------------------------------------------------------------

#ifndef __MCB_GAME_H__
#define __MCB_GAME_H__

#include "mcb_internal.hpp"

struct ItemDescriptor {
  ItemDescriptor() = default;

  virtual ~ItemDescriptor() = default;

  // From binary.
  virtual void serialize(void *) { };

  // From JSON.
  virtual void serialize(void **) { };

  // A function.
  void *unk_1;

  void *unk_2;
};

struct ItemDescriptorCount: ItemDescriptor {
  ItemDescriptorCount() = default;

  u16 getStackSize() {
    return stackSize;
  }

  // Item stack size.
  u16 stackSize;
};

// #ifndef __MCB_GAME_H__
#endif
