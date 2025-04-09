#include <iostream>
#include <fstream>

struct Node {
	Node* parent;
	Node* spiling;
	Node* child;
	int degree;
	int key;
	int data;
	Node() :parent(nullptr), spiling(nullptr), child(nullptr),
		degree(0), data(0) {}
};
template <typename T>
class Vector {
private:
	//T* array;
	size_t size;
	size_t capacity;

public:
	T* array;
	Vector() : array(nullptr), size(0), capacity(0) {}
	~Vector() {
		delete[] array;
	}

	void push_back(const T& element) {
		if (size >= capacity) {
			size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
			T* new_array = new T[new_capacity];
			if (array != nullptr) {
				for (int i = 0; i < size; ++i) {
					new_array[i] = array[i];
				}
				delete[] array;
			}
			array = new_array;
			capacity = new_capacity;
		}
		array[size++] = element;
	}

	void print() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}
	T& operator[](size_t index){
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}
		return array[index];
	}
};
class BinomialHeap {
	Node* root;
	void BinomialTreeLink(Node* child, Node* parent) {
		child->parent = parent;
		child->spiling = parent->child;
		parent->child = child;
		parent->degree = child->degree + 1;
	}
public:
	BinomialHeap() :root(nullptr) {}
	void mergeNode(Node* h2) {
		if (!root) {
			root = h2;
			return;
		}
		if (!h2) {
			return;
		}
		Node* h1 = root;
		Node* h = nullptr;
		Node* x = nullptr;

		if (h1->degree < h2->degree) {
			h = h1;
			h1 = h1->spiling;
		}
		else {
			h = h2;
			h2 = h2->spiling;
		}
		x = h;
		while (h1 && h2) {
			if (h1->degree < h2->degree) {
				x->spiling = h1;
				h1 = h1->spiling;
			}
			else {
				x->spiling = h2;
				h2 = h2->spiling;
			}
			x = x->spiling;
		}
		while (h1) {
			x->spiling = h1;
			h1 = h1->spiling;
			x = x->spiling;
		}
		while (h2) {
			x->spiling = h2;
			h2 = h2->spiling;
			x = x->spiling;
		}

		Node* x0 = nullptr;
		Node* x1 = h;
		Node* x2 = h->spiling;
		while (x2) {
			if (x1->degree != x2->degree 
				|| x2->spiling && (x2->spiling->degree == x1->degree)) {
				x0 = x1;
				x1 = x2;
			}
			else if (x1->data <= x2->data) {
				x1->spiling = x2->spiling;
				BinomialTreeLink(x2, x1);
			}
			else {
				if (!x0) {
					h = x2;
				}
				else {
					x0->spiling = x2;
				}
				BinomialTreeLink(x1, x2);
				x1 = x2;
			}
			x2 = x1->spiling;
		}

		root = h;
	}
	Node* insert(int x, int key) {
		Node* X = new Node();
		X->data = x;
		X->key = key;
		mergeNode(X);
		Node* tmp(X);//?
		return tmp;
	}
	int extractMin(bool& empty) {
		if (!root) { 
			empty = true;
			return 0;
		}
 		int minData = -1;
		Node* x = root;
		Node* prev = nullptr;
		Node* minPrevNode = nullptr;
		Node* minNode = nullptr;
		int min = INT32_MAX;
		while (x) {
			if (x->data < min) {
				min = x->data;
				minPrevNode = prev;
				minNode = x;
			}
			prev = x;
			x = x->spiling;
		}
		if (!minPrevNode) {
			root = minNode->spiling;
		}
		else { 
			minPrevNode->spiling = minNode->spiling;
		}
		minData = minNode->data;
		Node* child = minNode->child;
		Node* spiling = nullptr;
		prev = nullptr;
		while (child) {
			spiling = child->spiling;
			child->spiling = prev;
			prev = child;
			child = spiling;
			prev->parent = nullptr;
		}
		delete minNode;
		minNode = nullptr;
		mergeNode(prev);
		return minData;
	}
	void decreaseKey(Node* x, int data, Vector<Node*>& V) {
		if (x->data < data) { return; }
		x->data = data;
		Node* y = x;
		Node* z = y->parent;	
		while (z) {
			std::swap(y->data, z->data);
			std::swap(y->key, z->key);
			std::swap(V[y->key-1], V[z->key - 1]);
			y = z;
			z = y->parent;
		}
	}
};

int main(int argc, const char* argv[]) {
	BinomialHeap H;
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	/*std::ifstream in("tests/input5.txt");
	std::ofstream out("output.txt");*/
	int x = 0;
	int key = 1;
	int y = 0;
	bool empty = false;
	Vector<Node*> M;
	while ((x = in.get()) != EOF) {
		Node* tmp = nullptr;
		switch (x)
		{
		case 'p':
			while ((x = in.get()) != ' ') {}
			in >> x;
			tmp = H.insert(x,key);
			while ((x = in.get()) != '\n') {}
			break;
		case 'e':
			while ((x = in.get()) != '\n') {}
			x = H.extractMin(empty);
			if (empty) { out << "*" << '\n'; }
			else { out << x << '\n'; }
			empty = false;
			break;
		case 'd':
			while ((x = in.get()) != ' ') {}
			in >> x;
			in >> y;
			H.decreaseKey(M[x - 1], y, M);
			while ((x = in.get()) != '\n') {}
			break;
		default:
			std::cout << "parse errror";
			break;
		}
		++key;
		M.push_back(tmp);
	}

	in.close();
	out.close();
	return 0;
}
