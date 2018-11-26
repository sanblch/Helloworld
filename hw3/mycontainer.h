#include <memory>

template<typename T>
struct MyItem {
  MyItem* next { nullptr };
  T val {};
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

  void operator++() {
    item = item->next;
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

  ~MyContainer() {
    auto nxt = init;
    auto fnxt = nxt;
    while(nxt != nullptr) {
      fnxt = nxt->next;
      allocator.deallocate(nxt, 1);
      nxt = fnxt;
    }
  }

  using value_type = T;
  using iterator = MyIterator<T>;

  void push_back(T t) {
    *next = allocator.allocate(1);
    (*next)->val = t;
    next = &((*next)->next);
  }

  iterator begin() {
    return iterator(init);
  }

  iterator end() {
    return iterator(*next);
  }
};