#ifndef boolexp
#define boolexp
#include "nodes.h"
#include "errors.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
bool lenNum(int a, const char* M);
template <typename T>
void InsertSort(T* M, int n) {
	T tmp;
	for (int j = 1; j < n; ++j) {
		// j - номер вставляемого элемента
		tmp = M[j];
		int i;
		for (i = j; i > 0; --i) {
			if (tmp < M[i - 1]) {
				M[i] = M[i - 1];
			}
			else { break; }
		}
		if (i != j) {
			M[i] = tmp;
		}
	}
}
class SmartCharpoint{
	char* M_;
public:
	SmartCharpoint() {
		M_ = nullptr;
	}
	SmartCharpoint(char *M) {
		M_ = M;
		M = nullptr;
	}
	char* getPoint() {
		return M_;
	}
	~SmartCharpoint() {
		delete[] M_;
	}
};

class BooleanExpression {
	FormulaNode* root;
	FormulaNode* Postfix2Tree(const char*);
	void Infix2Postfix(const char* instr, char* outstr);
	static void parsing(const char* instr, char* outstr);
	char* str_;
	char* str_parsing;
public:
	Values V;
	BooleanExpression() {
		root = nullptr;
		str_ = nullptr;
	}

	BooleanExpression(const BooleanExpression& other) {
		size_t Len = strlen(other.str_parsing);
		Len = (Len < 10) ? 20 : 2 * Len;
		char* str_posfix = new char[Len] {0};
		str_parsing = new char[Len] {0};

		try {
			parsing(other.str_parsing, str_parsing);
			Infix2Postfix(str_parsing, str_posfix);
			str_ = str_posfix;
			root = Postfix2Tree(str_posfix);
		}
		catch (...) {
			delete[] str_posfix;
			delete[] str_parsing;
			delete[] str_;
			root = nullptr;
			throw;
		}
	}

	BooleanExpression(const char* str) {
		size_t Len = strlen(str);
		Len = (Len < 10) ? 20 : 2 * Len;
		char* str_posfix = new char[Len] {0};
		str_parsing = new char[Len] {0};

		try {
			parsing(str, str_parsing);
			Infix2Postfix(str_parsing, str_posfix);
			str_ = str_posfix;
			str_posfix = nullptr;
			if (strlen(str_) > 0) {
				root = Postfix2Tree(str_);
			}
			else { root = nullptr; }
		}
		catch (...) {
			//delete[] str_;
			delete[] str_posfix;
			delete[] str_parsing;
			root = nullptr;
			throw;
		}
	}

	void setBoolean(const char* str) {
		V.setCondition(str);
	}

	int setStr(std::string str) {
		size_t Len = strlen(str_);
		char* str_boolean = new char[Len] {0};
		int i = 0;
		int j = 0;
		int k = 0;
		while (j < Len) {
			if ((str_[j] >= 'a' && str_[j] <= 'z')) {
				str_boolean[i] = str[k];
				++i;
				j += 2;
				++k;
			}
			else {
				str_boolean[i] = str_[j];
				++i;
				++j;
			}
		}
		root = Postfix2Tree(str_boolean);
		if (root != nullptr) { return root->calc(); }
		delete[] str_boolean;
		return 0;
	}

	BooleanExpression dnf() {
		int counter = 0;
		int indx = 0;
		int ix = 0;
		int bound = (int)pow(2, V.amountVal);
		char* newStr = new char[strlen(str_) * (bound + 1)]{ 0 };
		char buff[128]{ 0 };

		//is it const?
		int* constant = new int[bound + 9]{ 0 };
		bool cnst = true;
		int result = 0;
		while (counter != bound && cnst) {
			char* str = new char[V.amountVal + 9]{ 0 }; //                       memory
			int j = 0;
			for (int i = V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			setBoolean(str);
			result = calc();
			if (isItComst(constant, result, counter)) {}
			else { cnst = false; }
			++counter;
			delete[] str;
		}
		counter = 0;
		delete[] constant;
		if (cnst) {			
			newStr[0] = (char)(result+ '0');
			SmartCharpoint smart(newStr);
			return BooleanExpression(smart.getPoint());
		}

		while (counter != bound) {
			char* str = new char[V.amountVal + 9]{ 0 };
			int b = 0;
			int j = 0;
			for (int i = V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			setBoolean(str);
			int result = calc();

			if (result == 1) {
				V.sort(str);
				if (buff[0] != 0) {
					for (int i = 0; i < strlen(buff); ++i) { //////////////???????
						newStr[indx] = buff[i];
						++indx;
					}
					for (int i = 0; buff[i] != 0; ++i) { buff[i] = 0; }
				}
				buff[b] = '(';
				++b;
				for (int k = 0; k < V.amountVal; ++k) {
					if (str[k] == '0') {
						if (k + 1 == V.amountVal) {
							buff[b] = '~';
							++b;
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = ')';
							++b;
							buff[b] = 'v';
							++b;
						}
						else {
							buff[b] = '~';
							++b;
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = '&';
							++b;
						}
					}
					else {
						if (k + 1 == V.amountVal) {
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = ')';
							++b;
							buff[b] = 'v';
							++b;
						}
						else {
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = '&';
							++b;
						}
					}
				}
				V.SendFlying();
			}
			++counter;
			delete[] str;
		}
		for (int i = 0; i < strlen(buff) - 1; ++i) {
			newStr[indx] = buff[i];
			++indx;
		}
		std::cout << newStr << std::endl;
		SmartCharpoint smart(newStr);
		return BooleanExpression(smart.getPoint());
	}

	BooleanExpression cnf() {
		int counter = 0;
		int indx = 0;
		int ix = 0;
		int bound = (int)pow(2, V.amountVal);
		char* newStr = new char[strlen(str_) * (bound + 1)]{ 0 };
		char buff[128]{ 0 };

		//is it const?
		int* constant = new int[bound + 9]{ 0 };
		bool cnst = true;
		int result = 0;
		while (counter != bound && cnst) {
			char* str = new char[V.amountVal + 9]{ 0 }; //                       memory
			int j = 0;
			for (int i = V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			setBoolean(str);
			result = calc();
			if (isItComst(constant, result, counter)) {}
			else { cnst = false; }
			++counter;
			delete[] str;
		}
		counter = 0;
		delete[] constant;
		if (cnst) {
			newStr[0] = (char)(result+'0');
			SmartCharpoint smart(newStr);
			return BooleanExpression(smart.getPoint());
		}

		while (counter != bound) {
			char* str = new char[V.amountVal + 9]{ 0 };
			int b = 0;
			int j = 0;
			for (int i = V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			setBoolean(str);
			int result = calc();

			if (result == 0) {
				V.sort(str);
				if (buff[0] != 0) {
					for (int i = 0; i < strlen(buff); ++i) { //////////////???????
						newStr[indx] = buff[i];
						++indx;
					}
					for (int i = 0; buff[i] != 0; ++i) { buff[i] = 0; }
				}
				buff[b] = '(';
				++b;
				for (int k = 0; k < V.amountVal; ++k) {
					if (str[k] == '1') {
						if (k + 1 == V.amountVal) {
							buff[b] = '~';
							++b;
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = ')';
							++b;
							buff[b] = '&';
							++b;
						}
						else {
							buff[b] = '~';
							++b;
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = 'v';
							++b;
						}
					}
					else {
						if (k + 1 == V.amountVal) {
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = ')';
							++b;
							buff[b] = '&';
							++b;
						}
						else {
							buff[b] = 'x';
							++b;
							putNumber(buff, V.SortValues[k], b);
							buff[b] = 'v';
							++b;
						}
					}
				}
				V.SendFlying();
			}
			++counter;
			delete[] str;
		}
		for (int i = 0; i < strlen(buff) - 1; ++i) {
			newStr[indx] = buff[i];
			++indx;
		}
		std::cout << newStr << std::endl;
		SmartCharpoint smart(newStr);
		return BooleanExpression(smart.getPoint());
	}

	BooleanExpression zhegalkin() {
		int amountVal = 0;
		bool end = false;
		if (strlen(str_) == 1) { return BooleanExpression(str_); }
		int counter = 0;
		amountVal = V.amountVal;
		int bound = (int)pow(2, V.amountVal);
		char* newStr = new char[strlen(str_) * (bound + 1)]{ 0 };
		std::string buff;
		while (counter != bound) {
			char* str = new char[V.amountVal + 9]{ 0 };
			int j = 0;
			for (int i = V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			setBoolean(str);
			int result = calc();
			if (result == 1) {
				//pairM strM(str);
				ChooseSort(str, V.SortValues, strlen(str));                          //////////////sort problem
				for (int k = 0; k < V.amountVal; ++k) {
					if (str[k] == '0') {
						if (k + 1 == V.amountVal) {
							buff.push_back('~');
							
							buff.push_back('x');
							
							putNumber(buff, V.SortValues[k]);
							
							buff.push_back(' ');
							
							buff.push_back('v');
							
							buff.push_back(' ');
							
						}
						else {
							buff.push_back('~');
							
							buff.push_back('x');
							
							putNumber(buff, V.SortValues[k]);
							
							buff.push_back('&');
							
						}
					}
					else {
						if (k + 1 == V.amountVal) {
							buff.push_back('x');
							
							putNumber(buff, V.SortValues[k]);
							
							buff.push_back(' ');
							
							buff.push_back('v');
							
							buff.push_back(' ');
							
						}
						else {
							buff.push_back('x');
							
							putNumber(buff, V.SortValues[k]);
							
							buff.push_back('&');
							
						}
					}
				}
				V.SendFlying();
			}
			++counter;
			delete[] str;
		}
		{
			if (buff.size() > 3) {
				buff[buff.size() - 1] = '\0';
				buff[buff.size() - 2] = '\0';
				buff[buff.size() - 3] = '\0';
			}
			// 1 action
			int ch = 2;
			int indx = 0;
			std::string outBuff;
			while (ch != '\0') {
				while (ch != '\0') {
					char fBlock[512]{ 0 };
					char sBlock[512]{ 0 };
					char* inBlock = fBlock;
					char* outBlock = sBlock;
					int i = 0;
					while ((ch = (int)(unsigned char)buff[indx]) != '\0' && ch != ' ') {
						inBlock[i] = (char)ch;
						++i;
						++indx;
					}
					//replace ~x.. to (1 + x..)
					char Oblock[512]{ 0 };
					replacer_1(inBlock, outBlock);
					char* tmp = outBlock;
					outBlock = inBlock;
					inBlock = tmp;
					for (int i = 0; outBlock[i] != 0; ++i) {
						outBlock[i] = 0;
					}
					//replace (1 + x..)&...
					replacer_2(inBlock, outBlock);
					if (strlen(inBlock) == 0) { inBlock = outBlock; }
					if (buff[indx] == '\0') { outBuff += inBlock; }
					else { outBuff += inBlock; outBuff += "+"; }
					indx += 3;
				}
				/*if (inFile.peek() != EOF) { outFile << std::endl; }
				if (ch == '\n') { ch = 0; }*/
			}
			outBuff.push_back('\0');
			outBuff.push_back('\0');
			outBuff.push_back('\0');

			// 2 action
			ch = 2;
			indx = 0;
			int** counter = new int* [amountVal + 1]{ 0 };
			int place = (int)pow(2, amountVal);
			for (int i = 0; i < amountVal + 1; ++i) {
				counter[i] = new int [place] {0};
			}

			//pull array[]
			while (outBuff[indx] != '\0') {
				char* str = new char[amountVal + 9]{ 0 };
				while (ch != '+' && ch != '\0') {
					ch = (int)(unsigned char)outBuff[indx];
					++indx;
					if (ch == 'x') {
						int number = 0;
						ch = (int)(unsigned char)outBuff[indx];
						char num[8]{ 0 };
						int a = 0;
						while (ch >= '0' && ch <= '9') {
							num[a] = (char)ch;
							++indx;
							ch = (int)(unsigned char)outBuff[indx];
							++a;
						}
						int d = (int)(strlen(num)-1);
						for (int o = 0; o < strlen(num); ++o) {
							number += (int)((num[o] - '0') * pow(10, d));
							--d;
						}
						str[V.findInd(number)] = 1;
					}
					else if (ch == '1') {
						++counter[amountVal][0];
						++indx;
						ch = (int)(unsigned char)outBuff[indx];
					}
					else { continue; }
				}

				int demision = 0;
				int d = 0;
				for (int i = amountVal - 1; i >= 0; --i) {
					demision += (int)(str[i] * pow(2, d));
					++d;
				}
				for (int i = 0; i < amountVal; ++i) {
					counter[i][demision] = (int)(unsigned char)str[i];
				}
				++counter[amountVal][demision];
				delete[] str;
				ch = 2;
				++indx;
			}

			//print it is...
			indx = 0;
			int amount_v = 0;
			for (int i = 0; i < place; ++i) {
				counter[amountVal][i] %= 2;
				if (counter[amountVal][i] != 0) { ++amount_v; }
			}
			if (counter[amountVal][0] == 1) {
				newStr[indx] = '1';
				++indx;
				newStr[indx] = ' ';
				++indx;
				newStr[indx] = '+';
				++indx;
				newStr[indx] = ' ';
				++indx;
			}
			for (int i = 1; i < place && amount_v != 0; ++i) {
				if (counter[amountVal][i] == 1) {
					int amount = 0;
					int numbers[128]{ 0 };
					int n = 0;
					for (int j = 0; j < amountVal; ++j) {
						if (counter[j][i] == 1) { 
							numbers[n] = V.SortValues[j];
							++n;
							++amount;
						}
					}
					InsertSort(numbers, n);
					n = 0;
					for (int j = 0; j < amountVal; ++j) {
						if (counter[j][i] == 1) {
							if (amount - 1 == 0) {
								newStr[indx] = 'x';
								++indx;
								putNumber(newStr, numbers[n], indx);
								++n;
							}
							else {
								newStr[indx] = 'x';
								++indx;
								putNumber(newStr, numbers[n], indx);
								++n;
								newStr[indx] = '&';
								++indx;
								--amount;
							}
						}
					}
					if (amount_v - 1 == 0) {}
					else {
						newStr[indx] = ' ';
						++indx;
						newStr[indx] = '+';
						++indx;
						newStr[indx] = ' ';
						++indx;
					}
					--amount_v;
				}
			}
			for (int i = 0; i < amountVal + 1; ++i) {
				delete[] counter[i];
			}
			delete[] counter;
			//end
		}
		SmartCharpoint smart(newStr);
		return BooleanExpression(smart.getPoint());
	}

	int calc()const {
		if (root!=nullptr) { return root->calc(); }
		return 0;
	}
	bool isEqual(const char* other) const {
		return strcmp(str_parsing, other)==0;
	}

	std::string str() const {
		//if (root) return root->str();
		return std::string(str_parsing);

	}
	~BooleanExpression() {
		delete root; 
		root = nullptr;
		delete[] str_parsing;
		delete[] str_;
	}
};

bool isFullSystem(const std::vector<BooleanExpression>& MathPart);

bool operator== (const BooleanExpression& X, const char* str);
//--------------------------------------------------------
int actionsRowNumber(char ch);
//--------------------------------------------------------
int actionColNumber(char ch);

//0 - ?
//1 - на выход
//2 - на стек
//3 - взять из стека на выход
//4 - выкинуть из стека
//4 - нет открывающий скобки
//5 - нет закрывающий скобки
//9 - победа

void foo(char* outstr, const char* instr, int& i, int& j, Values& V);
#endif
