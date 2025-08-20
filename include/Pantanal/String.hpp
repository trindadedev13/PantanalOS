#ifndef __PANTANAL_STRING_HPP__
#define __PANTANAL_STRING_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace std {
    class String {
      private:
        char* data;
        size_t length;
      public:
        String();
        ~String();
        String(const char*);
        String(const String&);
        String(int);
        String operator+(const String&) const;
        String& operator+=(char);
        String& operator=(const String&);
        String& operator=(const char*);
        char& operator[](size_t);
        const char& operator[](size_t) const;
        bool operator==(const String&) const;
        bool operator==(const char*) const;
  
        size_t size() const {
          return length;
        }

        const char* c_str() const {
          return data;
        }
    };

    /** to support concatenation of const char* + Pantanal String */
    String operator+(const char*, const String&);
  }
}


#endif