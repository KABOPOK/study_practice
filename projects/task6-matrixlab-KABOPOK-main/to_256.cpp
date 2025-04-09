#include "biginteger.h"
int binary(unsigned char* binaryCase, std::string str) {
	for (int i{}; i < str.length(); ++i) {
		str[i] -= '0';
	}
	int j = 0;
	int z = 0;
	while (z != str.length()) {
		int ten{};
		for (int i = z; i < str.length(); ++i) {
			if (str[i] % 2 == 1) {
				str[i] = (str[i] + ten) / 2;
				ten = 10;
			}
			else {
				str[i] = (str[i] + ten) / 2;
				ten = 0;
			}
		}
		if (ten != 0) {
			binaryCase[j] = 1;
		}
		else {
			binaryCase[j] = '\0';
		}
		++j;
		if (str[z] == '\0') { ++z; }
	}
	return j;
}
void converter(const unsigned char* binaryCase, unsigned char* number_, int size) {
	int j = {};
	int s = size;
	if (size % 8 != 0) {
		size = size / 8 + 1;
	}
	else { size /= 8; }
	for (int i = 0; i < size; ++i) {
		int sum{};
		for (int b{}; b < 8 && j != s; ++b) {
			sum += int(binaryCase[j] * pow(2, b));
			++j;
		}
		number_[i] = sum;
	}
}

std::ostream& operator<< (std::ostream& out, const BigInteger& A) {
	out << to_string(A);
	return out;
}

BigInteger operator+ (const BigInteger& X, const BigInteger& Y) {
	BigInteger result(X);
	result += Y;
	return result;
}

BigInteger operator* (const BigInteger& X, const BigInteger& Y) {
	BigInteger result(X);
	result *= Y;
	return result;
}

BigInteger operator- (const BigInteger& X, const BigInteger& Y) {
	BigInteger result(X);
	result += -Y;
	return result;
}

BigInteger operator% (const BigInteger& X, const BigInteger& Y) {
	BigInteger result(X);
	result %= Y;
	return result;
}

BigInteger operator/ (const BigInteger& X, const BigInteger& Y) {
	BigInteger result(X);
	result /= Y;
	return result;
}

bool operator<= (const BigInteger& X, const BigInteger& Y) {
	return X < Y || X == Y;
}

bool operator!= (const BigInteger& X, const BigInteger& Y) {
	return !(X == Y);
}

bool operator>= (const BigInteger& X, const BigInteger& Y) {
	return Y < X;
}

bool operator> (const BigInteger& X, const BigInteger& Y) {
	return !(X < Y);
}

bool operator== (const BigInteger& X, const BigInteger& Y) {
	return X.isEqual(Y);
}

bool operator== (const int& X, const BigInteger& Y) {
	BigInteger tmp(X);
	return tmp.isEqual(Y);
}
