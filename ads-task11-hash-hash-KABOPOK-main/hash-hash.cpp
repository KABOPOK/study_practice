#include <iostream>
#include <fstream>

int counter;

struct Node {
    int num;
    char condition;
    Node():num(0),condition('n') {}
};

void print(Node* M, int n) {
    std::cout << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << M[i].num << " ";

    }
    std::cout << "\n";
}

class DynamicHashTable {
    Node* data;
    int a;
    int b;
    int size;
    int capacity;
    int hash(int k) const { return ((a * k + b) % (capacity + 3)) % capacity; }
    void upDataBorders() {
        int n = size;
        capacity *= 10;
        a = rand() % (capacity +2);
        b = rand() % (capacity +1) + 1;
        Node* tmp;
        tmp = new Node[capacity];
        for(int i =0; i < n; ++i){
            int index = hash(data[i].num);
            while (tmp[index].condition == 'b') {
                ++index;
                if (index == capacity) { index = 0; }
            } 
            tmp[index] = data[i];
        }
       // print(tmp, capacity);
        delete[] data;
        data = tmp;
    }
public:
    DynamicHashTable(int x) :size(1), a(0), b(0), capacity(1) {
        data = new Node[1];
        data[0].num = x;
        data[0].condition = 'b'; //deleted
        ++counter;
    }
    void push(int k) {
        if (size == capacity) upDataBorders() ;
        int index = hash(k);
        while (data[index].condition == 'b') {
            ++index;
            if (index == capacity) { index = 0; }
        }
        data[index].num = k;
        data[index].condition = 'b';
        ++size;
    }
    void erase(int k) {
        int index = hash(k);
        int start = index;
        while (data[index].num != k && (data[index].condition != 'n'|| data[index].condition != 'd')) {
            ++index;
            if (index == capacity) { index = 0; }
            if (index == start) { return; }
        }
        data[index].condition = 'd';
    }
    bool find(int k) const {
        int index = hash(k);
        int start = index;
        while (data[index].condition != 'n' && (data[index].num != k || data[index].condition == 'd')) {
            ++index;
            if (index == capacity) { index = 0; }
            if (index == start) { break; }
        }
        if (data[index].num == k && data[index].condition != 'd') { return true; }
        return false;
    }
    ~DynamicHashTable() { 
        delete[] data;
        --counter;
    }
};

class PerfectHashTable {
    DynamicHashTable** M;
    int a;
    int b;
    int m;
    int p;
    int hash(int k) const { return ((a * k + b) % p) % m; }
public:
    PerfectHashTable(int size, int nextSimpleNum): p(nextSimpleNum),m(size) {
        M = new DynamicHashTable * [size] {nullptr};
        a = rand() % (p - 1);
        b = rand() % (p - 2) + 1;
    }
    void push(int k){
        int i = hash(k);
        if (i < 0) { i *= -1; }
        if (!M[i]) {
            M[i] = new DynamicHashTable(k);
        }
        else {
            M[i]->push(k);
        }
    }
    void erase(int k) {
        int i = hash(k);

        if (i < 0) { i *= -1; }
        if (!M[i]) { return; }
        M[i]->erase(k);
    }
    bool find(int k) const {
        int i = hash(k);
        if (i < 0) { i *= -1; }
        if (!M[i]) { return false; }
        return M[i]->find(k);
    }

    ~PerfectHashTable() {
        for (int i = 0; i < m; ++i) {
           delete M[i];
        }
        delete[] M;
    }
};

int main(int argc, const char* argv[]) {
    /*std::ifstream in("input4.txt");
    std::ofstream out("o.txt");*/
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    const int N = 100000;
    const int P = 100003;
    //const int N = 10;
    //const int P = 13;
    int n = 0;
    int x = 0;
    char sign = 0;
    in >> n;
    PerfectHashTable T(N, P);
    while (n != 0) {
        sign = in.get();
        while (sign == '\n' || sign == '\r') {sign = in.get();}
        in >> x;
        --n;
        switch (sign) {
        case '+':
            /*if (x < 0) {
                std::cout << "kd";
            }*/
            T.push(x);
            break;
        case '-':
            T.erase(x);
            break;
        case '?':
            if (T.find(x)) { out << "true" << '\n'; }
            else { out << "false" << '\n'; }
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        
    }
}
