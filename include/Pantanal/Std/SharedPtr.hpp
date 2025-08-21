#ifndef __PANTANAL_STD_SHARED_PTR_HPP__
#define __PANTANAL_STD_SHARED_PTR_HPP__

#include "Pantanal/types.h"

namespace Pantanal {
  namespace std {
    template <typename T>
    class SharedPtr {
      public:
        explicit SharedPtr(T* p = nullptr);
        SharedPtr(const SharedPtr&);
        SharedPtr(SharedPtr&&) noexcept;
        SharedPtr& operator=(const SharedPtr&);
        SharedPtr& operator=(SharedPtr&&) noexcept;
        ~SharedPtr();

        T* operator->() { return ptr; }
        T* operator->() const { return ptr; }

        T& operator*() { return *ptr; }
        T& operator*() const { return *ptr; }

        T* get() const { return ptr; }

        bool valid() const {
          return ptr != nullptr;
        }
      private:
        T* ptr = nullptr;
        size_t* refCount = nullptr;

        void release();
    };
  }
}

#include "Pantanal/Std/SharedPtr.tpp"

#endif