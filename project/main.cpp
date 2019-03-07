#include <forward_list>
#include <functional>
#include <iostream>

class IBlock {
  std::forward_list<std::reference_wrapper<IBlock>> input;
  std::forward_list<std::reference_wrapper<IBlock>> output;
public:
  void setInput(IBlock& in) {
    input.emplace_front(in);
  }
  void setOutput(IBlock& out) {
    output.emplace_front(out);
  }
  void update() {
    for(auto it = input.begin(); it != input.end(); ++it)
      it->get().update();
  }
};

template <typename I, typename O>
class Block : public IBlock {
  std::function<O(I)> func;
public:
  Block() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Block(const Block&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Block(Block&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  template<typename BI>
  void setInput(Block<BI, I>& in) {
    IBlock::setInput(in);
  }

  template<typename BO>
  void setOutput(const Block<O, BO>& out) {
    IBlock::setOutput(out);
  }
};

int main() {
  Block<int, int> b1;
  Block<int, int> b2;
  b2.setInput(b1);
}
