#ifndef __PANTANAL_ALLOCATOR_HPP__
#define __PANTANAL_ALLOCATOR_HPP__

#include "Pantanal/types.h"

//#define KERNEL_HEAP_START ((uint32_t)&__kernel_end)
#define KERNEL_HEAP_START 0x0000000
#define KERNEL_HEAP_SIZE  0x1000000  // 16 MB

extern "C" char __kernel_end;

namespace Pantanal {
  namespace Kernel {
    namespace Allocator {
      struct Block {
        Block* next;
        size_t size;
        bool free;
      };

      struct Allocator {
        Block* freeList;

        Allocator();
        void* alloc(size_t);
        void free(void*);
        void* realloc(void*, size_t);
      };

    }
  }
}

#endif