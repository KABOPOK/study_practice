#include "biginteger.h"
void miniReverse(char*& mass, int to, int from) {
	for (int i = 0; i < 4; ++i) {
		std::swap(mass[to + i], mass[from - 1 - i]);
	}
}
void numRepresent(char* binaryCase, int n, const unsigned char* num) {
	int j{};
	for (int i = 0; i < n; ++i) {
		int itermediat = num[i];
		for (int eight = 0; eight < 8; ++eight) {
			binaryCase[j] = static_cast<signed char>(itermediat % 2);
			itermediat /= 2;
			++j;
		}
	}
}
std::string doub(std::string str) {
	int bonus{};
	for (int i = static_cast<signed int>(str.length() - 1); i >= 0; --i) {
		if (str[i] * 2 + bonus > 9) {
			str[i] = bonus + str[i] * 2 - 10;
			bonus = 1;
		}
		else {
			str[i] = str[i] * 2 + bonus;
			bonus = 0;
		}
	}
	const char a = 1;
	if (bonus != 0) {
		str.insert(0, 1, '\x1');
	}
	return str;
}
std::string plus(std::string str, char ch) {
	int bonus{};
	int len = static_cast<signed int>(str.length() - 1);
	if (str[len] + ch > 9) {
		for (int i = len; i >= 0; --i) {
			if (str[i] + ch > 9) {
				str[i] = 0;
				bonus = 1;
			}
			else {
				str[i] += bonus;
				bonus = 0;
			}
		}
	}
	else {
		str[len] += ch;
	}
	if (bonus != 0) {
		str.insert(0, 1, '\x1');
	}
	return str;
}
std::string plus(std::string& strX, std::string strY) {
	int bonus{};
	for (int i = 0; i <= strY.length() - 1 || bonus != 0; ++i) {
		if (strX[i] + strY[i] + bonus > 9) {
			strX[i] += (strY[i] - 10 + bonus);
			bonus = 1;
		}
		else {
			strX[i] += strY[i] + bonus;
			bonus = 0;
		}
	}
	return strX;
}
void to_str(char* binaryCase, std::string& answer, int n) {
	int from = n - 1;
	while (binaryCase[from] == 0) { --from; }
	answer = binaryCase[from];
	for (int i = from - 1; i >= 0; --i) {
		answer = plus(doub(answer), binaryCase[i]);
	}
}
std::string to_string(const BigInteger& X) {
	if (X.number_[X.size_ - 2] == '\0') { return "0"; }
	char* binaryCase = new char[(X.size_ - 1) * 8];
	std::string answer;
	numRepresent(binaryCase, X.size_ - 1, X.number_);
	to_str(binaryCase, answer, (X.size_ - 1) * 8);
	delete[] binaryCase;
	for (int i{}; i < answer.length(); ++i) {
		answer[i] += '0';
	}
	if (X.sign_ == -1) { return '-' + answer; }
	return answer;
}
