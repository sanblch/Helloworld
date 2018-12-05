#include "matrix.h"
#include <cassert>

int main() {
  Matrix<int, 0> matrix;
  for(unsigned i = 0; i < 10; ++i)
    matrix[i][i] = i;

  for(unsigned i = 0; i < 10; ++i)
    matrix[9 - i][i] = i;

  for(unsigned i = 1; i < 9; ++i) {
    for(unsigned j = 1; j < 9; ++j) {
      if(j == 1)
        std::cout << matrix[i][j];
      else
        std::cout << " " << matrix[i][j];
    }
    std::cout << std::endl;
  }

  std::cout << matrix.size() << std::endl;
  for(auto c : matrix) {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }
}
