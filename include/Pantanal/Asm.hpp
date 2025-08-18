#ifndef __PANTANAL_ASM_HPP__
#define __PANTANAL_ASM_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace Asm {
    static inline uint8_t inb(uint16_t port) {
      uint8_t res;
      asm volatile(
        "inb %1, %0"
        : "=a"(res)
        : "Nd"(port)
      );
      return res;
    }

    static inline void outb(uint16_t port, uint8_t value) {
      asm volatile(
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
      );
    }

    static inline void cli() { asm volatile("cli"); }

    static inline void hlt() { asm volatile("hlt"); }
  }
}

#endif