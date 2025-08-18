#ifndef __PANTANAL_TERMINAL_HPP__
#define __PANTANAL_TERMINAL_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Graphics/Graphics.hpp"

namespace Pantanal {
  class Terminal {
    private:
      size_t cursorX;
      size_t cursorY;

    public:
      Terminal();
      void moveCursor(size_t, size_t);
      void advanceCursor();
      void clearScreen();
      void newLine();
      uint8_t readKeyScancode();

      void putChar(char, uint8_t);
      void printf(const char*, uint8_t);

      inline void printf(const char* str) {
        printf(str, Graphics::Color::White);
      }
  };
}

#endif