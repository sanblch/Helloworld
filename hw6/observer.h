#include <forward_list>
#include <functional>

class Observable;

class Observer {
public:
  virtual ~Observer() {}
  virtual void update(const Observable& observable) = 0;
  const std::string& getName() const {
    return name;
  }
protected:
  std::string name;
};

class Observable {
  std::forward_list<std::reference_wrapper<Observer>> observers;
  bool changed;
public:
  virtual ~Observable() = default;
  
  void addObserver(Observer& o) {
    observers.emplace_front(o);
  }

  void removeObserver(const Observer &o) {
    observers.remove_if(
        [&o](Observer &i) { return o.getName() == i.getName(); });
  }

  void notifyObservers() {
    if(changed)
      for(auto it = observers.begin(); it != observers.end(); ++it)
        it->get().update(*this);
    changed = false;
  }

  void setChanged() {
    changed = true;
  }
};
