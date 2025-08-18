#include "Pantanal/Graphics/Graphics.hpp"

#include "Pantanal/types.h"
#include "Pantanal/Graphics/Font.hpp"

namespace Pantanal {
  namespace Graphics {
    void setPixel(size_t x, size_t y, uint8_t color) {
      uint8_t* fb = VESA::getFramebuffer();
      fb[y * VESA::WIDTH + x] = color;
    }

    uint8_t getPixel(size_t x, size_t y) {
      uint8_t* fb = VESA::getFramebuffer();
      return fb[y * VESA::WIDTH + x];
    }

    void clearScreen() {
      for (size_t y = 0; y < VESA::HEIGHT; ++y) {
        for (size_t x = 0; x < VESA::WIDTH; ++x) {
          setPixel(x, y, 0x00);
        }
      }
    }

    void drawRect(size_t x, size_t y, size_t w, size_t h, uint8_t color) {
      for (size_t rectY = 0; rectY < y + h; ++rectY) {
        for (size_t rectX = 0; rectX < x + w; ++rectX) {
          setPixel(rectX, rectY, color);
        }
      }
    }

    void drawChar(size_t x, size_t y, uint8_t* bitmap, uint8_t color) {
      for (size_t chY = 0; chY < FONT_HEIGHT; chY++) {
        for (size_t chX = 0; chX < FONT_WIDTH; chX++) {
          if (bitmap[chY] & (1 << (FONT_WIDTH - 1 - chX))) {
            setPixel(x + chX, y + chY, color);
          }
        }
      }
    }

    void drawString(size_t x, size_t y, const char* str, uint8_t color) {
      size_t fontX = x;
      for (size_t i = 0; str[i] != '\0'; ++i) {
        uint8_t* bitmap = isoFont + (str[i] * FONT_HEIGHT);
        drawChar(fontX, y, bitmap, color);
        fontX += FONT_WIDTH;
      }
    }
  }
}