namespace Pantanal {
  namespace std {
    template <typename T>
    Vec<T>::Vec(): data(nullptr), capacity(0), len(0) { }

    template <typename T>
    Vec<T>::~Vec() {
      delete[] data;
    }

    template <typename T>
    void Vec<T>::resize(size_t newCapacity) {
      T* newData = new T[newCapacity];
      for (size_t i = 0; i < len; ++i)
        newData[i] = data[i];

      delete[] data;
      data = newData;
      capacity = newCapacity;
    }

    template <typename T>
    void Vec<T>::push(const T& value) {
      if (len == capacity) {
        size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
        resize(newCapacity);
      }
      data[len++] = value;
    }

    template <typename T>
    T& Vec<T>::operator[](size_t idx) const {
      return data[idx];
    }
  }
}