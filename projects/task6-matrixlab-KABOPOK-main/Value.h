#ifndef VALUES
#define VALUES
#include"Matrix.h"
class Value {
	Matrix VALUE;
	fraction value;
	bool matrix;
	bool frac;
	char name[32];
public:
	Value(const char* VName)  {
		for (int i = 0; i < 32; ++i) {
			name[i] = VName[i];
		}
		matrix = false;
		frac = false;
	}
	Value(std::string VName, const fraction &a) : VALUE(a), value(a) {
		for (int i = 0; i < VName.size(); ++i) {
			name[i] = VName[i];
		}
		//VALUE = Matrix(a);
		for (int i = (int)VName.size(); i < 32; ++i) {
			name[i] = 0;
		}
		matrix = false;
		frac = true;
	}
	Value(std::string VName, const Matrix &a) : VALUE(a) {
		for (int i = 0; i < VName.size(); ++i) {
			name[i] = VName[i];
		}
		for (int i = (int)VName.size(); i < 32; ++i) {
			name[i] = 0;
		}
		matrix = true;
		frac = false;
	}
	Value(const Matrix& M) : VALUE(M) {
		for (int i = 0; i < 32; ++i) {
			name[i] = 0;
		}
		matrix = true;
		frac = false;
	}
	Value(const fraction& a) : VALUE(a), value(a) {
		for (int i = 0; i < 32; ++i) {
			name[i] = 0;
		}
		//VALUE = Matrix(a);
		matrix = false;
		frac = true;
	}
	Value(const Matrix &M, const char* VName) : VALUE(M) {
		for (int i = 0; i < 32; ++i) {
			name[i] = VName[i];
		}
		matrix = true;
		frac = false;
	}
	Value(const fraction &a, const char* VName) : VALUE(a), value(a) {
		for (int i = 0; i < 32; ++i) {
			name[i] = VName[i];
		}
		//VALUE = Matrix(a);
		matrix = false;
		frac = true;
	}
	char* getName(){
		return name;
	}
	bool getType() const {
		return matrix;
	}
	Matrix getMatrix() {
		return VALUE;
	}
	fraction getFraction() {
		return value;
	}

};
#endif
