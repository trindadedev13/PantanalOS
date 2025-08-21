#ifndef __PANTANAL_TERMINAL_HPP__
#define __PANTANAL_TERMINAL_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Std/String.hpp"
#include "Pantanal/Graphics/Graphics.hpp"

namespace Pantanal {
  namespace Terminal {
    static size_t cursorX = 0;
    static size_t cursorY = 0;

    void moveCursor(size_t, size_t);
    void advanceCursor();
    void clearScreen();
    void newLine();
    uint8_t readKeyScancode();

    void putChar(char, uint8_t);
    void printf(const std::String&, uint8_t);

    inline void printf(const std::String& str) {
      printf(str, Graphics::Color::White);
    }

    inline void println(const std::String& str, uint8_t color) {
      printf(str, color);
      printf("\n");
    }

    inline void println(const std::String& str) {
      println(str, Graphics::Color::White);
    }
  }
}

#endif