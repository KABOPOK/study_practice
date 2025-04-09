#include <string>
#include"gtest/gtest.h"
#include "boolexpr.h"
#include "algoritms.h"
bool help();
int main(int argc, const char* argv[])
{
	bool conk = false;
	bool dizk = false;
	bool zglk = false;
	bool isll = false;
	bool turn_down = false;
	switch (argv[1][1])
	{//cdzih?
	case'c':
		conk = true;
		break;
	case'd':
		dizk = true;
		break;
	case'i':
		isll = true;
		break;
	case'z':
		zglk = true;
		break;
	case'h':
	case'?':
		turn_down = help();
		break;
	default:
		turn_down = help();
	}

	if (argc > 4) {
		help();
		return 0;
	}

	if (turn_down) { return 0; }

	if (conk) {

		std::ifstream inFile(argv[2]);
		std::ofstream outFile(argv[3]);
		try {
		if (!inFile) { inFile.close(); outFile.close(); help(); }
		if (!outFile) { inFile.close(); outFile.close(); help(); }

		char mycop[256]{ 0 };
		while (inFile.getline(mycop, 256)) {
			BooleanExpression F(mycop);
			int counter = 0;
			int bound = (int)pow(2, F.V.amountVal);
			char buff[126]{ 0 };

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
				if (inFile.peek() == EOF) { outFile << result; }
				else { outFile << result << std::endl; }
				continue;
			}

			while (counter != bound) {
				int b = 0;
				char* str = new char[F.V.amountVal + 9]{ 0 }; //                       memory
				int j = 0;
				for (int i = F.V.amountVal - 1; i >= 0; --i) {
					str[i] = (char)((counter >> j & 1) + '0');
					++j;
				}
				F.setBoolean(str);
				result = F.calc();
				if (result == 0) {
					F.V.sort(str);
					if (buff[0] != 0) {
						outFile << buff;
						for (int i = 0; buff[i] != 0; ++i) { buff[i] = 0; }
					}
					outFile << "(";
					for (int k = 0; k < F.V.amountVal; ++k) {
						if (str[k] == '1') {
							if (k + 1 == F.V.amountVal) {
								buff[b] = '~';
								++b;
								buff[b] = 'x';
								++b;
								buff[b] =(char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = ')';
								++b;
								buff[b] = ' ';
								++b;
								buff[b] = '&';
								++b;
								buff[b] = ' ';
								++b;
							}
							else {
								buff[b] = '~';
								++b;
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = 'v';
								++b;
							}
						}
						else {
							if (k + 1 == F.V.amountVal) {
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = ')';
								++b;
								buff[b] = ' ';
								++b;
								buff[b] = '&';
								++b;
								buff[b] = ' ';
								++b;
							}
							else {
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = 'v';
								++b;
							}
						}
					}
					F.V.SendFlying();
				}
				++counter;
				delete[] str;
			}
			if (inFile.peek() == EOF) {
				for (int i = 0; i < strlen(buff) - 3; ++i) {
					outFile << buff[i];
				}
			}
			else {
				for (int i = 0; i < strlen(buff) - 3; ++i) {
					outFile << buff[i];
				}
				outFile << std::endl;
			}
		}
		}
		catch (const Error& error) {
			outFile << "error";
			std::cout << "Error. " << error.what() << std::endl;
			inFile.close();
			outFile.close();
		}
		inFile.close();
		outFile.close();
	}

	if (dizk) {
		std::ifstream inFile(argv[2], std::ios_base::binary);
		std::ofstream outFile(argv[3]);
		try {
		if (!inFile) { inFile.close(); outFile.close(); help(); }
		if (!outFile) { inFile.close(); outFile.close(); help(); }

		char mycop[256]{ 0 };
		while (inFile.getline(mycop, 256)) {
			BooleanExpression F(mycop);
			int counter = 0;
			int bound = (int)pow(2, F.V.amountVal);
			char buff[126]{ 0 };

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
				if (inFile.peek() == EOF) { outFile << result; }
				else { outFile << result << std::endl; }
				continue;
			}

			while (counter != bound) {
				char* str = new char[F.V.amountVal + 9]{ 0 };
				int b = 0;
				int j = 0;
				for (int i = F.V.amountVal - 1; i >= 0; --i) {
					str[i] = (char)((counter >> j & 1) + '0');
					++j;
				}
				F.setBoolean(str);
				int result = F.calc();

				if (result == 1) {
					F.V.sort(str);
					if (buff[0] != 0) {
						outFile << buff;
						for (int i = 0; buff[i] != 0; ++i) { buff[i] = 0; }
					}
					buff[b] = '(';
					++b;
					for (int k = 0; k < F.V.amountVal; ++k) {
						if (str[k] == '0') {
							if (k + 1 == F.V.amountVal) {
								buff[b] = '~';
								++b;
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = ')';
								++b;
								buff[b] = ' ';
								++b;
								buff[b] = 'v';
								++b;
								buff[b] = ' ';
								++b;
							}
							else {
								buff[b] = '~';
								++b;
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = '&';
								++b;
							}
						}
						else {
							if (k + 1 == F.V.amountVal) {
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = ')';
								++b;
								buff[b] = ' ';
								++b;
								buff[b] = 'v';
								++b;
								buff[b] = ' ';
								++b;
							}
							else {
								buff[b] = 'x';
								++b;
								buff[b] = (char)(F.V.SortValues[k] + '0');
								++b;
								buff[b] = '&';
								++b;
							}
						}
					}
					F.V.SendFlying();
				}
				++counter;
				delete[] str;
			}
			if (inFile.peek() == EOF) {
				for (int i = 0; i < strlen(buff) - 3; ++i) {
					outFile << buff[i];
				}
			}
			else {
				for (int i = 0; i < strlen(buff) - 3; ++i) {
					outFile << buff[i];
				}
				outFile << std::endl;
			}
		}
		}
		catch (const Error& error) {
			outFile << "error";
			std::cout << "Error. " << error.what() << std::endl;
			inFile.close();
			outFile.close();
		}
		inFile.close();
		outFile.close();
	}

	if (zglk) {
		std::ifstream inFileTocop(argv[2], std::ios_base::binary);
		std::ofstream outFileM(argv[3]);

		if (!inFileTocop) { inFileTocop.close(); outFileM.close(); help(); }
		if (!outFileM) { inFileTocop.close(); outFileM.close(); help(); }
		try {
			int amountVal = 0;
			bool end = false;
			char mycop[256]{ 0 };
			while (inFileTocop.getline(mycop, 256)) {
				BooleanExpression F(mycop);
				int counter = 0;
				amountVal = F.V.amountVal;
				int bound = (int)pow(2, F.V.amountVal);
				std::string buff;

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
					if (inFileTocop.peek() == EOF) { outFileM << result; }
					else { outFileM << result << std::endl; }
					continue;
				}

				int b = 0;
				while (counter != bound) {
					char* str = new char[F.V.amountVal + 9]{ 0 };
					int j = 0;
					for (int i = F.V.amountVal - 1; i >= 0; --i) {
						str[i] = (char)((counter >> j & 1) + '0');
						++j;
					}
					F.setBoolean(str);
					int result = F.calc();
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
									buff.push_back('v');
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
									number += int((num[d] - '0') * pow(10, d));
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
					char* newStr = new char[static_cast<unsigned long>(place * place * 4)]{ 0 };
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
							for (int j = 0; j < amountVal; ++j) {
								if (counter[j][i] == 1) { ++amount; }
							}
							for (int j = 0; j < amountVal; ++j) {
								if (counter[j][i] == 1) {
									if (amount - 1 == 0) {
										newStr[indx] = 'x';
										++indx;
										newStr[indx] = (char)(F.V.SortValues[j] + '0');
										++indx;
									}
									else {
										newStr[indx] = 'x';
										++indx;
										newStr[indx] = (char)(F.V.SortValues[j] + '0');
										++indx;
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
					if (newStr[indx - 1] == ' ') { newStr[indx - 1] = 0; newStr[indx - 2] = 0; newStr[indx - 3] = 0; }
					outFileM << newStr;
					delete[] counter;
					delete[] newStr;
					//end
				}
				if (inFileTocop.peek() == EOF) {}
				else { outFileM << std::endl; }
			}
			inFileTocop.close();
			outFileM.close();
			if (end) { return 0; }
		}
		catch (const Error& error) {
			outFileM << "error";
			std::cout << "Error. " << error.what() << std::endl;
			inFileTocop.close();
			outFileM.close();
		}
	}

	if (isll) {
		std::ifstream inFile(argv[2]);
		std::ofstream outFile(argv[3]);
		if (!inFile) { inFile.close(); outFile.close(); help(); }
		if (!outFile) { inFile.close(); outFile.close(); help(); }
		try {
			fooo(inFile, outFile);
		}
		catch (const Error& error) {
			outFile << "error";
			std::cout << "Error. " << error.what() << std::endl;
			inFile.close();
			outFile.close();
		}
	}
	return 0;
}
