#include "Pantanal/Kernel/Allocator/Allocator.hpp"

#include "Pantanal/types.h"

#include "Pantanal/Kernel/Kernel.hpp"

/** override C++ new & delete operators */

void* operator new(size_t size) {
  void* ptr = Pantanal::Kernel::allocator.alloc(size);
  if (!ptr) {
    Pantanal::Kernel::panic("Failed to allocate $bytes");
  }
  return ptr;
}

void* operator new[](size_t size) {
  return operator new(size);
}

void operator delete(void* ptr) noexcept {
  Pantanal::Kernel::allocator.free(ptr);
}

void operator delete(void* ptr, size_t size) {
  operator delete(ptr);
}

void operator delete[](void* ptr) {
  operator delete(ptr);
}

void operator delete[](void* ptr, size_t size) {
  operator delete(ptr);
}

namespace Pantanal {
  namespace Kernel {
    namespace Allocator {
      static uint8_t* heapStart = (uint8_t*)KERNEL_HEAP_START;

      Allocator::Allocator() {
        freeList = (Block*)heapStart;
        freeList->size = KERNEL_HEAP_SIZE - sizeof(Block);
        freeList->next = 0;
        freeList->free = true;
      }

      static size_t align(size_t size, size_t alignment = 8) {
        size_t rem = size % alignment;
        if (rem == 0) return size;
        return size + (alignment - rem);
      }

      void* Allocator::alloc(size_t size) {
        size = align(size);

        Block* curr = freeList;
        while (curr) {
          if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(Block)) {
              Block* next = (Block*)((uint8_t*)(curr + 1) + size);
              next->size = curr->size - size - sizeof(Block);
              next->next = curr->next;
              next->free = true;

              curr->next = next;
              curr->size = size;
            }

            curr->free = false;
            return (void*)(curr + 1);
          }
          curr = curr->next;
        }
        return 0; // oom
      }

      void Allocator::free(void* ptr) {
        if (!ptr) return;

        Block* block = (Block*)ptr - 1;
        block->free = true;

        // optional: coalesce with next block
        Block* next = block->next;
        if (next && next->free) {
          block->size += sizeof(Block) + next->size;
           block->next = next->next;
        }
      }

      void* Allocator::realloc(void* ptr, size_t size) {
        if (!ptr) return alloc(size);

        Block* block = (Block*)ptr - 1;
        if (block->size >= size) return ptr;

        void* newPtr = alloc(size);
        if (!newPtr) return 0;

        // copy bytes
        size_t i;
        for (i = 0; i < block->size; ++i) {
          ((uint8_t*)newPtr)[i] = ((uint8_t*)ptr)[i];
        }
        free(ptr);
        return newPtr;
      }
    }
  }
}