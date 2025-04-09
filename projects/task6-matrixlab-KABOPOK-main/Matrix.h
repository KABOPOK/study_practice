#ifndef MYMYITSMY
#define MYMYITSMY
#include"fraction.h"
#include <vector>
class Matrix {
	fraction** M_;
	int row_;
	int col_;
public:
	Matrix() : row_(0), col_(0) { M_ = nullptr; }
	Matrix(int rows, int cols) : row_(rows), col_(cols) {
		M_ = new fraction * [row_] {};
		for (int i = 0; i < row_; ++i) {
			M_[i] = new fraction[col_]{};
		}
	}
	Matrix(int a) : row_(1), col_(1) {
		M_ = new fraction * [row_] {0};
		for (int i = 0; i < row_; ++i) {
			M_[i] = new fraction[col_]{ 0 };
		}
		M_[0][0] = a;
	}
	Matrix(const fraction& b) : row_(1), col_(1) {
		M_ = new fraction * [row_] {0};
		for (int i = 0; i < row_; ++i) {
			M_[i] = new fraction[col_]{ 0 };
		}
		M_[0][0] = b;
	}
	Matrix(const Matrix& other) {
		row_ = other.row_;
		col_ = other.col_;
		M_ = new fraction * [row_] {};
		for (int i = 0; i < row_; ++i) {
			M_[i] = new fraction[col_]{};
		}
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				M_[row][col] = other.M_[row][col];
			}
		}
	}
	Matrix(char type, int rows, int cols) :row_(rows), col_(cols) {
		M_ = new fraction * [row_] {};
		for (int i = 0; i < row_; ++i) {
			M_[i] = new fraction[col_]{};
		}
		switch (type)
		{
		case 'z':
			/*for (int row = 0; row < row_; ++row) {
				for (int col = 0; col < col_; ++col) {
					M_[row][col] = 0;
				}
			}*/
			break;
		case 'o':
			for (int row = 0; row < row_; ++row) {
				for (int col = 0; col < col_; ++col) {
					M_[row][col] = 1;
				}
			}
			break;
		case 'e':
			for (int row = 0; row < row_; ++row) {
				for (int col = 0; col < col_; ++col) {
					if (row == col) { M_[row][col] = 1; }
				}
			}
			break;
		default:
			std::cout << "error type";
		}
	}
	//(horz/vert)cat
	Matrix(char type, std::vector<Matrix>& MatrixList) {
		if (type == '>') {
			col_ = MatrixList[0].col_;
			row_ = (int)(MatrixList[0].row_ * MatrixList.size());
			M_ = new fraction * [row_] {};
			for (int i = 0; i < row_; ++i) {
				M_[i] = new fraction[col_]{};
			}
			int rows = 0;
			for (int m = 0; m < MatrixList.size(); ++m) {
				for (int row = 0; row < MatrixList[m].row_; ++row, ++rows) {
					for (int col = 0; col < col_; ++col) {
						M_[rows][col] = MatrixList[m].M_[row][col];
					}
				}
			}
		}
		else {
			col_ = (int)(MatrixList[0].col_ * MatrixList.size());
			row_ = MatrixList[0].row_;
			M_ = new fraction * [row_] {};
			for (int i = 0; i < row_; ++i) {
				M_[i] = new fraction[col_]{};
			}
			int cols = 0;
			for (int m = 0; m < MatrixList.size(); ++m) {
				for (int row = 0; row < row_; ++row) {
					for (int col = 0; col < MatrixList[m].col_; ++col) {
						M_[row][cols + col] = MatrixList[m].M_[row][col];
					}
				}
				cols = MatrixList[0].col_ * (m + 1);
			}
		}
		//std::cout << *this;
	}
	//linspace (1....n)
	Matrix(fraction& x1, fraction& xn, fraction& n, int lenght) {
		fraction d = (n - x1) / (n - 1);
		col_ = lenght;
		row_ = 1;
		M_ = new fraction * [row_] {};
		M_[0] = new fraction[col_]{};
		for (int i = 0; i < col_; ++i) {
			M_[0][i] = x1 + fraction(i) * d;
		}
	}

	int getCol() const { return col_; }
	int getRow() const { return row_; }

	Matrix& operator+=(const Matrix& other)
	{
		if (col_ != other.col_)
		{
			//throw "Plus matrix: wrong matrix size";
		}
		if (row_ != other.row_)
		{
			//throw "Plus matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row)
		{
			for (int col = 0; col < col_; ++col)
			{
				M_[row][col] += other.M_[row][col];
			}

		}
		return *this;
	}
	Matrix& operator-=(const Matrix& other)
	{
		if (col_ != other.col_)
		{
			//throw "Plus matrix: wrong matrix size";
		}
		if (row_ != other.row_)
		{
			//throw "Plus matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row)
		{
			for (int col = 0; col < col_; ++col)
			{
				M_[row][col] -= other.M_[row][col];
			}

		}
		return *this;
	}
	Matrix& operator/=(const Matrix& other)
	{
		Matrix other_inv(other.inverse());
		if (other_inv.row_ != col_)
		{
			std::cout << "Multiplication: Wrong matrix size";
		}
		Matrix C('z', row_, other_inv.col_);
		for (int rowA = 0; rowA < row_; ++rowA)
		{
			for (int colB = 0; colB < other_inv.col_; ++colB)
			{
				for (int k = 0; k < col_; ++k) {
					C.M_[rowA][colB] += M_[rowA][k] * other_inv.M_[k][colB];
				}
			}

		}
		std::swap(*this, C);
		return *this;
	}
	Matrix& operator*=(const Matrix& other)
	{
		if (other.row_ != col_)
		{
			std::cout << "Multiplication: Wrong matrix size";
		}
		Matrix C('z', row_, other.col_);
		for (int rowA = 0; rowA < row_; ++rowA)
		{
			for (int colB = 0; colB < other.col_; ++colB)
			{
				for (int k = 0; k < col_; ++k) {
					C.M_[rowA][colB] += M_[rowA][k] * other.M_[k][colB];
				}
			}

		}
		std::swap(*this,C);
		return *this;
	}
	Matrix& operator= (const Matrix& other) {
		if(this!=&other) {
			for (int i = 0; i < row_; ++i) {
				delete[] M_[i];
			}
			delete[] M_;
			row_ = other.row_;
			col_ = other.col_;

			M_ = new fraction * [row_] {};
			for (int i = 0; i < row_; ++i) {
				M_[i] = new fraction[col_]{};
			}

			for (int row = 0; row < row_; ++row)
			{
				for (int col = 0; col < col_; ++col)
				{
					M_[row][col] = other.M_[row][col];
				}

			}
		}
		return *this;
	}
	Matrix operator-() const {
		Matrix M(*this);
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				M.M_[row][col] *= -1;
			}
		}
		return M;
	}

	//operation with Matrix
	Matrix inverse() const {
		//pull and add E
		Matrix I(row_, col_ * 2);
		for (int i = 0; i < row_; ++i) {
			for (int j = 0; j < row_; ++j) {
				I.M_[i][j] = M_[i][j];
			}
			for (int j = row_; j < 2 * row_; ++j) {
				if (i == j - row_) {
					I.M_[i][j] = 1;
				}
				else {
					I.M_[i][j] = 0;
				}
			}
		}
		//std::cout << I << std::endl;
		//upper triangual
		int row = 1;
		int col = 0;
		int constrow = 1;
		int count = 0;
		fraction cdoof = I.M_[0][0];
		for (int i = 0; i < 2 * row_; ++i) {
			I.M_[0][i] /= cdoof;
		}
		for (int col = 0; col < row_ - 1; ++col) {
			//std::cout << I << std::endl;
			constrow = 1 + col;
			row = 1 + col;
			for (int count = 0; count + col < row_ - 1; ++count) {
				//if coof = 4/0
				if (I.M_[col][col] == fraction()) {
					int i = col;
					while (i != row_ - 1) {
						if (I.M_[i][col] != fraction()) {
							break;
						}
						++i;
					}
					for (int j = 0 + col; j < 2 * row_; ++j) {
						I.M_[col][j] += I.M_[i][j];

					}
				}
				//end problem with 4/0
				fraction coof = I.M_[constrow][col] / I.M_[col][col];
				for (int j = 0 + col; j < 2 * row_; ++j) {
					I.M_[row][j] -= I.M_[col][j] * coof;
				}
				//std::cout << I << std::endl;
				++row;
				++constrow;
			}
			fraction coof = I.M_[col + 1][col + 1];
			for (int i = col + 1; i < 2 * row_; ++i) {
				I.M_[col + 1][i] /= coof;
			}
			//std::cout << I << std::endl;
		}
		//std::cout << I << std::endl;
		int a = 0;
		//under triangual
		for (int i = row_ - 2; i >= 0; --i) {
			for (int j = i; j >= 0; --j) {
				fraction coof = I.M_[j][i + 1];
				for (int l = 0; l < 2 * row_; ++l) {
					fraction as = 0;
					as = I.M_[i + 1][l] * coof;
					I.M_[j][l] -= as;//row&
				}
			}
			//std::cout << I << std::endl;
		}
		//for (int col = 0; col < row_ - 1; ++col) {
		//	for (int row = 0; row < col + 1; ++row) {
		//		fraction coof = I.M_[row][col + 1] / I.M_[col + 1][col + 1];
		//		for (int j = 1 + col; j < 2 * row_; ++j) {
		//			I.M_[row][j] -= I.M_[col + 1][j] * coof;//row&
		//		}
		//		std::cout << I << std::endl;
		//	}
		//}
		//std::cout << I << std::endl;
		Matrix I_Answ(row_, col_);
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				I_Answ.M_[row][col] = I.M_[row][col + I.row_];
			}
		}
		//std::cout << I_Answ;
		return I_Answ;
	}
	Matrix max(const Matrix& other) const {
		Matrix tmp(*this);
		if (col_ != other.col_)
		{
			std::cout << "max matrix: wrong matrix size";
		}
		if (row_ != other.row_)
		{
			std::cout << "max matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row)
		{
			for (int col = 0; col < col_; ++col)
			{
				if (tmp.M_[row][col] < other.M_[row][col]) {
					tmp.M_[row][col] = other.M_[row][col];
				}
			}

		}
		return tmp;
	}
	Matrix min(const Matrix& other) const {
		Matrix tmp(*this);
		if (col_ != other.col_)
		{
			std::cout << "min matrix: wrong matrix size";
		}
		if (row_ != other.row_)
		{
			std::cout << "min matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row)
		{
			for (int col = 0; col < col_; ++col)
			{
				if (tmp.M_[row][col] > other.M_[row][col]) {
					tmp.M_[row][col] = other.M_[row][col];
				}
			}

		}
		return tmp;
	}
	Matrix transpose() const {
		Matrix B(col_, row_);
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				B.M_[col][row] = M_[row][col];
			}
		}
		return B;
	}
	fraction getDet() const {
		//upper triangual
		Matrix I(*this);
		int row = 1;
		int col = 0;
		int constrow = 1;
		int count = 0;
		for (int col = 0; col < row_ - 1; ++col) {
			constrow = 1 + col;
			row = 1 + col;
			for (int count = 0; count + col < row_ - 1; ++count) {
				//if coof = 4/0
				if (I.M_[col][col] == fraction()) {
					int i = col;
					while (i != row_ - 1) {
						if (I.M_[i][col] != fraction()) {
							break;
						}
						++i;
					}
					for (int j = 0 + col; j < row_; ++j) {
						I.M_[col][j] += I.M_[i][j];

					}
				}
				//end problem with 4/0
				fraction coof = I.M_[constrow][col] / I.M_[col][col];
				for (int j = 0 + col; j < row_; ++j) {
					I.M_[row][j] -= I.M_[col][j] * coof;
					//std::cout << I << std::endl;
				}
				++row;
				++constrow;
				//std::cout << I << std::endl;
			}
		}
		fraction Det = 1;
		for (int i = 0; i < row_; ++i) {
			Det *= I.M_[i][i];
			//std::cout << I << std::endl;
		}
		return Det;
	}
	fraction getSum()const {
		fraction sum = 0;
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				//std::cout << sum << " + " << M_[row][col] << " = ";
				sum += M_[row][col];
				//std::cout << sum << std::endl;
			}
		}
		return sum;
	}
	fraction getMultiplication() const {
		fraction sum = 1;
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				//std::cout << sum << " * " << M_[row][col] << " = ";
				sum *= M_[row][col];
				//std::cout << sum << std::endl;
			}
		}
		return sum;
	}

	//unusual operations
	Matrix& Multiplication(const Matrix& other) {
		if (col_ != other.col_) {
			//throw "Plus matrix: wrong matrix size";
		}
		if (row_ != other.row_) {
			//throw "Plus matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				M_[row][col] *= other.M_[row][col];
			}
		}
		return *this;
	}
	Matrix& Division(const Matrix& other) {
		if (col_ != other.col_) {
			//throw "Plus matrix: wrong matrix size";
		}
		if (row_ != other.row_) {
			//throw "Plus matrix: wrong matrix size";
		}
		for (int row = 0; row < row_; ++row) {
			for (int col = 0; col < col_; ++col) {
				M_[row][col] /= other.M_[row][col];
			}
		}
		return *this;
	}

	~Matrix() {
		for (int i = 0; i < row_; ++i) {
			delete[] M_[i];
		}
		delete[] M_;
	}

	friend std::ostream& operator<< (std::ostream& out, const Matrix& A);
};


Matrix operator+ (const Matrix& X, const Matrix& Y);
Matrix operator/ (const Matrix& X, const Matrix& Y);
Matrix operator* (const Matrix& X, const Matrix& Y);
Matrix operator- (const Matrix& X, const Matrix& Y);
#endif
