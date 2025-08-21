namespace Pantanal {
  namespace std {
    template <typename T>
    Optional<T>::Optional() : hasValue_(false) {}

    template <typename T>
    Optional<T>::Optional(const T& value) : hasValue_(true), value_(value) {}

    template <typename T>
    Optional<T>::Optional(T&& value) : hasValue_(true), value_(static_cast<T&&>(value)) {}

    template <typename T>
    bool Optional<T>::hasValue() const { return hasValue_; }

    template <typename T>
    T& Optional<T>::value() { return value_; }

    template <typename T>
    const T& Optional<T>::value() const { return value_; }

    template <typename T>
    void Optional<T>::setValue(const T& value) {
      value_ = value;
      hasValue_ = true;
    }

    template <typename T>
    void Optional<T>::reset() { hasValue_ = false; }

    template <typename T>
    Optional<T>::operator bool() const { return hasValue_; }

    template <typename T>
    Optional<T>& Optional<T>::operator=(const T& val) {
      setValue(val);
      return *this;
    }

    template <typename T>
    Optional<T>& Optional<T>::operator=(const Optional<T>& other) {
      if (other.hasValue())
        setValue(other.value());
      else
        reset();
      return *this;
    }

    template <typename T>
    T& Optional<T>::operator*() { return value_; }

    template <typename T>
    const T& Optional<T>::operator*() const { return value_; }

    template <typename T>
    T* Optional<T>::operator->() { return &value_; }

    template <typename T>
    const T* Optional<T>::operator->() const { return &value_; }

    template <typename T>
    bool Optional<T>::operator==(const Optional<T>& other) const {
      if (hasValue_ != other.hasValue_) return false;
      if (!hasValue_) return true;
      return value_ == other.value_;
    }

    template <typename T>
    bool Optional<T>::operator!=(const Optional<T>& other) const {
      return !(*this == other);
    }
  }
}