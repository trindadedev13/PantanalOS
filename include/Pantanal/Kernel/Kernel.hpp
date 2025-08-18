#ifndef __PANTANAL_KERNEL_HPP__
#define __PANTANAL_KERNEL_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Kernel/multiboot.h"
#include "Pantanal/Terminal/Terminal.hpp"

namespace Pantanal {
  struct Kernel {
    public:
      Terminal terminal;

      Kernel();
      void panic(const char*);
      void reboot();
  };
}

extern void (*__init_array_start [])();
extern void (*__init_array_end   [])();

extern "C" void init_cpp();

#endif