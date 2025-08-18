#ifndef __PANTANAL_KEYBOARD_HPP__
#define __PANTANAL_KEYBOARD_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace Keyboard {
    const int DATA_PORT = 0x60;
    const int STATUS_PORT = 0x64;
  }

  namespace Scancode {
    const uint8_t ENTER = 0x1C;
  }
}

#endif