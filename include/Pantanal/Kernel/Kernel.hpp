#ifndef __PANTANAL_KERNEL_HPP__
#define __PANTANAL_KERNEL_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Std/String.hpp"
#include "Pantanal/Kernel/Allocator/Allocator.hpp"

namespace Pantanal {
  namespace Kernel {
    static Allocator::Allocator allocator;

    void panic(const std::String&);
    void reboot();
  }
}

extern void (*__init_array_start [])();
extern void (*__init_array_end   [])();

extern "C" void init_cpp();

#endif