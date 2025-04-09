#include <iostream>
#include <fstream>
struct MinMax {
    int min_;
    int max_;
    int num_;
    MinMax(int num, int max, int min)
        : min_(min), max_(max), num_(num){}
    MinMax() = default;
};
template <typename T>
class Stack {
    T* M_;
    size_t size_;
    size_t capacity_;
public : 
    Stack() {
        M_ = new T[10];
        size_ = 0;
        capacity_ = 10;
    }
    Stack(size_t size) {
        M_ = new T[size];
        size_ = 0;
        capacity_ = size;
    }
    void pop() {
        if (size_ == 0) { throw std::empty("stack is empty"); }
        --size_;
    }
    void push(T x) {
        if (size_ == capacity_) {
            capacity_ *= 2;
            T* tmp = new T[capacity_];
            for (int i = 0; i < size_; ++i) {
                tmp[i] = M_[i];
            }
            delete[] M_;
            M_ = tmp;
        }
        M_[size_++] = x;
    }
    T& top() {
        return M_[size_ - 1];
    }
    size_t size() const { return size_; }
    ~Stack() {
        delete[] M_;
    }
};
class TwoStack {
private:
    Stack<int> putM_;
    Stack<MinMax> outM_;
    int max_;
    int min_;
public:
    TwoStack() {
        max_ = 0;
        min_ = 1000000;
    }
    void pop() {
        int outSize = outM_.size();
        if (outSize == 0) {
            int putSize = putM_.size();
            if (putSize == 0) { throw std::empty("stack is empty"); }
            int max = putM_.top();
            putM_.pop();
            int min = max;
            outM_.push(MinMax(max,min,max));
            --putSize;
            for (; putSize>0; --putSize) {
                int x = putM_.top();
                putM_.pop();
                if (max < x) { max = x; }
                if (x < min) { min = x; }
                outM_.push(MinMax(x, max, min));
            }
        }
        outM_.pop();
    }
    void push(int x) {
        if (putM_.size() == 0) { max_ = x; min_ = x;}
        if (x > max_) { max_ = x; }
        if (x < min_) { min_ = x; }
        putM_.push(x);
    }
    int getDifferent() {
        int outSize = outM_.size();
        int putSize = putM_.size();
        if (outSize + putSize < 2) { return 0; }
        if (outSize == 0) { return max_- min_; }
        if (putSize == 0) { return outM_.top().max_ - outM_.top().min_; }
        return std::max(max_, outM_.top().max_) - std::min(min_, outM_.top().min_);
    }
};
int main(int argc, const char* argv[])
{
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    int n = 0;
    int count = 0;
    in >> n;
    TwoStack stack;
    while (n > 0) {
        ++count;
        if (count == 100000) {
            --count;
        }
        char action;
        int number = 0;
        in >> action;
        switch (action)
        {
        case'+':
            in >> number;
            stack.push(number);
            break;
        case '-':
            stack.pop();
            break;
        case '?':
            out << stack.getDifferent() << '\n';
            break;
        default:
            out << "unknown command: " << action << '\n';
        }
        --n;
    }
    return 0;
}
