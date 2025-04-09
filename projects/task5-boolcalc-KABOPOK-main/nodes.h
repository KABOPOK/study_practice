
//#include "boolexpr.h"
#ifndef nodes
#define nodes
#include <string>
#include <vector>
#include "algoritms.h"

struct Values {
	std::vector<int> values;
	std::vector<int> SortValues;
	std::vector<int> CopyOfSortValues;
	std::vector<int> V_condition;
	int amountVal;
public:
	Values() {
		amountVal = 0;
	}
	void push(int n) {
		bool repeat = false;
		int i = 0;
		for (; i < values.size(); ++i) {
			if (values[i] == n) { repeat = true; break; }
		}
		if (repeat) {
			values.push_back(n);
		}
		else {
			values.push_back(n);
			SortValues.push_back(n);
			CopyOfSortValues.push_back(n);
			V_condition.push_back(0);
			++amountVal;
		}
	}

	void sort() {
		ChooseSortM(SortValues, values.size());
	}
	void sort(char* str) {
		ChooseSortM2(SortValues, str, SortValues.size());
	}
	void SendFlying() {
		for (int i = 0; i < SortValues.size(); ++i) {
			SortValues[i] = CopyOfSortValues[i];
		}
	}

	void setCondition(const char* str) {
		for (int i = 0; i < strlen(str); ++i) {
			V_condition[i] = str[i] - '0';
		}
	}
	int findInd(int n) {
		for (int i = 0; i < SortValues.size(); ++i) {
			if (SortValues[i] == n) { return i; }
		}
		return -1;
	}
};

struct pairM {
	const int numeral = 49;
	char* M_;
	int* M_n;
	pairM(char* M) {
		M_ = M;
		M_n = new int[strlen(M)]{ 0 };
		for (int i = 0; i < strlen(M); ++i) {
			M_n[i] = numeral + i;
		}
	}
	~pairM() {
		delete[] M_n;
	}
};

class FormulaNode {
public:
	virtual int calc() const = 0;
	virtual ~FormulaNode() {}
};
//-------------------------------------------
class NumNode : public FormulaNode {
	const int num;
public:
	NumNode(int x) : num(x) {}
	int calc() const { return num; }
};
//-------------------------------------------
class ParamNode : public FormulaNode {
	const int num_;
	Values* V_;
public:
	ParamNode(int num, Values* V) : num_(num) { V_ = V; }
	int calc() const {
		return V_->V_condition[V_->findInd(num_)];
	}
};
//-------------------------------------------
class BinNode : public FormulaNode {
protected:
	FormulaNode* left, * right;
public:
	BinNode(FormulaNode* L, FormulaNode* R) : left(L), right(R) {}
	~BinNode() {
		delete left;
		delete right;
		left = right = nullptr;
	}
};
//-------------------------------------------
class DisjunctionNode : public BinNode { // V
public:
	DisjunctionNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return left->calc() | right->calc(); }
};
//-------------------------------------------
class ConjunctionNode : public BinNode { // &
public:
	ConjunctionNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return left->calc() & right->calc(); }
};
//-------------------------------------------
class ExclusiveOrNode : public BinNode { // +
public:
	ExclusiveOrNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return left->calc() ^ right->calc(); }
};
//-------------------------------------------
class ShepherStrokeNode : public BinNode { // |
public:
	ShepherStrokeNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return ((left->calc() & right->calc())==1) ? 0 : 1; }
};
//-------------------------------------------
class NeedleNode : public BinNode { // ^
public:
	NeedleNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return ((left->calc() | right->calc()) == 1) ? 0 : 1;
	}
};
//-------------------------------------------
class RInplicationNode : public BinNode { // >
public:
	RInplicationNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return inplication(left->calc(), right->calc()); }
};
//-------------------------------------------
class LInplicationNode : public BinNode { // <
public:
	LInplicationNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return inplication(right->calc(), left->calc()); }
};
//-------------------------------------------
class EquivalenceNode : public BinNode { // =
public:
	EquivalenceNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	int calc() const { return static_cast<int>(right->calc() == left->calc()) == 1 ? 1 : 0; }
};
//-------------------------------------------
class DenialNode : public FormulaNode { // ~
protected:
	FormulaNode* next;
public:
	DenialNode(FormulaNode* node) : next(node) {}
	int calc() const {
		return next->calc() == 1 ? 0 : 1;
	}
	~DenialNode() {
		delete next;
		next = nullptr;
	}
};
//-------------------------------------------
#endif
