#include "Pantanal/Kernel/Kernel.hpp"

#include "Pantanal/types.h"
#include "Pantanal/Asm.hpp"
#include "Pantanal/Kernel/multiboot.h"
#include "Pantanal/Keyboard/Keyboard.hpp"
#include "Pantanal/Terminal/Terminal.hpp"

namespace Pantanal {
  Kernel::Kernel() { }

  void Kernel::panic(const char* msg) {
    terminal.printf("KERNEL PANIC: ");
    terminal.printf(msg);
    Asm::cli();
    Asm::hlt();
    while (1) Asm::hlt();
  }

  void Kernel::reboot() {
    Asm::outb(Keyboard::STATUS_PORT, 0xFE);
  }
}

extern "C" void kernel_main() {
  Pantanal::Kernel kernel;

  kernel.terminal.printf("  +-----------------------------------------------+\n");
  kernel.terminal.printf("  |              ::Pantanal OS::                  |\n");
  kernel.terminal.printf("  +-----------------------------------------------+\n");
  kernel.terminal.printf("  |         https://github.com/PantanalBR/        |\n");
  kernel.terminal.printf("  +-----------------------------------------------+\n");
  kernel.terminal.printf("  |            PRESS [ENTER] TO REBOOT            |\n");
  kernel.terminal.printf("  +-----------------------------------------------+\n");

  while (1){
    uint8_t scancode = kernel.terminal.readKeyScancode();
    if (scancode == Pantanal::Scancode::ENTER) {
      kernel.terminal.printf("\nRestarting...\n");
      kernel.reboot();
    }
  }
}

extern "C" void init_cpp() {
  for (auto **ctor = __init_array_start; ctor != __init_array_end; ++ctor) {
    (*ctor)();
  }
}