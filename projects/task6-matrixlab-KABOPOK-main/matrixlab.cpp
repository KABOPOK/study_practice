#include "Value.h"
#include "algoritms.h"
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

void throwOutTheTrash(int begin, int end, std::string& local, char* expression) {
	int l = 0;
	for (int j = begin; j < begin + local.size(); ++j, ++l) {
		expression[j] = (char)local[l];
	}
	for (int j = (int)(local.size() + begin); j <= end; ++j) {
		expression[j] = 0;
	}
}

int FindLocalValue(std::vector<Value> box, Value a) {
	for (int i = 0; i < box.size(); ++i) {
		if (strcmp(box[i].getName(), a.getName()) == 0) {
			return i;
		}
	}
	return -1;
}
int FindGlobalValue(std::vector<Value> box, Value a) {
	for (int i = 0; i < box.size(); ++i) {
		if (strcmp(box[i].getName(), a.getName()) == 0) {
			return i;
		}
	}
	return -1;
}
int getNumber(const char* str) {
	int i = 0;
	while (!(str[i] >= '0' && str[i] <= '9')) {
		++i;
	}
	int number = 0;
	int d = 0;
	for (int o = strlen(str); o > i; --o) {
		number += (int)((str[o - 1] - '0') * pow(10, d));
		++d;
	}
	return number;
}
fraction getFrac(const char* value, std::vector<Value> globalValues, std::vector<Value> localValues) {
	fraction num = 0;
	if (value[0] >= '0' && value[0] <= '9') {
		num = fraction(getNumber(value));
	}
	else if (value[0] == '~') {
		num = localValues[FindLocalValue(localValues, Value(value))].getFraction();
	}
	else {
		num = globalValues[FindGlobalValue(globalValues, Value(value))].getFraction();
	}
	return num;
}
int getNumber(std::string str) {
	int i = 0;
	int number = 0;
	int d = 0;
	for (int o = str.size(); o > i; --o) {
		number += (int)((str[o - 1] - '0') * pow(10, d));
		++d;
	}
	return number;
}
void getValue(int& i, const char* expression, char* value) {
	int j = 0;
	while (expression[i] == ' ' || expression[i] == 0) { ++i; }
	while (expression[i] != ' ' && expression[i] != ')') {
		value[j] = expression[i];
		++i;
		++j;
	}
}

//int main() {
//	fraction a(-12600,10780);
//	fraction b(-6,7);
//	std::cout << a << " " << b<< '\n';
//	std::cout << b-a << std::endl;
//	return 0;
//}

int main(int argc, const char* argv[])
{
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);
	std::vector<Value> globalValues;
	char expression[512]{ 0 };
	while (inFile.getline(expression, 512)) {
		std::vector<Value> localValues;
		int lenght = strlen(expression);
		int i = 0;
		while (i + 1 < lenght) {
			i = 0;
			bool out = false;
			while (expression[i] != ')' && i < lenght) { ++i; }
			int end = i;
			while (expression[i] != '(' && i >= 0) { --i; }
			int begin = i;
			// (... )
			for (i = begin + 1; expression[i] == ' ' || expression[i] == ')'; ++i) {}
			char operation[512]{ 0 };
			for (int j = 0; expression[i] != ' '; ++i, ++j) { operation[j] = expression[i]; }
			// (?.. )

			//problem with unar/binar -
			bool unar = false;
			for (int j = begin; j < end; ++j) {
				if (expression[j] == ' ') { unar = !unar; }
			}

			if (strlen(operation) == 1 && !unar) {
				// (bin ? ? )
				char firstVal[512]{ 0 };
				fraction firstFrac(bigZero, bigOne);
				bool fLocal = false;
				char secondVal[512]{ 0 };
				fraction secondFrac(bigZero, bigOne);
				bool sLocal = false;
				int fIndx = -1;
				int sIndx = -1;
				// (... ? ...)
				while (expression[i] == ' ') { ++i; }
				for (int j = 0; expression[i] != ' '; ++i, ++j) { firstVal[j] = expression[i]; }
				if (firstVal[0] >= '0' && firstVal[0] <= '9') {
					firstFrac = getNumber(firstVal);
				}
				else {
					//local or not
					if (firstVal[0] >= '~') {
						fLocal = true;
						fIndx = getNumber(firstVal);
					}
					else {
						Value b(firstVal);
						fIndx = FindGlobalValue(globalValues, b);
					}
				}
				// (... ... ?)
				int j = 0;
				while (expression[i] == ' ') { ++i; }
				for (; expression[i] != ' ' && expression[i] != ')'; ++i, ++j) { secondVal[j] = expression[i]; }
				if (secondVal[0] >= '0' && secondVal[0] <= '9') {
					secondFrac = getNumber(secondVal);
				}
				else {
					//local or not
					if (secondVal[0] >= '~') {
						sLocal = true;
						sIndx = getNumber(secondVal);
					}
					else {
						Value b(secondVal);
						sIndx = FindGlobalValue(globalValues, b);
					}
				}
				//( ? ... ...)
				switch (operation[0])
				{
				case'+':
					makePlusOperation(expression, begin, end, firstFrac, secondFrac, globalValues, localValues, fIndx, sIndx, fLocal, sLocal);
					break;
				case'-':
					makeSubtractionOperation(expression, begin, end, firstFrac, secondFrac, globalValues, localValues, fIndx, sIndx, fLocal, sLocal);
					break;
				case'*':
					makeMultiplicationOperation(expression, begin, end, firstFrac, secondFrac, globalValues, localValues, fIndx, sIndx, fLocal, sLocal);
					break;
				case'/':
					makeDivisionOperation(expression, begin, end, firstFrac, secondFrac, globalValues, localValues, fIndx, sIndx, fLocal, sLocal);
					break;
				case'=':
					if (sIndx == -1) {
						globalValues.push_back(Value(secondFrac, firstVal));
					}
					else if (sLocal) {
						if (localValues[sIndx].getType()) { globalValues.push_back(Value(localValues[sIndx].getMatrix(), firstVal)); }
						else { globalValues.push_back(Value(localValues[sIndx].getFraction(), firstVal)); }
					}
					else {
						if (globalValues[sIndx].getType()) { globalValues.push_back(Value(globalValues[sIndx].getMatrix(), firstVal)); }
						else { globalValues.push_back(Value(globalValues[sIndx].getFraction(), firstVal)); }
					}
					break;
				default:
					break;
				}
			}
			else {
				//(? ....)
				while (expression[i] == ' ') { ++i; }
				if (strcmp(operation, "disp") == 0) {
					char value[512]{ 0 };
					for (int j = 0; expression[i] != ' ' && expression[i] != ')'; ++i, ++j) { value[j] = expression[i]; }
					if (value[0] == '~') {
						int index = getNumber(value);
						if (localValues[index].getType()) { outFile << "ans = [" << std::endl << localValues[index].getMatrix() << ']' << std::endl; }
						else { outFile << "ans = " << localValues[index].getFraction() << std::endl; }
					}
					else {
						int index = FindGlobalValue(globalValues, value);
						if (globalValues[index].getType()) { outFile << globalValues[index].getName() << " = [" << std::endl << globalValues[index].getMatrix() << ']' << std::endl; }
						else { outFile << globalValues[index].getName() << " = " << globalValues[index].getFraction() << std::endl; }
					}
					out = true;
				}
				else if (strcmp(operation, ".*") == 0) {
					char value_1[512]{ 0 };
					Matrix matrix_1 = 0;
					getValue(i, expression, value_1);
					char value_2[512]{ 0 };
					Matrix matrix_2 = 0;
					getValue(i, expression, value_2);
					int i_1 = FindLocalValue(localValues, Value(value_1));
					if (i_1 != -1) { matrix_1 = localValues[i_1].getMatrix(); }
					else { matrix_1 = globalValues[FindGlobalValue(globalValues, Value(value_1))].getMatrix(); }
					int i_2 = FindLocalValue(localValues, Value(value_2));
					if (i_2 != -1) { matrix_2 = localValues[i_2].getMatrix(); }
					else { matrix_2 = globalValues[FindGlobalValue(globalValues, Value(value_2))].getMatrix(); }
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, matrix_1.Multiplication(matrix_2)));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "./") == 0) {
					char value_1[512]{ 0 };
					Matrix matrix_1 = 0;
					getValue(i, expression, value_1);
					char value_2[512]{ 0 };
					Matrix matrix_2 = 0;
					getValue(i, expression, value_2);
					int i_1 = FindLocalValue(localValues, Value(value_1));
					if (i_1 != -1) { matrix_1 = localValues[i_1].getMatrix(); }
					else { matrix_1 = globalValues[FindGlobalValue(globalValues, Value(value_1))].getMatrix(); }
					int i_2 = FindLocalValue(localValues, Value(value_2));
					if (i_2 != -1) { matrix_2 = localValues[i_2].getMatrix(); }
					else { matrix_2 = globalValues[FindGlobalValue(globalValues, Value(value_2))].getMatrix(); }
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, matrix_1.Division(matrix_2)));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "-") == 0) {
					char value[512]{ 0 };
					getValue(i, expression, value);
					std::string local(('~') + std::to_string(localValues.size()));
					if (value[0] == '~') {
						int index = getNumber(value);
						if (localValues[index].getType()) { localValues.push_back(Value(local, -(localValues[index].getMatrix()))); }
						else { localValues.push_back(Value(local, -(localValues[index].getFraction()))); }
					}
					else {
						int index = FindLocalValue(globalValues, Value(value));
						if (globalValues[index].getType()) { localValues.push_back(Value(local, -(globalValues[index].getMatrix()))); }
						else { localValues.push_back(Value(local, -(globalValues[index].getFraction()))); }
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "zeros") == 0) {
					char value_1[512]{ 0 };
					getValue(i, expression, value_1);
					fraction num_1 = getFrac(value_1, globalValues, localValues);
					char value_2[512]{ 0 };
					getValue(i, expression, value_2);
					fraction num_2 = getFrac(value_2, globalValues, localValues);
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, Matrix('z', getNumber(to_string(num_1.getBigInteger())), getNumber(to_string(num_2.getBigInteger())))));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "ones") == 0) {
					char value_1[512]{ 0 };
					getValue(i, expression, value_1);
					fraction num_1 = getFrac(value_1, globalValues, localValues);
					char value_2[512]{ 0 };
					getValue(i, expression, value_2);
					fraction num_2 = getFrac(value_2, globalValues, localValues);
					std::string local(('~') + std::to_string(localValues.size()));
					Matrix tmp('o', getNumber(to_string(num_1.getBigInteger())), getNumber(to_string(num_2.getBigInteger())));
					localValues.push_back(Value(local, tmp));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "transpose") == 0) {
					char value[512]{ 0 };
					int j = 0;
					while (expression[i] != ')' && expression[i] != ' ') {
						value[j] = expression[i];
						++j;
						++i;
					}
					std::string local(('~') + std::to_string(localValues.size()));
					if (value[0] == '~') {
						int index = getNumber(value);
						localValues.push_back(Value(local, localValues[index].getMatrix().transpose()));
					}
					else {
						int index = FindGlobalValue(globalValues, Value(value));
						localValues.push_back(Value(local, globalValues[index].getMatrix().transpose()));
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "eye") == 0) {
					char value_1[512]{ 0 };
					getValue(i, expression, value_1);
					fraction num_1 = getFrac(value_1, globalValues, localValues);
					char value_2[512]{ 0 };
					getValue(i, expression, value_2);
					fraction num_2 = getFrac(value_2, globalValues, localValues);
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, Matrix('e', getNumber(to_string(num_1.getBigInteger())), getNumber(to_string(num_2.getBigInteger())))));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "linspace") == 0) {
					char value_x0[512]{ 0 };
					getValue(i, expression, value_x0);
					fraction num_x0 = getFrac(value_x0, globalValues, localValues);
					char value_xn[512]{ 0 };
					getValue(i, expression, value_xn);
					fraction num_xn = getFrac(value_xn, globalValues, localValues);
					char value_n[512]{ 0 };
					getValue(i, expression, value_n);
					fraction num_n = getFrac(value_n, globalValues, localValues);
					int n = getNumber(to_string(num_n.getBigInteger()));
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, Matrix(num_x0, num_xn, num_n, n)));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "vertcat") == 0) {
					std::vector<Matrix> MatrixList;
					for (; expression[i] != ')'; ++i) {
						char value[512]{ 0 };
						int j = 0;
						while (expression[i] != ')' && expression[i] != ' ') {
							value[j] = expression[i];
							++j;
							++i;
						}
						if (value[0] >= '0' && value[0] <= '9') {
							int num = 0;
							num = getNumber(value);
							MatrixList.push_back(Matrix(num));
						}
						else if (value[0] == '~') {
							int index = getNumber(value);
							MatrixList.push_back(localValues[index].getMatrix());
						}
						else {
							int index = FindGlobalValue(globalValues, Value(value));
							MatrixList.push_back(globalValues[index].getMatrix());
						}
						if (expression[i] == ')') { break; }
					}
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, Matrix('>', MatrixList)));
					int l = 0;
					for (int j = begin; j < begin + local.size(); ++j, ++l) {
						expression[j] = local[l];
					}
					for (int j = (int)(local.size() + begin); j <= end; ++j) {
						expression[j] = 0;
					}
				}
				else if (strcmp(operation, "horzcat") == 0) {
					std::vector<Matrix> MatrixList;
					for (; expression[i] != ')'; ++i) {
						char value[512]{ 0 };
						int j = 0;
						while (expression[i] != ')' && expression[i] != ' ') {
							value[j] = expression[i];
							++j;
							++i;
						}
						if (value[0] >= '0' && value[0] <= '9') {
							int num = 0;
							num = getNumber(value);
							MatrixList.push_back(Matrix(num));
						}
						else if (value[0] == '~') {
							int index = getNumber(value);
							MatrixList.push_back(localValues[index].getMatrix());
						}
						else {
							int index = FindGlobalValue(globalValues, Value(value));
							MatrixList.push_back(globalValues[index].getMatrix());
						}
						if (expression[i] == ')') { break; }
					}
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, Matrix('h', MatrixList)));
					int l = 0;
					for (int j = begin; j < begin + local.size(); ++j, ++l) {
						expression[j] = local[l];
					}
					for (int j = (int)(local.size() + begin); j <= end; ++j) {
						expression[j] = 0;
					}
				}
				else if (strcmp(operation, "det") == 0) {
					char value[512]{ 0 };
					std::string local(('~') + std::to_string(localValues.size()));
					getValue(i, expression, value);
					if (value[0] == '~') {
						localValues.push_back(Value(local, localValues[getNumber(value)].getMatrix().getDet()));
					}
					else {
						localValues.push_back(Value(local, globalValues[FindGlobalValue(globalValues, Value(value))].getMatrix().getDet()));
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "inv") == 0) {
					char value[512]{ 0 };
					int j = 0;
					while (expression[i] != ')' && expression[i] != ' ') {
						value[j] = expression[i];
						++j;
						++i;
					}
					std::string local(('~') + std::to_string(localValues.size()));
					if (value[0] == '~') {
						int index = getNumber(value);
						localValues.push_back(Value(local, localValues[index].getMatrix().inverse()));
					}
					else {
						int index = FindGlobalValue(globalValues, Value(value));
						localValues.push_back(Value(local, globalValues[index].getMatrix().inverse()));
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "sum") == 0) {
					char value[512]{ 0 };
					std::string local(('~') + std::to_string(localValues.size()));
					getValue(i, expression, value);
					if (value[0] == '~') {
						localValues.push_back(Value(local, localValues[getNumber(value)].getMatrix().getSum()));
					}
					else {
						localValues.push_back(Value(local, globalValues[FindGlobalValue(globalValues, Value(value))].getMatrix().getSum()));
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "prod") == 0) {
					char value[512]{ 0 };
					std::string local(('~') + std::to_string(localValues.size()));
					getValue(i, expression, value);
					if (value[0] == '~') {
						localValues.push_back(Value(local, localValues[getNumber(value)].getMatrix().getMultiplication()));
					}
					else {
						localValues.push_back(Value(local, globalValues[FindGlobalValue(globalValues, Value(value))].getMatrix().getMultiplication()));
					}
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "min") == 0) {
					char value_1[512]{ 0 };
					getValue(i, expression, value_1);
					char value_2[512]{ 0 };
					getValue(i, expression, value_2);
					Matrix one;
					Matrix two;
					if (value_1[0] == '~') { one = localValues[FindLocalValue(localValues, Value(value_1))].getMatrix(); }
					else { one = globalValues[FindGlobalValue(globalValues, Value(value_1))].getMatrix(); }
					if (value_2[0] == '~') { two = localValues[FindLocalValue(localValues, Value(value_2))].getMatrix(); }
					else { two = globalValues[FindGlobalValue(globalValues, Value(value_2))].getMatrix(); }
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, one.min(two)));
					throwOutTheTrash(begin, end, local, expression);
				}
				else if (strcmp(operation, "max") == 0) {
					char value_1[512]{ 0 };
					getValue(i, expression, value_1);
					char value_2[512]{ 0 };
					getValue(i, expression, value_2);
					Matrix one;
					Matrix two;
					if (value_1[0] == '~') { one = localValues[FindLocalValue(localValues, Value(value_1))].getMatrix(); }
					else { one = globalValues[FindGlobalValue(globalValues, Value(value_1))].getMatrix(); }
					if (value_2[0] == '~') { two = localValues[FindLocalValue(localValues, Value(value_2))].getMatrix(); }
					else { two = globalValues[FindGlobalValue(globalValues, Value(value_2))].getMatrix(); }
					std::string local(('~') + std::to_string(localValues.size()));
					localValues.push_back(Value(local, one.max(two)));
					throwOutTheTrash(begin, end, local, expression);
				}
			}
			if (out) { break; }
		}
	}


	inFile.close();
	outFile.close();
}
