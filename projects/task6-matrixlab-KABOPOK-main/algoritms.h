#ifndef ALGORITMS
#define ALGORITMS
#include "Value.h"
#include <vector>
#include <stack>
#include <fstream>
void makePlusOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal);
void makeMultiplicationOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal);
void makeDivisionOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal);
void makeSubtractionOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal);

#endif 

