#include <iostream>

template<typename T>
struct logging_allocator {
  using value_type = T;

  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  template<typename U>
  struct rebind {
    using other = logging_allocator<U>;
  };

  static unsigned allocated;
  static unsigned deallocated;
  static unsigned constructed;
  static unsigned destroyed;

  T *allocate(std::size_t n) {
    ++allocated;
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    auto p = std::malloc(n * sizeof(T));
    if (!p)
      throw std::bad_alloc();
    return reinterpret_cast<T *>(p);
  }

  void deallocate(T *p, std::size_t n) {
    ++deallocated;
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    std::free(p);
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args) {
    ++constructed;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    new(p) U(std::forward<Args>(args)...);
  }

  template<typename U>
  void destroy(U *p) {
    ++destroyed;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    p->~U();
  }
};

template<typename T>
unsigned logging_allocator<T>::allocated = 0;
template<typename T>
unsigned logging_allocator<T>::deallocated = 0;
template<typename T>
unsigned logging_allocator<T>::constructed = 0;
template<typename T>
unsigned logging_allocator<T>::destroyed = 0;
