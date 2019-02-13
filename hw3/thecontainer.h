#include <memory>

template<typename T>
class TheContainerIterator;

template<typename T, typename A>
class TheContainer;

template<typename T>
class TheContainerItem {
  friend class TheContainerIterator<T>;
  template<class U, class Allocator>
  friend class TheContainer;

  TheContainerItem* next { nullptr };
  T val {};
public:
  TheContainerItem() {}
  TheContainerItem(TheContainerItem* next) : next(next) {}
  TheContainerItem(TheContainerItem* next, const T& val) : next(next), val(val) {}
};

template<typename T>
class TheContainerIterator {
  TheContainerItem<T>* item;

public:
  TheContainerIterator(TheContainerItem<T>* item) : item(item) {}

  T operator*() {
    return item->val;
  }

  TheContainerItem<T>* Item() {
    return item;
  }

  TheContainerIterator<T>& operator++() {
    item = item->next;
    return *this;
  }

  bool operator!=(const TheContainerIterator<T>& it) const {
    return item != it.item;
  }
};

template<class T, class Allocator = std::allocator<TheContainerItem<T>>>
class TheContainer {
  Allocator allocator;

  TheContainerItem<T>* init { nullptr };
  TheContainerItem<T>** next { &init };

public:
  TheContainer() = default;

  TheContainer(const TheContainer& other) {
    for(const auto &i : other)
      push_back(i);
  }

  TheContainer(TheContainer&& other) {
    if (other.init != nullptr) {
      std::swap(init, other.init);
      next = &(init->next);
      other.next = &other.init;
      while (*next != nullptr)
        next = &((*next)->next);
    }
  }

  ~TheContainer() {
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
  using iterator = TheContainerIterator<T>;

  void push_back(const T& t) {
    *next = allocator.allocate(1);
    allocator.construct(*next, nullptr, t);
    next = &((*next)->next);
  }

  void push_back(T&& t) {
    *next = allocator.allocate(1);
    allocator.construct(*next, nullptr, std::move(t));
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
