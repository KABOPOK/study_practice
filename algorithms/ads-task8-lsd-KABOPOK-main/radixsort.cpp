#include <iostream>
#include <fstream>

struct Section {
    int x1;
    int x2;
};
void print(Section* M, int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::cout << (char)M[i].x1 << " ";
    }
    std::cout << '\n';
    for (int i = start; i <= end; ++i) {
        std::cout << M[i].x2 << " ";
    }
    std::cout << '\n';
    std::cout << '\n';
}
bool compX1(Section i, Section j) {
    return i.x1 <= j.x1;
}
bool compX2(Section i, Section j) {
    return i.x2 <= j.x2;
}
class Container {
    int* M;
    int row;
    int col;
public:
    Container(int row, int col) : row(row), col(col) {
        M = new int[row * col];
    }
    int& operator()(int i, int j) {
        return M[i * col + j];
    }
    int& operator()(int i) {
        return M[i];
    }
    ~Container() {
        delete[] M;
    }
};
void merge(Section*& M, Section*& tmp, int start1, int start2, int end, bool (*comp)(Section i, Section j)) {
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
void MergeSort(Section*& M, int n, bool (*comp)(Section i, Section j)) {
    Section* tmp = new Section[n];
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

int main(int argc, const char* argv[]) {
    using namespace std;
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    int row = 0;
    int col = 0;
    int k = 0;
    in >> col;
    in >> row;
    in >> k;
    Container M(row, col);
    int counter = 0;
    in.ignore();
    int x = in.get();
    while (x != EOF) {
        M(counter++) = x;
        x = in.get();
        while (x == '\n' || x == '\r') { x = in.get(); }
    }
    Section* S = new Section[col];
    for (int i = 0; i < col; ++i) {
        S[i].x2 = i;
    }
    counter -= col;
    for (int j = 0; j < k - 1; ++j) {
        //pull
        for (int i = col - 1; i >= 0; --i) {
            S[i].x1 = M(counter + S[i].x2);
        }
        //sort
        MergeSort(S, col, compX1);
        counter -= col;
    }
    //pull
    for (int i = col - 1; i >= 0; --i) {
        S[i].x1 = M(counter + S[i].x2);
    }
    //sort
    MergeSort(S, col, compX1);
    //set
    for (int i = col - 1; i >= 0; --i) {
        S[i].x1 = M(S[i].x2);
    }
    for (int i = 0; i < col; ++i) {
        out << (char)S[i].x1;
    }
    delete[] S;
}
