#include "structures.h"
void swap(int ch, char* M) {
	char tmp = M[ch];
	for (int i = ch; i > 0; --i) {
		M[i] = M[i - 1];
	}
	M[0] = tmp;
}
int findIndx(int ch, const char* M) {
	for (int i = 0; i < 256; ++i) {
		if (M[i] == (char)ch) {
			return i;
		}
	}
	return -1;
}
void MTC(std::ifstream& inFile, std::ofstream& outFile) {
	char M[256]{ 0 };
	for (int i = 0; i < 256; ++i) {
		M[i] = (char)i;
	}
	int ch = 0;
	int buff = 0;
	buff = inFile.get();
	outFile << (char)buff;
	swap(buff, M);
	while ((ch = inFile.get()) != EOF) {
		if (ch == buff) { outFile << (char)0; }
		else {
			buff = ch;
			int f = findIndx(ch, M);
			outFile << (char)f;
			swap(f, M);
		}
	}
}
void deMTC(std::ifstream& inFile, std::ofstream& outFile) {
	//98 98 110 1 1 1 0 0
//bananaaa
	char M[256]{ 0 };
	for (int i = 0; i < 256; ++i) {
		M[i] = (char)i;
	}
	int ch = 0;
	ch = inFile.get();
	outFile << M[ch];
	swap(ch, M);
	while ((ch = inFile.get()) != EOF) {
		outFile << M[ch];
		swap(ch, M);
	}
}

//new rate

void swap(char* M_1, char* M_2, int ch) {

	for (int i = 0; i < M_2[ch]; ++i) {
		M_1[M_2[ch] - i] = M_1[M_2[ch] - 1 - i];
		++M_2[M_1[M_2[ch] - 1 - i]];
	}
	M_1[0] = (char)ch;
	M_2[ch] = 0;
}

void newMTC(std::ifstream& inFile, std::ofstream& outFile) {
	int ch = 0;
	int buff = 0;
	char M_1[256]{ 0 };
	char M_2[256]{ 0 };
	for (int i = 0; i < 256; ++i) {
		M_1[i] = (char)i;
		M_2[i] = (char)i;
	}
	ch = inFile.get();
	outFile << (char)ch;
	buff = ch;
	swap(M_1, M_2, ch);
	while ((ch = inFile.get()) != EOF) {
		if (ch == buff) { outFile << (char)0; }
		else {
			outFile << (char)M_2[ch];
			swap(M_1, M_2, ch);
			buff = ch;
		}
	}
}