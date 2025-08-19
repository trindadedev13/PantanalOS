#ifndef __PANTANAL_STRING_HPP__
#define __PANTANAL_STRING_HPP__

namespace Pantanal {
  namespace String {
    static const char* fromInt(int value) {
      static char buf[20];
      char* p = buf + sizeof(buf) - 1;
      *p = '\0';
      bool negative = false;
      if (value < 0) {
        negative = true,
        value = -value;
      }
      do {
        *--p = '0' + (value % 10);
        value /= 10;
      } while (value > 0);
      if (negative) {
        *--p = '-';
      }
      return p;
    }
  }
}

#endif