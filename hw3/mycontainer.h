#include <memory>

template<typename T>
class MyIterator;

template<typename T, typename A>
class MyContainer;

template<typename T>
class MyItem {
  friend class MyIterator<T>;
  template<class U, class Allocator>
  friend class MyContainer;

  MyItem* next { nullptr };
  T val {};
public:
  MyItem() {}
  MyItem(MyItem* next) : next(next) {}
  MyItem(MyItem* next, const T& val) : next(next), val(val) {}
};

template<typename T>
class MyIterator {
  MyItem<T>* item;

public:
  MyIterator(MyItem<T>* item) : item(item) {}

  T operator*() {
    return item->val;
  }

  MyItem<T>* Item() {
    return item;
  }

  MyIterator<T>& operator++() {
    item = item->next;
    return *this;
  }

  bool operator!=(const MyIterator<T>& it) const {
    return item != it.item;
  }
};

template<class T, class Allocator = std::allocator<MyItem<T>>>
class MyContainer {
  Allocator allocator;

  MyItem<T>* init { nullptr };
  MyItem<T>** next { &init };

public:
  MyContainer() = default;

  MyContainer(const MyContainer& other) {
    for(const auto &i : other)
      push_back(i);
  }

  MyContainer(MyContainer&& other) {
    if (other.init != nullptr) {
      std::swap(init, other.init);
      next = &(init->next);
      other.next = &other.init;
      while (*next != nullptr)
        next = &((*next)->next);
    }
  }

  ~MyContainer() {
    auto nxt = init;
    auto fnxt = nxt;
    while(nxt != nullptr) {
      fnxt = nxt->next;
      allocator.destroy(nxt);
      allocator.deallocate(nxt, 1);
      nxt = fnxt;
    }
  }

  using value_type = T;
  using iterator = MyIterator<T>;

  void push_back(T t) {
    *next = allocator.allocate(1);
    allocator.construct(*next, nullptr, t);
    next = &((*next)->next);
  }

  iterator begin() {
    return iterator(init);
  }

  iterator end() {
    return iterator(*next);
  }

  iterator begin() const {
    return iterator(init);
  }

  iterator end() const {
    return iterator(*next);
  }
};
