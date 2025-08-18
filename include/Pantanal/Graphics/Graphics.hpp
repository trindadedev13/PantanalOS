#ifndef __PANTANAL_GRAPHICS_HPP__
#define __PANTANAL_GRAPHICS_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace Graphics {
    namespace VESA {
      const int WIDTH = 800;
      const int HEIGHT = 600;
      const int MEMORY = 0xFD000000;

      static inline uint8_t* getFramebuffer() {
        return (uint8_t*) MEMORY;
      }
    }

    namespace Color {
      enum Color {
        Black       = 0x00,
        DarkBlue    = 0x01,
        DarkGreen   = 0x02,
        DarkCyan    = 0x03,
        DarkRed     = 0x04,
        DarkMagenta = 0x05,
        Brown       = 0x06,
        LightGray   = 0x07,
        DarkGray    = 0x08,
        Blue        = 0x09,
        Green       = 0x0A,
        Cyan        = 0x0B,
        Red         = 0x0C,
        Magenta     = 0x0D,
        Yellow      = 0x0E,
        White       = 0x0F
      };
    }

    void setPixel(size_t, size_t, uint8_t);
    uint8_t getPixel(size_t, size_t);
    void clearScreen();

    void drawChar(size_t, size_t, uint8_t*, uint8_t);
    void drawString(size_t, size_t, const char*, uint8_t);
    void drawRect(size_t, size_t, size_t, size_t, uint8_t);
  }
}

#endif