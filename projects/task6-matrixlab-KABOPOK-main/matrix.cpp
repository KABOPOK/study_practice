#include "Matrix.h"
std::ostream& operator<< (std::ostream& out, const Matrix& A) {
	int* MaxSize = new int[A.col_]{ 0 };
	int** currentSize = new int* [A.row_]{};
	for (int i = 0; i < A.row_; ++i) {
		currentSize[i] = new int[A.col_]{};
	}
	for (int row = 0; row < A.row_; ++row) {
		for (int col = 0; col < A.col_; ++col) {
			if (A.M_[row][col].getNumerator() == 0 || A.M_[row][col].getDenominator() == 0) { currentSize[row][col] = 1; }
			else if (A.M_[row][col].getDenominator() == 1) { currentSize[row][col] = to_string(A.M_[row][col].getNumerator()).size(); }
			else { currentSize[row][col] = (int)((to_string(A.M_[row][col].getNumerator())).size() + (to_string(A.M_[row][col].getDenominator())).size() + 1); }
			if (currentSize[row][col] > MaxSize[col]) { MaxSize[col] = currentSize[row][col]; }
		}
	}

	for (int row = 0; row < A.row_; ++row) {
		for (int col = 0; col < A.col_; ++col) {
			for (int i = 0; MaxSize[col] - currentSize[row][col] - i > 0; ++i) {
				out << ' ';
			}
			if (col == A.col_ - 1) { out << A.M_[row][col]; }
			else { out << A.M_[row][col] << ' '; }
		}
		out << std::endl;
		//std::cout << std::endl;
	}
	for (int i = 0; i < A.row_; ++i) {
		delete[] currentSize[i];
	}
	delete[] currentSize;
	delete[] MaxSize;
	return out;
}

Matrix operator-(const Matrix& X, const Matrix& Y) {
	Matrix tmp(X);
	return tmp -= Y;
}
Matrix operator+(const Matrix& X, const Matrix& Y) {
	Matrix tmp(X);
	return tmp += Y;
}
Matrix operator*(const Matrix& X, const Matrix& Y) {
	Matrix tmp(X);
	return tmp *= Y;
}
Matrix operator/(const Matrix& X, const Matrix& Y) {
	Matrix tmp(X);
	return tmp /= Y;
}
