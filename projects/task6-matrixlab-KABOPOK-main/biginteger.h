#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#define __standart__

#ifdef  __standart__
//typedef std::basic_string<unsigned char> ustring;
const int byte = 256;
//ustring to_256(std::string str);
int binary(unsigned char* binaryCase, std::string str);
void converter(const unsigned char* binaryCase, unsigned char* number_, int size);
class BigInteger {
	char sign_;
	unsigned char* number_;
	int size_;
	void swap(BigInteger& other) {
		std::swap(sign_, other.sign_);
		std::swap(size_, other.size_);
		std::swap(number_, other.number_);
	}
public:
	// for string
	BigInteger() : sign_(1) {
		size_ = 2;
		number_ = new unsigned char[size_];
		number_[0] = '\0';
		number_[1] = '\0';
	}
	BigInteger(std::string inputStr) : sign_(1) {
		if (inputStr[0] == '-') { sign_ = -1; inputStr.erase(0, 1); }
		if (inputStr.length() == 0) { throw std::invalid_argument(inputStr); }
		for (int i = 0; i < inputStr.length(); ++i) {
			if (inputStr[i] < '0' || inputStr[i] > '9') {
				throw std::invalid_argument(inputStr);
			}
		}
		if (inputStr.length() == 0) { throw std::invalid_argument(inputStr); }
		unsigned char* binaryCase = new unsigned char[inputStr.length() * 4]{};
		int size = binary(binaryCase, inputStr);
		if (size % 8 != 0) {
			size_ = size / 8 + 2;
		}
		else { size_ = size / 8 + 1; }
		number_ = new unsigned char[size_] {};
		converter(binaryCase, number_, size);
		number_[size_ - 1] = '\0';
		delete[] binaryCase;
	}

	BigInteger(int n) : BigInteger((signed long long)n) {
		/*number_ = nullptr;
		*this = BigInteger((signed long long)n);
		*/
	}
	BigInteger(long n) : BigInteger((signed long long)n) {
		/*number_ = nullptr;
		*this = BigInteger((signed long long)n);
		*/
	}
	BigInteger(unsigned int n) : BigInteger((unsigned long long)n) {
		/*number_ = nullptr;
		*this = BigInteger((unsigned long long)n);
		*/
	}
	BigInteger(unsigned long n) : BigInteger((unsigned long long)n) {
		/*number_ = nullptr;
		*this = BigInteger((unsigned long long)n);
		*/
	}

	BigInteger(signed long long n) {
		if (n < 0) { sign_ = -1; n *= -1; }
		else { sign_ = 1; }
		std::string inputStr = std::to_string(n);
		unsigned char* binaryCase = new unsigned char[inputStr.length() * 4]{};
		int size = binary(binaryCase, inputStr);
		if (size % 8 != 0) {
			size_ = size / 8 + 2;
		}
		else { size_ = size / 8 + 1; }
		number_ = new unsigned char[size_] {};
		converter(binaryCase, number_, size);
		number_[size_ - 1] = '\0';
		delete[] binaryCase;
	}

	BigInteger(unsigned long long n) {
		if (n < 0) { sign_ = -1; n *= -1; }
		else { sign_ = 1; }
		std::string inputStr = std::to_string(n);
		unsigned char* binaryCase = new unsigned char[inputStr.length() * 4]{};
		int size = binary(binaryCase, inputStr);
		if (size % 8 != 0) {
			size_ = size / 8 + 2;
		}
		else { size_ = size / 8 + 1; }
		number_ = new unsigned char[size_] {};
		converter(binaryCase, number_, size);
		number_[size_ - 1] = '\0';
		delete[] binaryCase;
	}
	BigInteger(const BigInteger& X) {
		sign_ = X.sign_;
		size_ = X.size_;
		number_ = new unsigned char[X.size_];
		memcpy(number_, X.number_, X.size_);
	}
	BigInteger(BigInteger&& X) noexcept {
		number_ = nullptr;
		sign_ = 0;
		size_ = 0;
		swap(X);
	}
	BigInteger& operator= (BigInteger&& other) noexcept {
		BigInteger tmp(std::move(other)); // �����������
		swap(tmp);
		return *this;
	}

	BigInteger operator-() const {
		BigInteger y(*this);
		y.sign_ = static_cast<signed char>(-sign_);
		return y;
	}
	BigInteger operator+() const {
		return *this;
	}
	BigInteger abc() const {
		if (sign_ < 0) {
			BigInteger tmp(*this);
			tmp.sign_ = 1;
			return  tmp;
		}
		return *this;
	}
	BigInteger& operator+= (const BigInteger& other) {
		oversize();
		if (sign_ == other.sign_) {
			int residue{};
			int to = other.size_;
			if (*this < other) {
				BigInteger tmp(other);
				for (int i = 0; i < size_ - 1 || residue != 0; ++i) {
					if (size_ <= i && residue == 1) {
						if (tmp.number_[i] == byte - 1) {
							tmp.number_[i] = 0;
						}
						else {
							++tmp.number_[i];
							break;
						}
					}
					if (number_[i] + tmp.number_[i] + residue >= byte) {
						tmp.number_[i] += (number_[i] - byte + residue);
						residue = 1;
					}
					else {
						tmp.number_[i] += number_[i] + residue;
						residue = 0;
					}
				}
				//*this = tmp;
				swap(tmp);
			}
			else {
				for (int i = 0; i < to - 1 || residue != 0; ++i) {
					if (other.size_ - 1 <= i && residue == 1) {
						if (number_[i] == byte - 1) {
							number_[i] = 0;
						}
						else {
							++number_[i];
							break;
						}
					}
					if (other.number_[i] + number_[i] + residue >= byte) {
						number_[i] += (other.number_[i] - byte + residue);
						residue = 1;
					}
					else {
						number_[i] += other.number_[i] + residue;
						residue = 0;
					}
				}
			}
		}
		else {
			// poblem with one
			int debt{};
			if (*this < other) {
				BigInteger tmp(other);
				for (int i = 0; i < size_ - 1 || debt != 0; ++i) {
					if (i >= size_ - 1 && debt != 0) {
						if (tmp.number_[i] == 0) {
							tmp.number_[i] = byte - 1;
						}
						else {
							--tmp.number_[i];
							break;
						}
					}
					if (tmp.number_[i] - number_[i] - debt < 0) {
						tmp.number_[i] += (byte - (number_[i] + debt));
						debt = 1;
					}
					else {
						tmp.number_[i] -= (number_[i] + debt);
						debt = 0;
					}
				}
				//*this = tmp;
				swap(tmp);
			}
			else {
				for (int i = 0; i < other.size_ - 1 || debt != 0; ++i) {
					if (i >= other.size_ - 1 && debt != 0) {
						if (number_[i] == 0) {
							number_[i] = byte - 1;
						}
						else {
							--number_[i];
							break;
						}
					}
					if (number_[i] - (other.number_[i] + debt) < 0) {
						number_[i] += (byte - (other.number_[i] + debt));
						debt = 1;
					}
					else {
						number_[i] -= (other.number_[i] + debt);
						debt = 0;
					}
				}
			}
		}

		//overflow +\0
		if (number_[size_ - 1] != '\0') {
			++size_;
			unsigned char* tmp = new unsigned char[size_] {0};
			int i{};
			for (; i < size_ - 1; ++i) { tmp[i] = number_[i]; }
			tmp[size_ - 1] = '\0';
			delete[] number_;
			number_ = tmp;

		}
		while (number_[size_ - 2] == '\0' && size_ - 2 > 0) {
			--size_;
		}
		return *this;
	}
	BigInteger& operator-= (const BigInteger& other) {
		oversize();
		*this += -other;
		return *this;
	}
	BigInteger& operator= (const BigInteger& X) {
		if (this != &X) {
			sign_ = X.sign_;
			size_ = X.size_;
			delete[] number_;
			this->number_ = new unsigned char[X.size_];
			//strcpy_s(number_, X.size_, X.number_);
			//memcpy(number_, X.number_, X.size_);
			for (int i = 0; i < X.size_; ++i) {
				number_[i] = X.number_[i];
			}
		}
		return *this;
	}
	BigInteger& operator= (int n) {
		if (n < 0) { sign_ = -1; }
		else { sign_ = 1; }
		std::string inputStr = std::to_string(n);
		unsigned char* binaryCase = new unsigned char[inputStr.length() * 4]{};
		int size = binary(binaryCase, inputStr);
		if (size % 8 != 0) {
			size_ = size / 8 + 2;
		}
		else { size_ = size / 8 + 1; }
		delete[] number_;
		number_ = new unsigned char[size_] {};
		converter(binaryCase, number_, size);
		number_[size_ - 1] = '\0';
		delete[] binaryCase;
		return *this;
	}

	BigInteger& oversize() {
		if (size_ <= 2) { return *this; }
		for (int i = size_ - 2; number_[i] == 0; --size_, --i) {}
		if (number_[size_ - 1] != 0) {
			++size_;
			unsigned char* tmp = new unsigned char[size_] {0};
			for (int i = 0; i < size_ - 1; ++i) {
				tmp[i] = number_[i];
			}
			delete[] number_;
			number_ = tmp;
		}
		return*this;
	}

	BigInteger& operator*= (const BigInteger& X) {
		oversize();
		char sign = static_cast<signed char>(X.sign_ * sign_);
		sign_ = static_cast<signed char>(X.sign_ * sign_);
		BigInteger answer;
		if (size_ < X.size_) {
			BigInteger cpyX(X);
			int zero{};
			for (int i{}; i < size_ - 1; ++i) {
				BigInteger tmp(X);
				int factor = number_[i];
				int resude{};
				for (int j{}; j < cpyX.size_ - 1; ++j) {
					if (factor * cpyX.number_[j] + resude >= byte) {
						tmp.number_[j] = (resude + factor * cpyX.number_[j]) % byte;
						resude = (resude + factor * cpyX.number_[j]) / byte;
					}
					else {
						tmp.number_[j] = resude + factor * cpyX.number_[j];
						resude = 0;
					}
				}
				if (resude != 0) {
					tmp.number_[tmp.size_ - 1] += resude;
				}
				if (zero != 0 || tmp.number_[tmp.size_ - 1] != '\0') {
					int last{};
					if (tmp.number_[tmp.size_ - 1] != '\0') { last = 1; }
					unsigned char* newTmp;
					newTmp = new unsigned char[zero + last + tmp.size_ + 100];
					int i{};
					tmp.size_ += zero + last;
					for (; i < zero; ++i) {
						newTmp[i] = '\0';
					}
					for (int j = 0; j < tmp.size_ - 1; ++j) {
						newTmp[i + j] = tmp.number_[j];
					}
					if (last != 0) {
						newTmp[tmp.size_ - 1] = '\0';
					}
					delete[] tmp.number_;
					tmp.number_ = newTmp;

				}
				//std::cout << to_string(tmp) << '\n';
				answer += tmp;
				++zero;
			}
		}
		else {
			int zero{};
			for (int i{}; i < X.size_ - 1; ++i) {
				BigInteger tmp(*this);
				int factor = X.number_[i];
				int resude{};
				for (int j{}; j < size_ - 1; ++j) {
					if (factor * number_[j] + resude >= byte) {
						tmp.number_[j] = (resude + factor * number_[j]) % byte;
						resude = (resude + factor * number_[j]) / byte;
					}
					else {
						tmp.number_[j] = resude + factor * number_[j];
						resude = 0;
					}
				}
				if (resude != 0) {
					tmp.number_[tmp.size_ - 1] += resude;
				}
				if (zero != 0 || tmp.number_[tmp.size_ - 1] != '\0') {
					int last{};
					if (tmp.number_[tmp.size_ - 1] != '\0') { last = 1; }
					unsigned char* newTmp;
					newTmp = new unsigned char[zero + last + tmp.size_ + 100];
					int i{};
					tmp.size_ += zero + last;
					for (; i < zero; ++i) {
						newTmp[i] = '\0';
					}
					for (int j = 0; j < tmp.size_ - 1; ++j) {
						newTmp[i + j] = tmp.number_[j];
					}
					if (last != 0) {
						newTmp[tmp.size_ - 1] = '\0';
					}
					delete[] tmp.number_;
					tmp.number_ = newTmp;

				}
				//std::cout << to_string(tmp) << '\n';
				answer += tmp;
				++zero;
			}
		}
		answer.oversize();
		answer.sign_ = sign;
		//*this = answer;
		swap(answer);
		return *this;
	}
	BigInteger& operator/= (const BigInteger& X_1) {
		oversize();
		char sign = static_cast<signed char>(X_1.sign_ * sign_);
		BigInteger X(X_1);
		X.sign_ = 1;
		sign_ = 1;
		BigInteger tmp(*this);
		if (this->isEqual(X)) {
			delete[] this->number_;
			size_ = 2;
			number_ = new unsigned char[2]{};
			number_[0] = '\x1';
			this->sign_ = sign;
			return *this;
		}
		BigInteger answer(tmp);
		for (int i{}; i < tmp.size_ - 1; ++i) {
			answer.number_[i] = '\0';
		}
		int n(answer.size_ - 2);
		for (int i = n; i >= 0; --i) {
			int left = 0;
			int right = byte;
			while (true) {
				int middle = (right + left) / 2;
				answer.number_[i] = middle;
				if (middle == 0) {
					--answer.size_;
					answer.number_[answer.size_ - 1] = '\0';
					break;
				}
				tmp = answer;
				tmp *= X;
				if (*this < tmp || this->isEqual(tmp)) {
					if (this->isEqual(tmp)) { break; }
					answer.number_[i] = middle - 1;
					tmp = answer;
					tmp *= X;
					if (*this < tmp) {
						right = middle;
					}
					else { break; }
				}
				else {
					if (this->isEqual(tmp)) { break; }
					if (middle + 1 == 256) {
						answer.number_[i] = middle;
						break;
					}
					answer.number_[i] = middle + 1;
					tmp = answer;
					tmp *= X;
					if (tmp < *this || tmp.isEqual(*this)) {
						left = middle;
					}
					else {
						answer.number_[i] = middle;
						break;
					}
				}
			}

		}
		answer.oversize();
		answer.sign_ = sign;
		// *this = answer;
		swap(answer);
		return *this;
	}
	BigInteger& operator%= (const BigInteger& X) {
		oversize();
		BigInteger tmp(*this);
		tmp /= X;
		tmp *= X;
		*this -= tmp;
		return *this;
	}
	BigInteger& operator++() {
		*this += 1;
		return *this;
	}
	BigInteger operator++(int) {
		BigInteger tmp(*this);
		++(*this);
		return tmp;
	}
	BigInteger& operator--() {
		*this -= 1;
		return *this;
	}
	BigInteger operator--(int) {
		BigInteger tmp(*this);
		--(*this);
		return tmp;
	}
	bool lessThanIt(const BigInteger& X) const {
		if (sign_ == -1 && X.sign_ == 1) { return true; }
		if (sign_ == 1 && X.sign_ == -1) { return false; }
		if (size_ < X.size_) { return true; }
		if (size_ > X.size_) { return false; }
		for (int i = X.size_ - 2; i >= 0; --i) {
			if (number_[i] <= X.number_[i]) {
				if (number_[i] == X.number_[i]) { continue; }
				return true;
			}
			return false;
		}
		return number_[0] < X.number_[0];
	}
	bool operator< (const BigInteger& X) const {
		if (this->abc().isEqual(X.abc())) { return false; };
		if (size_ < X.size_) { return true; }
		if (size_ > X.size_) { return false; }
		for (int i = X.size_ - 2; i >= 0; --i) {
			if (number_[i] <= X.number_[i]) {
				if (number_[i] == X.number_[i]) { continue; }
				return true;
			}
			return false;
		}
		if (number_[0] < X.number_[0]) { return true; }
		return true;
	}
	bool isEqual(const BigInteger& X) const {
		if (number_[0] == '\0' && X.number_[0] == '\0' && size_ == 2 && X.size_ == 2) { return true; }
		if (size_ != X.size_) { return false; }
		if (sign_ != X.sign_) { return false; }
		for (int i = 0; i < X.size_ - 1; ++i) {
			if (number_[i] != X.number_[i]) { return false; }
		}
		return true;
	}
	bool getSign() const{
		return !(sign_ == -1);
	}
	void setSign(BigInteger& X) {
		this->sign_ = (char)(this->sign_*X.sign_);
		X.sign_ = 1;
	}
	~BigInteger() {
		if (number_ != nullptr) {
			delete[] number_;
			number_ = nullptr;
		}
	}

	//bad idea
	friend std::ostream& operator<< (std::ostream& out, const BigInteger& A);
	friend std::string to_string(const BigInteger&);
};
//convert system 
//void reverse(unsigned char* cpyStr, int n);
//void strAdd(std::string& cpyStr, int part, int anwCounter);
//std::string zeroProblem(int part, int start, int itr, const std::string& str);
//int lenghtChek(const std::string str, int start, int end, int& itr);
//to_string

void miniReverse(char*& mass, int to, int from);
void numRepresent(char* binaryCase, int n, const unsigned char* num);
std::string doub(std::string str);
std::string plus(std::string str, char ch);
std::string plus(std::string& strX, std::string strY);
void to_str(char* binaryCase, std::string& answer, int n);
std::string to_string(const BigInteger& X);

bool operator== (const BigInteger& X, const BigInteger& Y);

bool operator== (const int& X, const BigInteger& Y);

std::ostream& operator<< (std::ostream& out, const BigInteger& A);

BigInteger operator+ (const BigInteger& X, const BigInteger& Y);

BigInteger operator* (const BigInteger& X, const BigInteger& Y);

BigInteger operator- (const BigInteger& X, const BigInteger& Y);

BigInteger operator% (const BigInteger& X, const BigInteger& Y);

BigInteger operator/ (const BigInteger& X, const BigInteger& Y);

bool operator<= (const BigInteger& X, const BigInteger& Y);

bool operator!= (const BigInteger& X, const BigInteger& Y);

bool operator>= (const BigInteger& X, const BigInteger& Y);

bool operator> (const BigInteger& X, const BigInteger& Y);


#endif