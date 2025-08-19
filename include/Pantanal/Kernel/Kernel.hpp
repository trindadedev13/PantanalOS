#ifndef __PANTANAL_KERNEL_HPP__
#define __PANTANAL_KERNEL_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Kernel/Allocator/Allocator.hpp"
#include "Pantanal/Terminal/Terminal.hpp"

namespace Pantanal {
  namespace Kernel {
    static Terminal terminal;
    static Allocator::Allocator allocator;

    void panic(const char*);
    void reboot();
  }
}

extern void (*__init_array_start [])();
extern void (*__init_array_end   [])();

extern "C" void init_cpp();

#endif