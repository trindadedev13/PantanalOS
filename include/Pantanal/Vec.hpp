#ifndef __PANTANAL_VEC_HPP__
#define __PANTANAL_VEC_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace std {
    template <typename T>
    class Vec {
      private:
        T* data;
        size_t capacity;
        size_t len;

        void resize(size_t);
      public:
        Vec();
        ~Vec();

        void push(const T&);
        T& operator[](size_t) const;

        const T* begin() const { return data; }
        const T* end() const { return data + len; }

        size_t size() const {
          return len;
        }
    };
  }
}

/** implementation of vec */
#include "Pantanal/Vec.tpp"

#endif