#include "Pantanal/Kernel/Kernel.hpp"

#include "Pantanal/types.h"
#include "Pantanal/Asm.hpp"
#include "Pantanal/Std/String.hpp"
#include "Pantanal/Kernel/Allocator/Allocator.hpp"
#include "Pantanal/Keyboard/Keyboard.hpp"
#include "Pantanal/Terminal/Terminal.hpp"
#include "Pantanal/Shell/Lang/Lexer.hpp"
#include "Pantanal/Shell/Lang/Parser.hpp"

namespace Pantanal {
  namespace Kernel {
    void panic(const std::String& msg) {
      Terminal::printf("KERNEL PANIC: ");
      Terminal::printf(msg);
      Asm::cli();
      Asm::hlt();
      while (1) Asm::hlt();
    }

    void reboot() {
      Asm::outb(Keyboard::STATUS_PORT, 0xFE);
    }
  }

  namespace Tests {
    void testPantScript() {
      // tokenize
      Shell::Lang::Lexer lexer(
        "def help()\n"
        "end\n"
        "help()"
      );
      auto tokens = lexer.lex();
      Terminal::println(std::String("Tokens: ") + tokens.size(), Graphics::Color::Blue);
      for (auto& token : tokens) {
        Terminal::println("Token Type: " + Shell::Lang::Token::typeToString(token.type) + " Token Value:" + token.value);
      }

      //parse
      Shell::Lang::Parser parser(tokens);
      auto nodes = parser.parse();
      Terminal::println(std::String("NODES: ") + nodes.size(), Graphics::Color::Yellow);
      for (auto& node : nodes) {
        Shell::Lang::printNode(node);
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
      Terminal::println(std::String(*a));
      delete a;
    }
  }
}

extern "C" void kernel_main() {

using namespace Pantanal;

  Terminal::println("  +-----------------------------------------------+");
  Terminal::println("  |              ::Pantanal OS::                  |");
  Terminal::println("  +-----------------------------------------------+");
  Terminal::println("  |         https://github.com/PantanalBR/        |");
  Terminal::println("  +-----------------------------------------------+");
  Terminal::println("  |            PRESS [ENTER] TO REBOOT            |");
  Terminal::println("  +-----------------------------------------------+");

  /**
   * Call Tests
   * Should be removed soon
   */
  Tests::testAllocator();
  Tests::testPantScript();

  while (1){
    uint8_t scancode = Terminal::readKeyScancode();
    if (scancode == Scancode::ENTER) {
      Terminal::printf("\nRestarting...\n");
      Kernel::reboot();
    }
  }
}

extern "C" void init_cpp() {
  for (auto **ctor = __init_array_start; ctor != __init_array_end; ++ctor) {
    (*ctor)();
  }
}