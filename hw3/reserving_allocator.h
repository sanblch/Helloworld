#include <iostream>

template<typename T, std::size_t N>
struct reserving_allocator {
  using value_type = T;

  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  reserving_allocator() {
    init = alloc(N);
    curr = init;
  }

  ~reserving_allocator() {
    deallocate(init, N);
  }

  template<typename U>
  struct rebind {
    using other = reserving_allocator<U, N>;
  };

  T* allocate(std::size_t n) {
    T* res;
    if(n <= static_cast<std::size_t>((init + N) - curr)) {
      res = curr;
      curr += n;
    } else {
      res = alloc(n);
    }
    return res;
  }

  void deallocate(T *p, std::size_t n) {
    if(p >= init + N) {
      std::free(p);
    } else if(p == init && n == N) {
      std::free(p);
    }
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args) {
    new(p) U(std::forward<Args>(args)...);
  }

  template<typename U>
  void destroy(U *p) {
    p->~U();
  }

private:
  T* alloc(std::size_t n) {
    auto p = std::malloc(n * sizeof(T));
    if (!p)
      throw std::bad_alloc();
    return reinterpret_cast<T *>(p);
  }

  T* init;
  T* curr;
};
