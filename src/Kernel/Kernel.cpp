#include "Pantanal/Kernel/Kernel.hpp"

#include "Pantanal/types.h"
#include "Pantanal/Asm.hpp"
#include "Pantanal/String.hpp"
#include "Pantanal/Kernel/Allocator/Allocator.hpp"
#include "Pantanal/Keyboard/Keyboard.hpp"
#include "Pantanal/Terminal/Terminal.hpp"

namespace Pantanal {
  namespace Kernel {
    void panic(const char* msg) {
      terminal.printf("KERNEL PANIC: ");
      terminal.printf(msg);
      Asm::cli();
      Asm::hlt();
      while (1) Asm::hlt();
    }

    void reboot() {
      Asm::outb(Keyboard::STATUS_PORT, 0xFE);
    }
  }

  void testAllocator() {
    int* a = new int;
    *a = 42;
    Kernel::terminal.printf(String::fromInt(*a));
    delete a;
  }
}

extern "C" void kernel_main() {
  Pantanal::Kernel::terminal.printf("  +-----------------------------------------------+\n");
  Pantanal::Kernel::terminal.printf("  |              ::Pantanal OS::                  |\n");
  Pantanal::Kernel::terminal.printf("  +-----------------------------------------------+\n");
  Pantanal::Kernel::terminal.printf("  |         https://github.com/PantanalBR/        |\n");
  Pantanal::Kernel::terminal.printf("  +-----------------------------------------------+\n");
  Pantanal::Kernel::terminal.printf("  |            PRESS [ENTER] TO REBOOT            |\n");
  Pantanal::Kernel::terminal.printf("  +-----------------------------------------------+\n");

  volatile uint32_t* test = (uint32_t*)KERNEL_HEAP_START;
  *test = 0xDEADBEEF;
  if (*test != 0xDEADBEEF) {
    Pantanal::Kernel::panic("heapStart não mapeado!");
  }

  Pantanal::testAllocator();

  while (1){
    uint8_t scancode = Pantanal::Kernel::terminal.readKeyScancode();
    if (scancode == Pantanal::Scancode::ENTER) {
      Pantanal::Kernel::terminal.printf("\nRestarting...\n");
      Pantanal::Kernel::reboot();
    }
  }
}

extern "C" void init_cpp() {
  for (auto **ctor = __init_array_start; ctor != __init_array_end; ++ctor) {
    (*ctor)();
  }
}