#include "algoritms.h"
#include "boolexpr.h"
//#include "nodes.h"
void replacer_1(const char* Iblock, char* Oblock) {

	int j = 0;
	for (int i = 0; i < strlen(Iblock);) {
		if (Iblock[i] == '~') {
			++i;
			Oblock[j] = '(';
			++j;
			Oblock[j] = '1';
			++j;
			Oblock[j] = '+';
			++j;
			for (; (Iblock[i] != '&' && Iblock[i] != 0); ++i) {
				Oblock[j] = Iblock[i];
				++j;
			}
			Oblock[j] = ')';
			++j;
		}
		else {
			Oblock[j] = Iblock[i];
			++j;
			++i;
		}
	}
}
int getNumber(char* str, int&i) {
	int number = 0;
	int d = 0;
	for (int o = (int)strlen(str); o > i; --o) {
		number += (int)((str[o - 1] - '0') * pow(10, d));
		++d;
	}
	return number;
}
void putNumber(char* str, int n, int &i) {
	int size = 0;
	int cpyN = n;
	n /= 10;
	while (n!=0) {
		n /= 10;
		++size;
	}
	while (size >= 0) {
		int demin = (int)pow(10, size);
		str[i] = char(cpyN / demin + '0');
		cpyN %= demin;
		--size;
		++i;
	}
}
void putNumber(std::string& str, int& n) {
	int size = 0;
	int cpyN = n;
	n /= 10;
	while (n!=0) {
		n /= 10;
		++size;
	}
	while (size >= 0) {
		int demin = (int)pow(10, size);
		str.push_back(char(cpyN / demin + '0'));
		cpyN %= demin;
		--size;
	}
}

void replacer_2(char* Iblock, char* Oblock) {
	bool skoba = true;
	int i = 0;
	int j = 0;
	while (skoba) {
		skoba = false;
		for (int i = 0; i < strlen(Iblock);) {
			if (Iblock[i] == '(') {
				skoba = true;
				char value[8]{ 0 };
				i += 3;
				for (int v = 0; Iblock[i] != ')'; ++i, ++v) {
					value[v] = Iblock[i];
				}
				if (Iblock[i + 1] == '&') {
					i += 2;
					int back = 0;
					while ((Iblock[i] != 0 && Iblock[i] != '+') || (Iblock[i] == '+' && Iblock[i - 1] == '1' && Iblock[i - 2] == '(')) {
						Oblock[j] = Iblock[i];
						++j;
						++i;
						++back;
					}
					Oblock[j] = '+';
					++j;
					i -= back;
					back = 0;
					while ((Iblock[i] != 0 && Iblock[i] != '+') || (Iblock[i] == '+' && Iblock[i - 1] == '1' && Iblock[i - 2] == '(')) {
						Oblock[j] = Iblock[i];
						++j;
						++i;
						++back;
					}
					Oblock[j] = '&';
					++j;
					for (int v = 0; v < strlen(value); ++v) {
						Oblock[j] = value[v];
						++j;
					}
					if (Iblock[i] == '+') {
						Oblock[j] = '+';
						++j;
					}
					if (Iblock[i] != 0 && Iblock[i] != '+') {
						Oblock[j] = Iblock[i];
						++j;
						i -= back;
					}
				}
				else {
					Oblock[j] = '1';
					++j;
					Oblock[j] = '+';
					++j;
					for (int v = 0; v < strlen(value); ++v) {
						Oblock[j] = value[v];
						++j;
					}
					/*++i;
					while (Iblock[i] != ')' ) {
						Oblock[j] = Iblock[i];
						++j;
						++i;
					}*/
					if (Iblock[i + 1] == '+') {
						Oblock[j] = '+';
						++j;
					}
				}

			}
			else { ++i; }
		}
		if (skoba) {
			char* tmp = Oblock;
			Oblock = Iblock;
			Iblock = tmp;
			for (int i = 0; Oblock[i] != 0; ++i) {
				Oblock[i] = 0;
			}
			j = 0;
		}
	}
}
bool isItComst(int* M, int ell, int indx) {
	M[indx] = ell;
	if (indx == 0) { return true; }
	return M[indx] == M[indx - 1];
}
void ChooseSort(char* M, std::vector<int>& V, int n) {
	for (int step = 0; step < n - 1; ++step) {
		int minimumIndex = step;
		for (int i = minimumIndex + 1; i < n; ++i) {
			if (M[i] < M[minimumIndex]) {
				minimumIndex = i;
			}
		}
		if (step < minimumIndex) {
			std::swap(M[step], M[minimumIndex]);
			std::swap(V[step], V[minimumIndex]);
		}
	}
}
char classL(int** box, int wight, int hight) {
	for (int i = 1; i < hight; ++i) {
		int counter = 0;
		if (box[wight][i] > 0) {
			for (int j = 0; j < wight; ++j) {
				counter += box[j][i];
			}
			if (counter > 1) { return 0; }
		}
	}
	return 1;
}
void classM(const char* M, int n, bool& b, int basis) {
	int j = 1;
	int interval = 1;
	while (j <= basis) {
		int from = 0;
		int to = interval;
		while (to <= n) {
			for (int i = from; i < to; ++i) {
				if (M[i] > M[i + interval]) { b = false; }
			}
			from += 2 * interval;
			to += 2 * interval;
		}
		++j;
		interval *= 2;
	}
}
void classS(const char* M, int n, bool& b) {
	int i = n / 2 - 1;
	int j = n / 2;
	for (; i != 0; ++j, --i) {
		if (M[i] == M[j]) { b = false; }
	}
}
void ChooseSortM(std::vector<int>& M, int n) {
	for (int step = 0; step < n - 1; ++step) {
		int minimumIndex = step;
		for (int i = minimumIndex + 1; i < n; ++i) {
			if (M[i] < M[minimumIndex]) {
				minimumIndex = i;
			}
		}
		if (step < minimumIndex) {
			std::swap(M[step], M[minimumIndex]);
		}
	}
}
void ChooseSortM2(std::vector<int>& M, char* str, int n) {
	for (int step = 0; step < n - 1; ++step) {
		int minimumIndex = step;
		for (int i = minimumIndex + 1; i < n; ++i) {
			if (M[i] < M[minimumIndex]) { minimumIndex = i; }
		}
		if (step < minimumIndex) {
			std::swap(M[step], M[minimumIndex]);
			std::swap(str[step], str[minimumIndex]);
		}
	}
}
int inplication(int a, int b) {
	if (a == 1 && b == 0) { return 0; }
	return 1;
}
bool help() {
	std::cout << "-(command) input_file output_file" << std::endl;
	std::cout << "choose command: " << std::endl;
	std::cout << "command -z: writes the zhegalkin polynomial form input_file to output_file" << std::endl;
	std::cout << "command -i: checks the system for completeness from input_file to output_file" << std::endl;
	std::cout << "command -c: writes the CKNF form from input_file to output_file" << std::endl;
	std::cout << "command -d: writes the CDNF form from input_file to output_file" << std::endl;
	return true;
}
void fooo(std::ifstream& inFile, std::ofstream& outFile) {
	char tablet[8]{ 0 };
	char expression[256]{ 0 };
	int indx = 0;
	char ch = 0;
	while (inFile.getline(expression, 256)) {
		//truth table
		char conditions[8]{ 0 };
		int j = 0;
		BooleanExpression F(expression);
		int amountVal = F.V.amountVal;
		int counter = 0;
		int bound = (int)pow(2, F.V.amountVal);
		char* answers = new char[bound + 9]{ 0 };
		std::string buff;
		int b = 0;

		//is it const?
		int* constant = new int[bound + 9]{ 0 };
		bool cnst = true;
		int result = 0;
		while (counter != bound && cnst) {
			char* str = new char[F.V.amountVal + 9]{ 0 }; //                       memory
			int j = 0;
			for (int i = F.V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> j & 1) + '0');
				++j;
			}
			F.setBoolean(str);
			result = F.calc();
			if (isItComst(constant, result, counter)) {}
			else { cnst = false; }
			++counter;
			delete[] str;
		}
		counter = 0;
		delete[] constant;
		if (cnst) {
			if (result == 1) {
				++tablet[1];
				++tablet[2];
				++tablet[3];
				++tablet[5];
			}
			else {
				++tablet[0];
				++tablet[2];
				++tablet[3];
				++tablet[5];
			}
			delete[] answers;
			continue;
		}
		while (counter != bound) {
			char* str = new char[F.V.amountVal + 9]{ 0 }; //                       memory
			int p = 0;
			for (int i = F.V.amountVal - 1; i >= 0; --i) {
				str[i] = (char)((counter >> p & 1) + '0');
				++p;
			}
			F.setBoolean(str);
			int result = F.calc();
			if (counter == 0 && result == 0) {
				conditions[0] = 1;
			}
			if (counter + 1 == bound) {
				conditions[1] = (char)result;
			}
			answers[j] = (char)result;
			if (result == 1) {
				//pairM strM(str);
				ChooseSort(str, F.V.SortValues, (int)strlen(str));                          //////////////sort problem
				for (int k = 0; k < F.V.amountVal; ++k) {
					if (str[k] == '0') {
						if (k + 1 == F.V.amountVal) {
							buff.push_back('~');
							++b;
							buff.push_back('x');
							++b;
							buff.push_back((char)(F.V.SortValues[k] + '0'));
							++b;
							buff.push_back(' ');
							++b;
							buff.push_back('V');
							++b;
							buff.push_back(' ');
							++b;
						}
						else {
							buff.push_back('~');
							++b;
							buff.push_back('x');
							++b;
							buff.push_back((char)(F.V.SortValues[k] + '0'));
							++b;
							buff.push_back('&');
							++b;
						}
					}
					else {
						if (k + 1 == F.V.amountVal) {
							buff.push_back('x');
							++b;
							buff.push_back((char)(F.V.SortValues[k] + '0'));
							++b;
							buff.push_back(' ');
							++b;
							buff.push_back('v');
							++b;
							buff.push_back(' ');
							++b;
						}
						else {
							buff.push_back('x');
							++b;
							buff.push_back((char)(F.V.SortValues[k] + '0'));
							++b;
							buff.push_back('&');
							++b;
						}
					}
				}
				F.V.SendFlying();
			}
			++counter;
			delete[] str;
			++j;
		}
		{
			buff[buff.size() - 1] = '\0';
			buff[buff.size() - 2] = '\0';
			buff[buff.size() - 3] = '\0';

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
						char num[4]{ 0 };
						int a = 0;
						while (ch >= '0' && ch <= '9') {
							num[a] = (char)ch;
							++indx;
							ch = (int)(unsigned char)outBuff[indx];
							++a;
						}
						for (int d = 0; d < strlen(num); ++d) {
							number += (int)((num[d] - '0') * pow(10, d));
							++d;
						}
						str[F.V.findInd(number)] = 1;
						//number = 0;
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
			int amount_v = 0;
			for (int i = 0; i < place; ++i) {
				counter[amountVal][i] %= 2;
				if (counter[amountVal][i] != 0) { ++amount_v; }
			}

			conditions[2] = classL(counter, amountVal, place);
			for (int i = 0; i < amountVal + 1; ++i) {
				delete[] counter[i];
			}
			delete[] counter;
			//end
		}

		//post
		if (answers[0] == 0 || answers[bound - 1] == 1) {
			if (answers[0] == 1) { conditions[1] = 1; conditions[0] = 0; }
			else { conditions[1] = 0; conditions[0] = 1; }
		}
		else { conditions[1] = 0; conditions[0] = 0; }
		cnst = true;
		classM(answers, bound, cnst, amountVal);
		if (cnst) { conditions[3] = 1; }
		classS(answers, bound, cnst);
		if (cnst) { conditions[4] = 1; }
		for (int i = 0; i < 5; ++i) {
			tablet[i] = (char)(tablet[i] + conditions[i]);
		}
		++tablet[5];
		delete[] answers;
	}
	bool full = true;
	for (int i = 0; i < 5; ++i) {
		if (tablet[i] == tablet[5]) { outFile << "no"; full = false; break; }
	}
	if (full) { outFile << "yes"; }
}
