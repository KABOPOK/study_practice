#include "boolexpr.h"
bool isFullSystem(const std::vector<BooleanExpression>& MathPart) {
	char tablet[8]{ 0 };
	char expression[256]{ 0 };
	int indx = 0;
	char ch = 0;
	for (int i = 0; i < MathPart.size(); ++i) {
		//truth table
		char conditions[8]{ 0 };
		int j = 0;
		BooleanExpression F(MathPart[i]);
		int amountVal = F.V.amountVal;
		int counter = 0;
		int bound = (int)pow(2, F.V.amountVal);
		char* answers = new char[bound + 9]{ 0 };
		std::string buff;
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
				ChooseSort(str, F.V.SortValues, strlen(str));                          //////////////sort problem
				for (int k = 0; k < F.V.amountVal; ++k) {
					if (str[k] == '0') {
						if (k + 1 == F.V.amountVal) {
							buff.push_back('~');
							
							buff.push_back('x');
							
							putNumber(buff, F.V.SortValues[k]);
							
							buff.push_back(' ');
							
							buff.push_back('V');
							
							buff.push_back(' ');
							
						}
						else {
							buff.push_back('~');
							
							buff.push_back('x');
							
							putNumber(buff, F.V.SortValues[k]);
							
							buff.push_back('&');
							
						}
					}
					else {
						if (k + 1 == F.V.amountVal) {
							buff.push_back('x');
							
							putNumber(buff, F.V.SortValues[k]);
							
							buff.push_back(' ');
							
							buff.push_back('v');
							
							buff.push_back(' ');
							
						}
						else {
							buff.push_back('x');
							
							putNumber(buff, F.V.SortValues[k]);
							
							buff.push_back('&');
							
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
						int d = (int)(strlen(num) - 1);
						for (int o = 0; o < strlen(num); ++o) {
							number += (int)((num[o] - '0') * pow(10, d));
							--d;
						}
						str[F.V.findInd(number)] = 1;
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
				ch = 2;
				++indx;

				delete[] str;
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
		bool cnst = true;
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
		delete[] answers;
		for (int i = 0; i < 5; ++i) {
			tablet[i] = (char)(tablet[i] + conditions[i]);
		}
		++tablet[5];
	}
	bool full = true;
	for (int i = 0; i < 5; ++i) {
		if (tablet[i] == tablet[5]) { return false; full = false; break; }
	}
	return true;
}
bool lenNum(int a, const char* M) {
	int sizeN = 0;
	while (a != 0) {
		a /= 10;
		++sizeN;
	}
	return strlen(M) + 1 == sizeN;



}
bool operator== (const BooleanExpression& X, const char* str) {
	return X.isEqual(str);
}
int actionsRowNumber(char ch) {
	switch (ch) {
	case 0: return 0;
	case '~': return 1;
	case '&': return 2;
	case 'v': return 3;
	case '+': return 4;
	case '|': return 5;
	case '^': return 6;
	case '>': return 7;
	case '<': return 8;
	case '=': return 9;
	}
	return 10;
}
//--------------------------------------------------------
int actionColNumber(char ch) {
	switch (ch) {
	case 0: return 0;
	case '~': return 1;
	case '&': return 2;
	case 'v': return 3;
	case '+': return 4;
	case '|': return 5;
	case '^': return 6;
	case '>': return 7;
	case '<': return 8;
	case '=': return 9;
	case '(': return 10;
	case ')': return 11;
	}
	if (ch == 'x') { return 12; }
	if (ch == 'y' || ch == 'z') { return 99; }
	return 100;
}
FormulaNode* BooleanExpression::Postfix2Tree(const char* str) {
	int index = 0; // Индекс элемента во входной строке
	std::stack<FormulaNode*> S;
	char ch;
	int i = 0;
	FormulaNode* result;
	FormulaNode* left;
	FormulaNode* right;
	try {
		while ((ch = str[index]) != 0) {
			left = right = nullptr;
			switch (ch) {
			case '&':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; } left = S.top(); S.pop();
				result = new ConjunctionNode(left, right);
				break;
			case 'v':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new DisjunctionNode(left, right);
				break;
			case '+':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new ExclusiveOrNode(left, right);
				break;
			case '|':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new ShepherStrokeNode(left, right);
				break;
			case '^':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new NeedleNode(left, right);
				break;
			case '>':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new RInplicationNode(left, right);
				break;
			case '<':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new LInplicationNode(left, right);
				break;
			case '=':
				if (S.empty()) { throw 1; }	right = S.top(); S.pop();
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new EquivalenceNode(left, right);
				break;
			case '~':
				if (S.empty()) { throw 1; }	left = S.top(); S.pop();
				result = new DenialNode(left);
				break;
			default:
				if (ch == 'x') {
					Values* c = &V;
					while (str[index + 1] >= '0' && str[index + 1] <= '9') {
						++index;
					}
					/*char num[4]{ 0 };
					int i = 0;
					while (str[index + 1] >= '0' && str[index + 1] <= '9' && lenNum(index+1, num)) {
						num[i] = str[index + 1];
						++index;
						++i;
					}
					int number = 0;
					int d = 0;
					for (int o = strlen(num); o > 0; --o) {
						number += (num[d] - '0') * pow(10, d);
						++d;
					}*/
					result = new ParamNode(V.values[i], c);
					++i;
				}
				else {
					if (ch == 'y') { result = new NumNode(1); }
					else { result = new NumNode(0); }
				}
				//while (str[index+1] >= '0' && str[index+1] <= '9') { ++index; }
			}
			S.push(result);
			++index;
		}
		if (S.size() > 1) {
			left = right = nullptr;
			throw 2;
		}
		result = S.top();
		return result;
	}
	catch (int error) {
		//if (left) delete left;
		//if (right) delete right;
		while (!S.empty()) {
			left = S.top();
			S.pop();
			delete left;
		}
		throw ErrorPostfix(str, index);
	}
}
const unsigned char ActionsTable[][13] = {
	//    0 ~ & V + | ^ > < = ( ) A
	/*0*/{9,2,2,2,2,2,2,2,2,2,2,4,1},
	/*~*/{3,2,3,3,3,3,3,3,3,3,2,3,1},
	/*&*/{3,2,3,3,3,3,3,3,3,3,2,3,1},
	/*V*/{3,2,2,3,3,3,3,3,3,3,2,3,1},
	/*+*/{3,2,2,3,3,3,3,3,3,3,2,3,1},
	/*|*/{3,2,2,2,2,3,3,3,3,3,2,3,1},
	/*^*/{3,2,2,2,2,2,3,3,3,3,2,3,1},
	/*>*/{3,2,2,2,2,2,2,3,3,3,2,3,1},
	/*<*/{3,2,2,2,2,2,2,3,3,3,2,3,1},
	/*=*/{3,2,2,2,2,2,2,2,2,3,2,3,1},
	/*(*/{5,2,2,2,2,2,2,2,2,2,2,4,1}
};
void BooleanExpression::Infix2Postfix(const char* instr, char* outstr) {
	int i = 0; // индекс во входной строке
	int j = 0; // индекс в выходной строке
	int row = 0; 
	int col = 0;
	unsigned char action = 0;
	std::stack<char> S;
	do {
		col = actionColNumber(instr[i]);

		if (col == 12) {
			if (!(instr[i + 1] >= '0' && instr[i + 1] <= '9')) {
				//no numeral after value
				throw ErrorUnknownOperation(instr[i]);
			}
		}
		if (col == 99) { outstr[j] = instr[i]; ++j; ++i; continue; }
		if (col == 100) { throw ErrorUnknownOperation(instr[i]); }

		row = S.empty() ? 0 : actionsRowNumber(S.top());
		action = ActionsTable[row][col];
		int val[126]{ 0 };
		switch (action) {
		case 1:
			foo(outstr, instr, i, j, V);
			break;
		case 2: S.push(instr[i]); ++i;	break;
		case 3: outstr[j] = S.top(); S.pop(); ++j; break;
		case 4: S.pop(); ++i; break;
		case 5: throw ErrorBracketsClose(instr, i); break;
		case 6: throw ErrorBracketsOpen(instr, i);	break;
		case 9: outstr[j] = '\0';	break;
		case 100: throw ErrorUnknownOperation(instr[i]);
		}
	} while (action != 9);
}

void BooleanExpression::parsing(const char* instr, char* outstr) {
	int j = 0;
	bool error = true;
	for (int i = 0; i < strlen(instr);) {
		switch (instr[i])
		{
		case'x':
			outstr[j] = instr[i];
			++i;
			++j;
			while (instr[i] >= '0' && instr[i] <= '9') {
				outstr[j] = instr[i];
				++i;
				++j;
				error = false;
			}
			if (error) { throw ErrorNumber(instr, i); }
			error = true;
			break;
		case' ':
			while (instr[i] == ' ') {
				++i;
			}
			break;
		case '1':
			if (j != 0 && outstr[j - 1] == 'x') { break; }
			outstr[j] = 'y';
			++i;
			++j;
			break;
		case '0':
			outstr[j] = 'z';
			++i;
			++j;
			break;
		case '\n':
		case '\r':
			++i;
			break;
		default:
			outstr[j] = instr[i];
			++i;
			++j;
		}
	}
}

//0 - ?
//1 - на выход
//2 - на стек
//3 - взять из стека на выход
//4 - выкинуть из стека
//4 - нет открывающий скобки
//5 - нет закрывающий скобки
//9 - победа

void foo(char* outstr, const char* instr, int& i, int& j, Values& V) {
	outstr[j] = instr[i];
	++i;
	++j;
	char num[4]{ 0 };
	for (int o = 0; (instr[i] >= '0' && instr[i] <= '9'); ++o) {
		outstr[j] = instr[i];
		num[o] = instr[i];
		++i;
		++j;
	}
	int number = 0;
	int d = 0;
	for (int o = strlen(num); o > 0; --o) {
		number += (int)((num[d] - '0') * pow(10, o-1));
		++d;
	}
	V.push(number);
}
