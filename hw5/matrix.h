#include <boost/functional/hash.hpp>
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>

template<unsigned S>
using MatrixIndex = std::array<unsigned, S>;

template<typename T, unsigned S>
using MatrixData = std::unordered_map<MatrixIndex<S>, T, boost::hash<MatrixIndex<S>>>;

template<typename T, T N, unsigned S>
class Matrix;

template<typename T, T N, unsigned S>
class MatrixRet {
public:
  MatrixRet(Matrix<T, N, S>& mtrx, unsigned ind) : iindex(0), mtrx(mtrx) {
    index.fill(std::numeric_limits<unsigned>::max());
    index[iindex] = ind;
  }

  MatrixRet<T, N, S>& operator=(T val) {
    check_index();
    if(mtrx.data.count(index) || val != N)
      mtrx.data[index] = val;
    if(val == N)
      mtrx.data.erase(index);
    return *this;
  }

  MatrixRet<T, N, S>& operator[](unsigned i) {
    ++iindex;
    if(iindex >= S) {
      throw std::invalid_argument("cannot get element from integral type");
    }
    index[iindex] = i;
    return *this;
  }

  operator T() {
    check_index();
    if(mtrx.data.count(index))
      return mtrx.data[index];
    return value;
  }

private:
  void check_index() {
    if(std::any_of(index.begin(), index.end(), [](unsigned v) {
          return v == std::numeric_limits<unsigned>::max();
        })) {
      throw std::invalid_argument("cannot assign value to matrix");
    }
  }
  unsigned iindex;
  MatrixIndex<S> index;
  Matrix<T, N, S>& mtrx;
  const T value {N};
};

template<typename T, unsigned S>
class MatrixIterator {
  using Iter = typename MatrixData<T, S>::iterator;
  Iter iter;

public:
  MatrixIterator(const Iter& iter) : iter(iter) {}

  auto operator*() {
    return std::tuple_cat(iter->first, std::tie(iter->second));
  }

  void operator++() noexcept {
    ++iter;
  }

  bool operator!=(const MatrixIterator<T, S>& it) const {
    return iter != it.iter;
  }
};

template<typename T, T N, unsigned S = 2>
class Matrix {
  friend class MatrixRet<T, N, S>;
  using iterator = MatrixIterator<T, S>;
public:
  MatrixRet<T, N, S> operator[](unsigned i) {
    return MatrixRet<T, N, S>(*this, i);
  }

  iterator begin() {
    return data.begin();
  }

  iterator end() {
    return data.end();
  }

  size_t size() const {
    return data.size();
  }

private:
  MatrixData<T, S> data;
};
