//
// Created by sergeyampo on 02.03.2021.
//

#ifndef INDUSTRIALPROGRAMMING_FIRST_LIB_MATRIXCALCULATIONS_H_
#define INDUSTRIALPROGRAMMING_FIRST_LIB_MATRIXCALCULATIONS_H_
#include "../Matrix.h"
#include <array>
#include <algorithm>


class MatrixCalculations {
  friend class Matrix;

 private:
  static Pair<Matrix, Matrix> align_matrix(const Matrix& mtrx_f, const Matrix& mtrx_s) {
	const auto matrix_sizes = std::Array<int64_t, 4>{mtrx_f.n, mtrx_f.m, mtrx_s.n, mtrx_s.m};
	const auto max_length = std::max(matrix_sizes);

	int64_t l = 2;
	if (l >= max_length) {
	  throw std::runtime_error("Bad sizes of matrix!");
	}

	for (; l < max_length; l *= 2);

	Matrix aligned_first_matrix(l, l, 0);
	aligned_first_matrix = mtrx_f;

	Matrix aligned_second_matrix(l, l, 0);
	aligned_second_matrix = mtrx_s;

	return {aligned_first_matrix, aligned_second_matrix};
  }

  static std::vector<Matrix> destructure_matrix(const Matrix& lhs, const Matrix& rhs) {
	const int64_t l_h = lhs.get_column_amount() / 2;
	std::vector<Matrix> res_matrix;
	res_matrix.reserve(8);
	for (short i = 0; i < 8; ++i) {
	  res_matrix.emplace_back(Matrix{l_h, l_h, 0});
	}
	res_matrix[0].explicit_assign(lhs);
	res_matrix[1].explicit_assign(lhs, 0, l_h);
	res_matrix[2].explicit_assign(lhs, l_h);
	res_matrix[3].explicit_assign(lhs, l_h, l_h);
	res_matrix[4].explicit_assign(rhs);
	res_matrix[5].explicit_assign(rhs, 0, l_h);
	res_matrix[6].explicit_assign(rhs, l_h);
	res_matrix[7].explicit_assign(rhs, l_h, l_h);

	return res_matrix;
  }

  static void calculate_temp_matrix(vector<Matrix>& temp_matrix, const vector<Matrix>& structured_matrix) {
	const int64_t l_h = temp_matrix[0].n;
	for (ptrdiff_t i = 0; i < l_h; ++i) {
	  for (ptrdiff_t j = 0; j < l_h; ++j) {
		for (ptrdiff_t z = 0; z < l_h; ++z) {
		  temp_matrix[0].data[i][j] += (structured_matrix[0].data[i][z] + structured_matrix[3].data[i][z])
			  * (structured_matrix[4].data[z][j] + structured_matrix[7].data[z][j]);
		  temp_matrix[1].data[i][j] +=
			  (structured_matrix[2].data[i][z] + structured_matrix[3].data[i][z]) * structured_matrix[4].data[z][j];
		  temp_matrix[2].data[i][j] +=
			  structured_matrix[0].data[i][z] * (structured_matrix[5].data[z][j] - structured_matrix[7].data[z][j]);
		  temp_matrix[3].data[i][j] +=
			  structured_matrix[3].data[i][z] * (structured_matrix[6].data[z][j] - structured_matrix[4].data[z][j]);
		  temp_matrix[4].data[i][j] +=
			  (structured_matrix[0].data[i][z] + structured_matrix[1].data[i][z]) * structured_matrix[7].data[z][j];
		  temp_matrix[5].data[i][j] += (structured_matrix[2].data[i][z] - structured_matrix[0].data[i][z])
			  * (structured_matrix[4].data[z][j] + structured_matrix[5].data[z][j]);
		  temp_matrix[6].data[i][j] += (structured_matrix[1].data[i][z] - structured_matrix[3].data[i][z])
			  * (structured_matrix[6].data[z][j] + structured_matrix[7].data[z][j]);
		}
	  }
	}
	for (short i = 8; i < 12; ++i) {
	  structured_matrix.emplace_back(Matrix{l_h, l_h});
	}
	structured_matrix[8].data[i][j] = temp_matrix[0].data[i][j] + temp_matrix[3].data[i][j] - temp_matrix[4].data[i][j] + temp_matrix[6].data[i][j];
	structured_matrix[9].data[i][j] = temp_matrix[2].data[i][j] + temp_matrix[4].data[i][j];
	structured_matrix[10].data[i][j] = temp_matrix[1].data[i][j] + temp_matrix[3].data[i][j];
	structured_matrix[11].data[i][j] = temp_matrix[0].data[i][j] - temp_matrix[1].data[i][j] + temp_matrix[2].data[i][j] + temp_matrix[5].data[i][j];
	
  }

  static Matrix build_result_matrix()

 public:
  MatrixCalculations() = delete;

  ~MatrixCalculations() = delete;

  static Matrix& multiply_matrix(Matrix& lhs, Matrix& rhs) {
	auto[aligned_first_matrix, aligned_second_matrix] = align_matrix(lhs, rhs);
	auto matrix_destructured = destructure_matrix(aligned_first_matrix, aligned_second_matrix);
	vector<Matrix> temp_matrix(8, Matrix{matrix_destructured[0].n, matrix_destructured[0].n, 0});
	calculate_temp_matrix(temp_matrix, matrix_destructured);

  }
};

#endif //INDUSTRIALPROGRAMMING_FIRST_LIB_MATRIXCALCULATIONS_H_