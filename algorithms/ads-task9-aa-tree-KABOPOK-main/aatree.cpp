#include "AATree.h"
int main(int argc, const char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    int n = 0;
    int x = 0;
    char s=0;
    AATree mTree;
    in >> n;
    in.ignore();
    while (n != 0) {
        --n;
        in >> s;
        in >> x;
        switch (s) {
            case '+':
                if (x == 6) {
                    std::cout << " ";
                }
                mTree.insert(x);
                out << mTree.getBalance() << std::endl;
                break;
            case '-':
                mTree.erase(x);
                out << mTree.getBalance() << std::endl;
                break;
            case '?':
                mTree.find(x) != nullptr ? out << "true" : out << "false";
                out << std::endl;
                break;
        }
    }

}
