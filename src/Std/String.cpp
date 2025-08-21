#include "Pantanal/cstr.h"
#include "Pantanal/Std/String.hpp"

namespace Pantanal {
  namespace std {
    String::String() {
      length = 0;
      data = new char[1];
      data[0] = '\0';
    }
  
    String::String(const char* str) {
      length = 0;
      while (str[length] != '\0') length++;
      data = new char[length + 1];
      for (size_t i = 0; i < length; i++)
          data[i] = str[i];
      data[length] = '\0';
    }
  
    String::String(const String& other) {
      length = other.length;
      data = new char[length + 1];
      for (size_t i = 0; i < length; i++)
          data[i] = other.data[i];
      data[length] = '\0';
    }
  
    String::String(int value) {
      static char buf[20];
      char* p = buf + sizeof(buf) - 1;
      *p = '\0';
      bool negative = false;
      if (value < 0) {
          negative = true;
          value = -value;
      }
      do {
          *--p = '0' + (value % 10);
          value /= 10;
      } while (value > 0);
      if (negative) {
          *--p = '-';
      }
      length = 0;
      while (p[length] != '\0') length++;
      data = new char[length + 1];
      for (size_t i = 0; i < length; i++)
          data[i] = p[i];
      data[length] = '\0';
    }
  
    String::~String() {
      delete[] data;
    }
  
    String& String::operator=(const String& other) {
      if (this == &other) return *this;
      delete[] data;
      length = other.length;
      data = new char[length + 1];
      for (size_t i = 0; i < length; i++)
          data[i] = other.data[i];
      data[length] = '\0';
      return *this;
    }
  
    String String::operator+(const String& other) const {
      String result;
      delete[] result.data;
      result.length = length + other.length;
      result.data = new char[result.length + 1];
  
      for (size_t i = 0; i < length; i++)
          result.data[i] = data[i];
      for (size_t i = 0; i < other.length; i++)
          result.data[length + i] = other.data[i];
  
      result.data[result.length] = '\0';
      return result;
    }

    String& String::operator+=(char other) {
      // original str + char + null-terminate
      char* newData = new char[length + 2];
      for (size_t i = 0; i < length; ++i)
        newData[i] = data[i];

      // concatenate other and null terminate
      newData[length] = other;
      newData[length + 1] = '\0';

      // update data
      delete[] data;
      data = newData;
      ++length;
      return *this;
    }

    char& String::operator[](size_t index) {
      return data[index];
    }
  
    const char& String::operator[](size_t index) const {
      return data[index];
    }
  
    String& String::operator=(const char* str) {
      delete[] data;
      length = 0;
      while (str[length] != '\0') length++;
      data = new char[length + 1];
      for (size_t i = 0; i < length; i++)
          data[i] = str[i];
      data[length] = '\0';
      return *this;
    }

    bool String::operator==(const String& other) const {
      return str_cmp(data, other.data) == 0;
    }

    bool String::operator==(const char* other) const {
      return str_cmp(data, other) == 0;
    }

    String String::operator+(int other) {
      String rhs(other);
      return *this + rhs;
    }

    String operator+(const char* lhs, const String& rhs) {
      return String(lhs) + rhs;
    }

    String operator+(int lhs, const String& rhs) {
      return String(lhs) + rhs;
    }
  }
}