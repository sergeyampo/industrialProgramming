#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "MatrixCalculations.h"

using namespace std;

Matrix create_matrix() {
  int64_t n, m;
  do {
	cout << "Введите размеры матрицы nxm: ";
	cin >> n >> m;
  } while (n <= 0 || m <= 0);
  return Matrix(n, m);
}

int main() {
  srand(time(NULL));

  Matrix A_mtrx = create_matrix();
  Matrix B_mtrx = create_matrix();

  int64_t k = 2;
  do {
	cout << "Выберите способ заполнения матриц\n" <<
		 "1 - Вручную \n2 - Случайным образом\n";
	cin >> k;
  } while (k != 1 && k != 2);
  switch (k) {
	case 1:
	  cout << "Введите 1 матрицу:\n";
	  A_mtrx.fill_matrix(cin);
	  cout << "Введите 2 матрицу:\n";
	  B_mtrx.fill_matrix(cin);

	  cout << "\nМатрица 1\n";
	  cout << A_mtrx;

	  cout << "\nМатрица 2\n\n";
	  cout << B_mtrx;
	  break;
	case 2:
	  A_mtrx.fill_matrix(cin, true);
	  B_mtrx.fill_matrix(cin, true);

	  cout << "\nМатрица 1\n";
	  cout << A_mtrx;

	  cout << "\nМатрица 2\n\n";
	  cout << B_mtrx;
	  break;
    default:
      return 1;
     break;
  }

  MatrixCalculations::multiply_matrix(A_mtrx, B_mtrx);

  return 0;
}