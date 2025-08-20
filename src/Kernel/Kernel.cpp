#include "Pantanal/Kernel/Kernel.hpp"

#include "Pantanal/types.h"
#include "Pantanal/Asm.hpp"
#include "Pantanal/String.hpp"
#include "Pantanal/Kernel/Allocator/Allocator.hpp"
#include "Pantanal/Keyboard/Keyboard.hpp"
#include "Pantanal/Terminal/Terminal.hpp"
#include "Pantanal/Shell/Lang/Lexer.hpp"

namespace Pantanal {
  namespace Kernel {
    void panic(const std::String& msg) {
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

  /**
   * function just to test the allocation
   * should be remove later
   */
  void testAllocator() {
    /** 
     * allocates a new int, set it pointer value to 42
     * if it succefully allocated
     * so 42 should appear in screen
     */
    int* a = new int;
    *a = 42;
    Kernel::terminal.println(std::String(*a));
    delete a;
  }
}

extern "C" void kernel_main() {
  Pantanal::Kernel::terminal.println("  +-----------------------------------------------+");
  Pantanal::Kernel::terminal.println("  |              ::Pantanal OS::                  |");
  Pantanal::Kernel::terminal.println("  +-----------------------------------------------+");
  Pantanal::Kernel::terminal.println("  |         https://github.com/PantanalBR/        |");
  Pantanal::Kernel::terminal.println("  +-----------------------------------------------+");
  Pantanal::Kernel::terminal.println("  |            PRESS [ENTER] TO REBOOT            |");
  Pantanal::Kernel::terminal.println("  +-----------------------------------------------+");

  volatile uint32_t* test = (uint32_t*)KERNEL_HEAP_START;
  *test = 0xDEADBEEF;
  if (*test != 0xDEADBEEF) {
    Pantanal::Kernel::panic("heapStart não mapeado!");
  }

  /** just to test allocation */
  Pantanal::testAllocator();

  Pantanal::Shell::Lang::Lexer lexer(
    "def help()\n"
    "end\n"
    "help()"
  );
  auto tokens = lexer.lex();
  for (auto token : tokens) {
    Pantanal::Kernel::terminal.println("Token Value: " + token.value);
  }

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