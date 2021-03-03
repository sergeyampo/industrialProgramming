#ifndef INDUSTRIALPROGRAMMING_FIRST_MATROX_H_
#define INDUSTRIALPROGRAMMING_FIRST_MATROX_H_

#include <stdint.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>


class Matrix {
  friend class MatrixCalculations;
 private:
  const int64_t n;

  const int64_t m;

  int64_t** data;

  void fill_with_rand() {
	srand(time(NULL));
	for (ptrdiff_t i = 0; i < n; ++i) {
	  for (ptrdiff_t j = 0; j < m; ++j) {
		data[i][j] = rand() % 100;
	  }
	}
  }

 public:
  Matrix() : n(0), m(0), data(nullptr) {}

  Matrix(const int64_t& n_lhs, const int64_t& m_rhs, const int64_t& num_to_fill): n(n_lhs), m(m_rhs) {
	data = new int64_t* [n];
	for (ptrdiff_t i = 0; i < n; ++i) {
	  data[i] = new int64_t[m];
	  for (ptrdiff_t j = 0; j < m; ++j) {
		data[i][j] = num_to_fill;
	  }
	}
  }

  Matrix(const int64_t& n_lhs, const int64_t& m_rhs, bool is_fill_with_rand = false) : n(n_lhs), m(m_rhs) {
	data = new int64_t* [n];
	for (ptrdiff_t i = 0; i < n; ++i) {
	  data[i] = new int64_t[m];
	}

	if (is_fill_with_rand)
	  fill_with_rand();
  }

  ~Matrix() {
	for (ptrdiff_t i = 0; i < n; ++i) {
	  delete[] data[i];
	}
	delete[] data;
  };

  Matrix(Matrix&&) = default;

  Matrix(const Matrix& rhs) : n(rhs.n), m(rhs.m) {
	data = new int64_t* [n];
	for (ptrdiff_t i = 0; i < n; ++i) {
	  data[i] = new int64_t[m];
	  for (ptrdiff_t j = 0; j < m; ++j)
		data[i][j] = rhs.data[i][j];
	}
  }

  Matrix& operator=(const Matrix& rhs){
    for(ptrdiff_t i = 0; i < rhs.m; ++i)
    	for(ptrdiff_t j = 0; j < rhs.m; ++j)
    	  data[i][j] = rhs.data[i][j];

    return *this;
  }

  Matrix& explicit_assign(const Matrix& rhs, const int64_t& i_shift = 0, const int64_t& j_shift = 0){
	for (ptrdiff_t i = 0; i < rhs.n; ++i)
	  for (ptrdiff_t j = 0; j < rhs.m; ++j)
		data[i][j] = rhs.data[i + i_shift][j + j_shift];

	return *this;
  }

  friend Matrix operator*(const Matrix&, const Matrix&);

  std::istream& fill_matrix(std::istream& in, const bool& is_rand = false) {
    if(!is_rand) {
	  for (ptrdiff_t i = 0; i < n; ++i)
		for (ptrdiff_t j = 0; j < m; ++j)
		  in >> data[i][j];
	}
    else {
	  fill_with_rand();
	}

	return in;
  }

  int64_t get_rows_amount() const noexcept(true) {
	return n;
  }

  int64_t get_column_amount() const noexcept(true) {
	return m;
  }

  std::pair<int64_t, int64_t> size() {
	return {n, m};
  }

  friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

std::ostream& operator<<(std::ostream& out, const Matrix& mtrx) {
  for (ptrdiff_t i = 0; i < mtrx.n; ++i) {
	for (ptrdiff_t j = 0; j < mtrx.m; ++j) {
	  out << mtrx.data[i][j] << " ";
	}
	out << "\n";
  }
}

#endif //INDUSTRIALPROGRAMMING_FIRST_MATROX_H_
