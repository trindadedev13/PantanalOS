#ifndef __PANTANAL_STD_OPTIONAL_HPP__
#define __PANTANAL_STD_OPTIONAL_HPP__

#include "Pantanal/Std/String.hpp"

namespace Pantanal {
  namespace std {
    template <typename T>
    class Optional {
      private:
        bool hasValue_;
        T value_;

      public:
        Optional();
        Optional(const T& value);
        Optional(T&& value);

        bool hasValue() const;

        T& value();
        const T& value() const;

        void setValue(const T& value);
        void reset();

        explicit operator bool() const;

        Optional<T>& operator=(const T& val);
        Optional<T>& operator=(const Optional<T>& other);

        T& operator*();
        const T& operator*() const;

        T* operator->();
        const T* operator->() const;

        bool operator==(const Optional<T>& other) const;
        bool operator!=(const Optional<T>& other) const;
    };
  }
}

#include "Pantanal/Std/Optional.tpp"

#endif