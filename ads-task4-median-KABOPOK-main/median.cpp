#include <iostream>
#include <fstream>

struct Student {
    int ID;
    double GPA;
};

//void printToConsole(int start, int end, Student* M) {
//    for (int i = start; i <= end; ++i) {
//        std::cout << M[i].GPA << " ";
//    }
//    std::cout << '\n';
//}

int main(int argc, const char* argv[]) {
    std::ifstream inFile(argv[1]);
    int n;
    inFile >> n;
    double x;
    Student* M = new Student[n];
    for (int i = 0; i < n; ++i) {
        inFile >> x;
        M[i].GPA = x;
        M[i].ID = i+1;
    }
    double max = 0;
    double min = std::numeric_limits<double>::max();
    int maxID = 0;
    int minID = 0;
    for(int i =0; i < n; ++i){
        if (M[i].GPA < min) { min = M[i].GPA; minID = M[i].ID; }
        if (M[i].GPA > max) { max = M[i].GPA; maxID = M[i].ID; }
    }
    int left = 0;
    int right = n - 1;
    int oldLeft = left;
    int oldRight = right;
    while (oldLeft - oldRight != -1) {
        left = oldLeft;
        right = oldRight;
        int random = left + rand() % (right - left);
        //printToConsole(oldLeft, oldRight, M);
        double supportElement = M[random].GPA;
        while (right > left) {
            while (M[left].GPA < supportElement) { ++left; }
            while (M[right].GPA > supportElement) { --right; }
            if (left < right) {
                std::swap(M[left], M[right]);
            }
            //printToConsole(oldLeft, oldRight, M);
        }
        if (n-right < left) {
            oldRight = right;
        }
        else {
            oldLeft = right;
        }
        //std::cout << '\n';
    }
    std::cout << minID << " " << M[oldLeft].ID << " " << maxID;
    delete[] M;
    return 0;
}
