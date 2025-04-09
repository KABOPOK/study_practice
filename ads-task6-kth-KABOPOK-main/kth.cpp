#include <iostream>
#include <fstream>
void print(int* M, int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::cout << M[i] << " ";
    }
    std::cout << '\n';
}
void QuickSortS(int* M, int start, int end, int leftBorder, int rightBorder) {
    int diff = end - start + 1;
    int size = 1;
    while (diff > 0) {
        diff >>= 1;
        ++size;
    }
    size += 2;
    int* stackLeft = new int[size];
    int* stackRight = new int[size];
    stackLeft[0] = start;
    stackRight[0] = end;
    int stackSize = 0;
    while (stackSize!=-1) {
        int left = stackLeft[stackSize];
        int right = stackRight[stackSize];
        --stackSize;
        int pIndex = left + (right - left) / 2;
        int p = M[pIndex];
        int from = left;
        int to = right;
        while (left < right) {
            while (M[left] < p) { ++left; }
            while (p < M[right]) { --right; }
            if (left < right) {
                std::swap(M[left], M[right]);
                ++left;
                --right;
            }
            else if (left == right) {
                ++left;
                --right;
            }
        }
        if (left < leftBorder) {
            if (left < to) {
                ++stackSize;
                stackLeft[stackSize] = left;
                stackRight[stackSize] = to;
            }
        }
        else {
            if (right > rightBorder) {
                if (right > from) {
                    ++stackSize;
                    stackLeft[stackSize] = from;
                    stackRight[stackSize] = right;
                }
            }
            else {
                if ((left + right) / 2 < left) {
                    if (right > from) {
                        ++stackSize;
                        stackLeft[stackSize] = from;
                        stackRight[stackSize] = right;
                    }
                    if (left < to) {
                        ++stackSize;
                        stackLeft[stackSize] = left;
                        stackRight[stackSize] = to;
                    }
                }
                else {
                    if (left < to) {
                        ++stackSize;
                        stackLeft[stackSize] = left;
                        stackRight[stackSize] = to;
                    }
                    if (right > from) {
                        ++stackSize;
                        stackLeft[stackSize] = from;
                        stackRight[stackSize] = right;
                    }
                }
            }
        }
    }
    delete[] stackLeft;
    delete[] stackRight;
}
int main(int argc, const char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    int n = 18;
    int leftBorder = 0;
    int rightBorder = 0;
    int A = 0;
    int B = 0;
    int C = 0;
    int x1 = 0;
    int x2 = 0;
    in >> n;
    in >> leftBorder;
    in >> rightBorder;
    in >> A;
    in >> B;
    in >> C;
    in >> x1;
    in >> x2;
    int* M = new int[n];
    --leftBorder;
    --rightBorder;
    M[0] = x1;
    M[1] = x2;
    for(int i = 2; i < n; ++i){
        M[i] = A*M[i-2] + B*M[i-1] + C;
    }
    //find border
    QuickSortS(M, 0, n - 1, leftBorder, rightBorder);
        for (int i = leftBorder; i <= rightBorder; ++i) {
            if (i != rightBorder) { out << M[i] << " "; }
           else { out << M[i]; }
        }
    delete[] M;
    return 0;
}
