#include "BTree.h"
bool compID(Node* i, Node* j) {
    return i->id <= j->id;
}
bool compID(Node**M, int i, int j, bool isLeftIndex) {
    if (isLeftIndex) return M[i]->id < j;
    return i < M[j]->id;
}
void print(Node** S, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << S[i]->id << " ";
    }
}
template <typename T>
void merge(T** M, T** tmp, int start1, int start2, int end, bool (*comp)(Node* i, Node* j)) {
    int index = start1;
    int i = start1;
    int j = start2;
    while (true) {
        if (comp(M[i], M[j])) {
            tmp[index++] = M[i++];
        }
        else {
            tmp[index++] = M[j++];
        }
        if (i == start2) {
            while (j < end) { tmp[index++] = M[j++]; }
            break;
        }
        if (j == end) {
            while (i < start2) { tmp[index++] = M[i++]; }
            break;
        }
    }
}
template <typename T>
void MergeSort(T**& M, int n, bool (*comp)(T* i, T* j)) {
    T** tmp = new T*[n];
    int p = 1;
    bool tmpOrder = true;
    while (p < n) {
        int i = 0;
        if (tmpOrder) {
            while (i + 2 * p <= n) {
                merge(M, tmp, i, i + p, i + 2 * p, comp);
                i += 2 * p;
            }
            if (i + p < n) {
                merge(M, tmp, i, i + p, n, comp);
                i += p;
            }
            else {
                for (; i < n; ++i) {
                    tmp[i] = M[i];
                }
            }
        }
        else {
            while (i + 2 * p <= n) {
                merge(tmp, M, i, i + p, i + 2 * p, comp);
                i += 2 * p;
            }
            if (i + p < n) {
                merge(tmp, M, i, i + p, n, comp);
                i += p;
            }
            else {
                for (; i < n; ++i) {
                    M[i] = tmp[i];
                }
            }
        }
        tmpOrder = !tmpOrder;
        p <<= 1;

    }
    if (!tmpOrder) {
        std::swap(M, tmp);
    }
    delete[] tmp;
}


Node* binarySearch(Node** M, int n, int x, bool (*iLessj)(Node** M, int i, int j, bool isLeftIndex)) {
    int left = 0;
    int right = n;
    int midlle = 0;
    int cMidlle = -1;
    while (true) {//5 7 
        midlle = left + (right - left) / 2;
        if (midlle == cMidlle) { return nullptr; }
        cMidlle = midlle;
        if (iLessj(M, midlle, x, true)) { // md < x
            left = midlle;
        }
        else {
            if (iLessj(M, x, midlle, false)) { // x < md
                right = midlle;
            }
            else {
                return M[midlle];
            }
        }
    }
}//-2147483648
//2147483647

void checkBorders(Node**M, int n, Node* root, int left, int right, bool& OK, int deep) {
    if (deep != 0 && !root->ptr) {
        OK = false;
        return;
    }
    if (!OK) { return; }
    for (int i = 0; i < root->sizeM; ++i) {
        if (root->M[i] < left || root->M[i] > right) { OK = false; }
    }
    int cLeft = left;
    int cRight = right;
    for (int i = 0; i < root->sizePtr; ++i) {
        i == 0? cLeft = left: cLeft = root->M[i-1];
        i + 1 != root->sizePtr ? cRight = root->M[i] : cRight = right;
        Node* current = binarySearch(M, n, root->ptr[i], compID);
        if (!current) { OK = false; }
        checkBorders(M, n, current, cLeft, cRight, OK, deep-1);
    }
    
    return;
}

int main(int argc, const char* argv[]) {
    int INTMAX = 2147483647;
    int INTMIN = -2147483648;
    std::ifstream in(argv[1]);
    int N = 0;
    in >> N;
    int t = 0;
    in >> t;
    int rootNum = 0;
    in >> rootNum;
    Node* root = nullptr;
    Node** S = new Node * [N];
    bool NO = false;
    for (int i = 0; i < N; ++i) {
        //pars
        S[i] = new Node(in, rootNum, root, t);
        if (t == -1) { std::cout << "no"; NO = true; N = i + 1; break; }
    }
    if (!NO) {
        MergeSort(S, N, compID);
        int deep = 0;
        Node* tmp = root;
        while (tmp->sizePtr!=0) {
            tmp = binarySearch(S, N, tmp->ptr[0], compID);
            ++deep;
        }
        bool OK = true;
        checkBorders(S, N, root, INTMIN, INTMAX, OK, deep);
        if (OK) { std::cout << "yes"; }
        else { std::cout << "no"; }
    }
    for (int i = 0; i < N; ++i) {
        delete S[i];
    }
    delete[] S;
    return 0;
}
