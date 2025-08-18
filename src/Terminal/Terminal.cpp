#include "Pantanal/Terminal/Terminal.hpp"

#include "Pantanal/Asm.hpp"
#include "Pantanal/Keyboard/Keyboard.hpp"
#include "Pantanal/Graphics/Font.hpp"
#include "Pantanal/Graphics/Graphics.hpp"

namespace Pantanal {

  Terminal::Terminal() : cursorX(0), cursorY(0) {}

  void Terminal::moveCursor(size_t x, size_t y) {
    cursorX = x;
    cursorY = y;
  }

  void Terminal::advanceCursor() {
    cursorX += FONT_WIDTH;
    if (cursorX + FONT_WIDTH > Graphics::VESA::WIDTH) {
      cursorX = 0;
      cursorY += FONT_HEIGHT;
      if (cursorY + FONT_HEIGHT > Graphics::VESA::HEIGHT) {
        cursorY = 0; // todo: scroll
      }
    }
  }

  void Terminal::newLine() {
    cursorX = 0;
    cursorY += FONT_HEIGHT;
    if (cursorY + FONT_HEIGHT > Graphics::VESA::HEIGHT) {
      cursorY = 0; // todo: scroll
    }
  }

  void Terminal::putChar(char ch, uint8_t color) {
    if (ch == '\n') {
      newLine();
      return;
    }
    uint8_t* bitmap = Graphics::isoFont + (ch * FONT_HEIGHT);
    Graphics::drawChar(cursorX, cursorY, bitmap, color);
    advanceCursor();
  }

  void Terminal::clearScreen() {
    Graphics::clearScreen();
    moveCursor(0, 0);
  }

  void Terminal::printf(const char* str, uint8_t color) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
      putChar(str[i], color);
    }
  }

  uint8_t Terminal::readKeyScancode() {
    uint8_t scancode;
    while ((Asm::inb(Keyboard::STATUS_PORT) & 0x01) == 0);
    scancode = Asm::inb(Keyboard::DATA_PORT);
    return scancode;
  }
}