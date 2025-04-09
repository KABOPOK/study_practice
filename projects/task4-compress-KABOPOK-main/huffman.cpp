#include "structures.h"
node* merge(unsigned long long i, unsigned long long j, table& T, char is, char js) {

	node* a = new node(i);
	T.nodes[(unsigned char)is] = a;
	a->ch = is;
	node* b = new node(j);
	T.nodes[(unsigned char)js] = b;
	b->ch = js;
	node* c = new node(i + j);
	a->dad = b->dad = c;
	c->l = a;
	c->r = b;
	return c;
}
node* merge(node* i, unsigned long long j, table& T, char js) {
	node* b = new node(j);
	T.nodes[(unsigned char)js] = b;
	b->ch = js;
	node* c = new node(i->power + j);
	i->dad = b->dad = c;
	c->l = i;
	c->r = b;
	return c;
}
node* merge(unsigned long long i, node* j, table& T, char is) {
	node* a = new node(i);
	T.nodes[(unsigned char)is] = a;
	a->ch = is;
	node* c = new node(i + j->power);
	a->dad = j->dad = c;
	c->l = a;
	c->r = j;
	return c;
}
node* merge(node* i, node* j) {
	node* c = new node(i->power + j->power);
	i->dad = j->dad = c;
	c->l = i;
	c->r = j;
	return c;
}
void getCode(node* c, table& T, char ch) {
	char counter = 0;
	node* prev = c;
	int i = 1;
	while (c->dad != nullptr) {
		prev = c->dad;
		if (prev->l == c) {
			T.symbols[(unsigned char)ch][i] = (char)1;
		}
		if (prev->r == c) {
			T.symbols[(unsigned char)ch][i] = (char)0;
		}
		++i;
		c = c->dad;
		++counter;
	}
	T.symbols[(unsigned char)ch][0] = counter;
}
void push(node** T, unsigned long long* M, char* M_S, int now, node* c) {
	unsigned long long power = c->power;
	M[now] = power;
	T[now] = c;
	for (int i = now; i < 255 && power > M[i + 1]; ++i) {
		std::swap(M[i + 1], M[i]);
		std::swap(T[i + 1], T[i]);
		std::swap(M_S[i + 1], M_S[i]);
	}

}
void HUFman(std::ifstream& inFile, obitfstream& outFile) {
	//take tablet
	unsigned long long M[256]{ 0 };
	unsigned long long counter = 0;
	char M_S[256]{ 0 };
	int ch = 0;
	while ((ch = inFile.get()) != EOF) {
		++M[ch];
		++counter;
	}

	for (int i = 0; i < 256; ++i) {
		outFile << M[i] << '\n';
	}
	outFile << counter << '\n';
	//putArray(M, counter, outFile);

	for (int i = 0; i < 256; ++i) { M_S[i] = (char)i; }
	QuickSortS(M_S, M, 256);

	//create tree
	int i = 0;
	table H;
	for (; i < 256; ++i) { if (M[i] > 0) { break; } }
	node* T[256]{ 0 };
	if (i == 255) {
		H.symbols[M_S[255]][0] = 1;
		H.symbols[M_S[255]][1] = 1;
	}
	while (i + 1 < 256) {
		node* c = nullptr;
		if (T[i] == nullptr && T[i + 1] == nullptr) { c = merge(M[i], M[i + 1], H, M_S[i], M_S[i + 1]); }
		if (T[i] == nullptr && T[i + 1] != nullptr) { c = merge(M[i], T[i + 1], H, M_S[i]); }
		if (T[i] != nullptr && T[i + 1] == nullptr) { c = merge(T[i], M[i + 1], H, M_S[i + 1]); }
		if (T[i] != nullptr && T[i + 1] != nullptr) { c = merge(T[i], T[i + 1]); }
		++i;
		push(T, M, M_S, i, c);
	}
	for (int i = 0; i < 256; ++i) {
		if (H.nodes[i] != nullptr) {
			getCode(H.nodes[i], H, (char)i);
		}
	}
	//
	inFile.clear();
	inFile.seekg(0);
	while ((ch = inFile.get()) != EOF) {
		if (ch < 0) {}
		outFile.putline(H.symbols, ch);
	}
	delete T[255];
}
void deHUFman(ibitfstream& inFile, obitfstream& outFile) {
	unsigned long long M[256];
	unsigned long long bytes;

	for (int i = 0; i < 256; ++i) {
		inFile >> M[i];
	}
	inFile >> bytes;
	//getArray(M, bytes, inFile);
	//take tablet
	char M_S[256]{ 0 };
	int ch = 0;
	for (int i = 0; i < 256; ++i) { M_S[i] = (char)i; }
	QuickSortS(M_S, M, 256);

	//create tree
	int i = 0;
	table H;
	for (; i < 256; ++i) { if (M[i] > 0) { break; } }
	node* T[256]{ 0 };
	if (i == 255) {
		T[255] = new node();
		T[255]->ch = M_S[255];
	}
	while (i + 1 < 256) {
		node* c = nullptr;
		if (T[i] == nullptr && T[i + 1] == nullptr) { c = merge(M[i], M[i + 1], H, M_S[i], M_S[i + 1]); }
		if (T[i] == nullptr && T[i + 1] != nullptr) { c = merge(M[i], T[i + 1], H, M_S[i]); }
		if (T[i] != nullptr && T[i + 1] == nullptr) { c = merge(T[i], M[i + 1], H, M_S[i + 1]); }
		if (T[i] != nullptr && T[i + 1] != nullptr) { c = merge(T[i], T[i + 1]); }
		++i;
		push(T, M, M_S, i, c);
	}

	int bit = 0;
	int y = 0;
	inFile.ignore();
	while (bytes > 0) {
		if (bytes == 2) {
			bytes = 1 + 1;
		}
		node* main = T[255];
		while (main->l != nullptr) {
			bit = inFile.getbit();
			//if (y != 0 && y % 8 == 0) { std::cout << " "; }
			//std::cout << bit;
			++y;
			if (bit == 1) { main = main->l; }
			else { main = main->r; }
		}
		outFile << main->ch;
		--bytes;
	}
	delete T[255];
}

void putArray(unsigned long long* M, unsigned long long counter, obitfstream& outFile) {
	for (int i = 0; i < 256; ++i) {
		outFile.putULLByBite(M[i]);
		//std::cout << std::endl;
	}
	outFile.putULLByBite(counter);
}
void getArray(unsigned long long* M, unsigned long long& counter, ibitfstream& inFile) {
	for (int i = 0; i < 256; ++i) {
		int j = 0;
		while (j < 64 && inFile.getbit() == 0) { ++j; }
		if (j == 64) { M[i] = 0; }
		else {
			M[i] = 1;
		}
		++j;
		for (; j < 64; ++j) {
			if (inFile.getbit() == 1) {
				M[i] *= 2; M[i] += 1;
			}
			else {
				M[i] *= 2;
			}
		}
	}
	int j = 0;
	while (inFile.getbit() == 0) { ++j; }
	counter = 1;
	++j;
	for (; j < 64; ++j) {
		if (inFile.getbit() == 1) { counter *= 2; counter += 1; }
		else { counter *= 2; }
	}
}