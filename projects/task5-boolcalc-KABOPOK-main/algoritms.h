
#ifndef algoritms
#define algoritms
#include <iostream>
#include <vector>
#include <cstring>

bool isItComst(int* M, int ell, int indx);
void replacer_1(const char* Iblock, char* Oblock);
void replacer_2(char* Iblock, char* Oblock);
char classL(int** box, int wight, int hight);

void ChooseSort(char* M, std::vector<int>& V, int n);
void classM(const char* M, int n, bool& b, int basis);
void classS(const char* M, int n, bool& b);
void ChooseSortM(std::vector<int>& M, int n);
void ChooseSortM2(std::vector<int>& M, char* str, int n);
int getNumber(char* str, int& i);
void putNumber(char* str, int n, int& i);
void putNumber(std::string& str, int& n);

int inplication(int a, int b);
void fooo(std::ifstream& inFile, std::ofstream& outFile);
#endif
