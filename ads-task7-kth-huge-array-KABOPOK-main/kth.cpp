#include <iostream>
#include <fstream>
void print(int* M, int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::cout << M[i] << " ";
    }
    std::cout << '\n';
}
class Heap {
    int* M_;
    int n_;
    void healHeap() {
        int i = 0;
        while (2 * i + 1 < n_) {
            if (2 * i + 2 >= n_ && M_[i] < M_[2 * i + 1] || M_[i] < M_[2 * i + 1] && M_[2 * i + 1] > M_[2 * i + 2]) {
                std::swap(M_[i], M_[2 * i + 1]);
                i = 2 * i + 1;
                continue;
            }
            else if (2 * i + 2 < n_ && M_[i] < M_[2 * i + 2]) {
                std::swap(M_[i], M_[2 * i + 2]);
                i = 2 * i + 2;
                continue;
            }
            else { break; }
        }
    }

    void sortHeap() {
        // shift down_ each eleM_en_t
        int size = n_;
        for (int i = 1; i < n_; ++i) {
            if (M_[size - 1] < M_[0]) {
                std::swap(M_[size - 1], M_[0]);
            }
            --size;
            int pos = 0;
            int posM_axChild;
            while ((posM_axChild = 2 * pos + 1) < size) { // Пока есть элемент слева
                if (posM_axChild + 1 < size) { // Есть кто-то еще справа
                    if (M_[posM_axChild] < M_[posM_axChild + 1]) {
                        ++posM_axChild;
                    }
                }
                if (M_[pos] < M_[posM_axChild]) {
                    std::swap(M_[pos], M_[posM_axChild]);
                    pos = posM_axChild;
                }
                else { break; }
            }

        }
    }
public:
    Heap(int* M, int n) {
        this->n_ = n;
        M_ = M;
        for (int i = 1; i < n; ++i) {
            int pos = i;
            while (pos != 0) {
                int parent = (pos - 1) / 2;
                if (M_[parent] < M_[pos]) {
                    std::swap(M_[parent], M_[pos]);
                    pos = parent;
                }
                else
                    break;
            }
        }
    }
    void addElement(int X) {
        if (M_[0] > X) {
            M_[0] = X;
            healHeap();
        }
    }
    void writeToFile(int leftBorder, int rightBorder, std::ofstream& out) {
        sortHeap();
        for (int i = leftBorder - 1; i < rightBorder; ++i) {
            if (i + 1 == rightBorder) { out << M_[i]; }
            else { out << M_[i] << " "; }
        }
    }
};

int main(int argc, const char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    int n = 17;
    int A = 0;
    int B = 0;
    int C = 0;
    int x1 = 0;
    int x2 = 0;
    int leftBorder = 2;
    int rightBorder = 5;
    in >> n;
    in >> leftBorder;
    in >> rightBorder;
    in >> A;
    in >> B;
    in >> C;
    in >> x1;
    in >> x2;
    int* M = new int[rightBorder];
    M[0] = x1;
    M[1] = x2;
    for(int i = 2; i < rightBorder; ++i){
        M[i] = A*M[i-2] + B*M[i-1] + C;
    }
    x2=M[rightBorder-1];
    x1=M[rightBorder-2];
    Heap H(M, rightBorder);
    for (int i = rightBorder; i < n; ++i) {
        int X = A*x1 + B*x2 + C;
       // print(M, 0, rightBorder);
        H.addElement(X);
        x1=x2;
        x2=X;
    }
    H.writeToFile(leftBorder, rightBorder, out);
    delete[] M;
}
