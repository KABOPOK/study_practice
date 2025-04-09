#define RLE

#ifdef RLE
#include <iostream>
#include <fstream>
#include <cstring>
//MTF
void MTC(std::ifstream& inFile, std::ofstream& outFile);
void newMTC(std::ifstream& inFile, std::ofstream& outFile);
void deMTC(std::ifstream& inFile, std::ofstream& outFile);

//Huftrees
struct node {
	unsigned long long power;
	char ch = 0;
	bool position;
	node* dad;
	node* l;
	node* r;
	node(unsigned long long i) {
		l = nullptr;
		r = nullptr;
		dad = nullptr;
		power = i;
		position = false;
		ch = 0;
	}
	node() {
		l = nullptr;
		r = nullptr;
		dad = nullptr;
		power = 0;
		position = false;
		ch = 0;
	}
	~node() {
		delete l;
		delete r;
		l = r = nullptr;
	}
};
struct table {
	node* nodes[256];
	char symbols[256][256];
	table() {
		for (int i = 0; i < 256; ++i) {
			symbols[i][0] = 0;
		}
		for (int i = 0; i < 256; ++i) {
			nodes[i] = 0;
		}
	}
};
node* merge(unsigned long long i, unsigned long long j, table& T, char is, char js);
node* merge(node* i, unsigned long long j, table& T, char js);
node* merge(unsigned long long i, node* j, table& T, char is);
node* merge(node* i, node* j);
void getCode(node* c, table& T, char ch);
void push(node** T, unsigned long long* M, char* M_S, int now, node* c);
class ibitfstream : public std::ifstream {
	unsigned char buffer;
	unsigned char bitcount;
public:
	ibitfstream(const char* filename) : std::ifstream(filename, std::ios_base::binary), bitcount(0) {}
	int getbit() {
		if (bitcount == 8) {
			bitcount = 0;
		}
		if (bitcount == 0) { buffer = get(); } // std::ifstream::get()
		int result = ((buffer & (1 << (7 - bitcount))) == 0) ? 0 : 1;
		++bitcount;
		return result;
	}
	bool eof() {
		if (bitcount > 0 && bitcount < 8) { return false; }
		if (peek() != EOF) { return false; }
		return true;
	}
};
class obitfstream : public std::ofstream {
	unsigned char buffer;
	unsigned char bitcount;
public:
	obitfstream(const char* filename) : std::ofstream(filename, std::ios_base::binary) {
		buffer = 0;
		bitcount = 0;
	}
	void putline(char(*symbols)[256], int i) {
		//011 ( *a )[4]

		for (int j = 0; j < symbols[i][0]; ++j) {
			buffer |= (symbols[i][symbols[i][0] - j] << (7 - bitcount));
			++bitcount;
			if (bitcount == 8) {
				put((char)buffer);
				buffer = 0;
				bitcount = 0;
			}
		}
	}

	void putULLByBite(unsigned long long a) {
		unsigned char bufferL = 0;
		unsigned char bitcountL = 0;
		int counter = 0;
		while (counter != 64) {
			if (bitcountL == 8) {
				put((char)bufferL);
				bufferL = 0;
				bitcountL = 0;
			}
			unsigned long long num = 1ULL << (63 - counter);
			if ((a & num) != 0) {
				bufferL |= 1 << (7 - bitcountL);
				/*if (bitcountL % 4 == 0) { std::cout << " "; }
				std::cout << "1";*/
			}
			else {
				/*if (bitcountL % 4 == 0) { std::cout << " "; }
				std::cout << "0";*/
			}
			++bitcountL;
			++counter;
		}
		if (bitcountL == 8) {
			put((char)bufferL);
		}
	}

	void close() { //problem 
		if (bitcount > 0) { put((char)buffer); }
		bitcount = 7;
		buffer = 0;
		std::ofstream::close();
	}

};
void HUFman(std::ifstream& inFile, obitfstream& outFile);
void deHUFman(ibitfstream& inFile, obitfstream& outFile);

//LZV
struct link {
	int offset;
	int length;
	int next;
	link() :offset(0), length(0), next(0) {};
};
struct cash {
	int mass[1024];
	int current_indx;
	int buff_indx;
	int start_of_buff;
	int end_of_buff;
	cash() : current_indx(0), start_of_buff(0) {
		for (int i = 0; i < 1024; ++i) {
			mass[i] = 300;
		}
		end_of_buff = 128;
		buff_indx = 0;
	}

	void operator++() {
		if (buff_indx + 1 >= end_of_buff) { buff_indx = start_of_buff; }
		else { ++buff_indx; }
	}

	void push(int ch) {
		if (current_indx == 1024) {
			for (int j = 0; j < 128; ++j) {
				mass[j] = mass[896 + j];
			}
			current_indx = 128;
		}
		mass[current_indx] = ch;
		++current_indx;
		++*this;
	}

	int getISymbol(int i) {
		return mass[start_of_buff + i];
	}

	void reSet() {
		if (current_indx - 128 > 0) { start_of_buff = current_indx - 128; }
		else { start_of_buff = 0; }
		end_of_buff = current_indx;
	}
	void setBuffer() {
		end_of_buff = current_indx;
	}
	int getCurrentSymbol() {
		return mass[current_indx];
	}
	int operator[](int i) {
		if (i + start_of_buff >= end_of_buff) {
			return mass[start_of_buff + i % end_of_buff - start_of_buff];
		}
		return mass[i + start_of_buff];
	}
};
void RLEcomBACK(ibitfstream& inFile, obitfstream& outFile);
void deRLEcomBACK(ibitfstream& inFile, obitfstream& outFile);


template <typename T>
void QuickSortS(char* M_S, T* M, int n) {
	if (!M) { return; }
	int N = n;
	int size = 1;
	while (N > 0) {
		N >>= 1; // N=N/2;
		++size;
	}
	size += 2;
	int* stackLeft = new int[size];
	int* stackRight = new int[size];
	int topInStack = -1;
	++topInStack; stackLeft[topInStack] = 0; stackRight[topInStack] = n - 1;
	while (topInStack > -1) {
		int from = stackLeft[topInStack];
		int to = stackRight[topInStack];
		--topInStack;
		int left = from;
		int right = to;
		//int pindex = left + (right-left)/2;
		if (right - left == 0) {
			right = 1;
			left = 0;
		}
		int pindex = left + rand() % (right - left);
		if (pindex == 0) { pindex = 1; }

		T p = M[pindex];
		while (left < right) {
			while (M[left] < p) { ++left; }
			while (p < M[right]) { --right; }
			if (left < right) {
				std::swap(M[left], M[right]);
				std::swap(M_S[left], M_S[right]);
				++left;
				--right;
			}
			else if (left == right) {
				++left;
				--right;
			}
		}

		if ((left + right) / 2 < left) {
			//Cначала на Cтeк помeCтим больший отрeзок
			if (right > from) {
				++topInStack;
				stackLeft[topInStack] = from;
				stackRight[topInStack] = right;
			}
			if (left < to) {
				++topInStack;
				stackLeft[topInStack] = left;
				stackRight[topInStack] = to;
			}
		}
		else {
			if (left < to) {
				++topInStack;
				stackLeft[topInStack] = left;
				stackRight[topInStack] = to;
			}
			if (right > from) {
				++topInStack;
				stackLeft[topInStack] = from;
				stackRight[topInStack] = right;
			}
		}
	}

	delete[] stackLeft;
	delete[] stackRight;
}
void putArray(unsigned long long* M, unsigned long long counter, obitfstream& outFile);
void getArray(unsigned long long* M, unsigned long long& counter, ibitfstream& inFile);
#endif