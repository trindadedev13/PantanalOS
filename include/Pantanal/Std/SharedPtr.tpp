namespace Pantanal {
  namespace std {
    // constructor
    template <typename T>
    SharedPtr<T>::SharedPtr(T* p) : ptr(p), refCount(nullptr) {
      if (p) refCount = new size_t(1);
    }

    // copy constructor
    template <typename T>
    SharedPtr<T>::SharedPtr(const SharedPtr& other): ptr(other.ptr), refCount(other.refCount) {
      if (refCount) (*refCount)++;
    }

    // move constructor
    template <typename T>
    SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
      other.ptr = nullptr;
      other.refCount = nullptr;
    }

    template <typename T>
    SharedPtr<T>::~SharedPtr() {
      release();
    }

    template <typename T>
    SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
      if (this != &other) {
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        if (refCount) (*refCount)++;
      }
      return *this;
    }

    template <typename T>
    SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
      if (this != &other) {
        release();
        ptr = other.ptr;
        refCount = other.refCount;
        other.ptr = nullptr;
        other.refCount = nullptr;
      }
      return *this;
    }

    template <typename T>
    void SharedPtr<T>::release() {
      if (refCount) {
        (*refCount)--;
        if (*refCount == 0) {
          delete ptr;
          delete refCount;
        }
      }
    }

    template <typename T, typename... Args>
    SharedPtr<T> makeShared(Args... args) {
      return SharedPtr<T>(new T(args...));
    }
  }
}