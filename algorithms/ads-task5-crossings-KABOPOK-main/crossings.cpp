#include <iostream>
#include <fstream>


struct Section {
    int x1;
    int x2;
};
long long counter = 0;
bool compX1(Section i, Section j) {
    return i.x1 <= j.x1;
}
bool compX2(Section i, Section j) {
    return i.x2 < j.x2;
}
void merge(Section*& M, Section*& tmp, int start1, int start2, int end, bool (*comp)(Section i, Section j)) {
    int index = start1;
    int i = start1;
    int j = start2;
    while (true) {
        if (comp(M[i], M[j])) {
            tmp[index++] = M[i++];
        }
        else {
            int c = 1;
            counter += (start2 - i);
            /*if (comp(M[j], M[i])) {
                tmp[index++] = M[j++];
            }
            else { tmp[index++] = M[i++]; }*/
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
        /*for (int i = 0; i < n; ++i) {
            cout << M[i].x2 << " ";
        }
        cout << endl;
        for (int i = 0; i < n; ++i) {
            cout << tmp[i].x2 << " ";
        }
        if (counter == 2) {
            ++counter;
            --counter;
        }
        cout << endl;
        cout << counter;
        cout << endl;*/

    }
    if (!tmpOrder) {
        std::swap(M, tmp);
    }
    delete[] tmp;
}

int main(int argc, const char* argv[]) {
    std::ifstream in(argv[1]);
    int n = 0;
    in >> n;
    Section* M = new Section[n];
    for (int i = 0; i < n; ++i) {
        in >> M[i].x1;
        in >> M[i].x2;
    }
    MergeSort(M, n, compX1);
    counter = 0;
    for (int i = 0; i < n - 1; ++i) {
        int a = 1;
        while ((i < n - 1) && (M[i].x1 == M[i + 1].x1)) {
            counter += a;
            ++a;
            ++i;
        }
    }
    MergeSort(M, n, compX2);

    std::cout << counter;
    delete[] M;
    return 0;
}
