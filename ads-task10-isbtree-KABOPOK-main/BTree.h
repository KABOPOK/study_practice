#include <iostream>
#include <fstream>

struct Node {
    int id;
    int* M;
    int* ptr;
    int sizeM;
    int sizePtr;
    Node(int id) :id(id) {
        M = nullptr;
        ptr = nullptr;
        sizeM = 0;
        sizePtr = 0;
    }
    Node(std::ifstream& in, int rootNum, Node*& root, int& t) {
        M = nullptr;
        ptr = nullptr;
        sizeM = 0;
        sizePtr = 0;
        bool branch = false;
        int s = 0;
        while ((s != 'b') && (s != 'l')) { s = in.get(); };
        s == 'b' ? branch = true : branch = false;
        while ((s = in.get()) != 'x') { s = in.get(); }
        in >> id;
        in.ignore();
        in.ignore();//(
        int n = 0;
        in >> n;
        sizeM = n;
        M = new int[n];
        in.ignore();//:
        in >> M[0];
        for (int i = 1; i < n; ++i) {
            in >> M[i];
            if (M[i] < M[i - 1]) { t = -1; }
        }
        if (id == rootNum) {
            root = this;
        }
        if (branch) {
            if (id == rootNum) {
                if (n < 1 || n > 2 * t - 1) { t = -1; }
            }
            else {
                if (n < t - 1 || n > 2 * t - 1) { t = -1; }
            }
            
            in.ignore();//)
            in.ignore();
            in.ignore();//(
            in >> n;
            sizePtr = n;
            in.ignore();//:
            if (sizePtr-1 != sizeM) { t = -1; }

            ptr = new int[n];
            for (int i = 0; i < n; ++i) {
                in >> ptr[i];
            }

        }
        else {
            if (n < t - 1 || n > 2 * t - 1) { t = -1; }
            ptr = nullptr;
        }
    }
    ~Node() {
        delete[]M;
        delete[]ptr;
    }
};
