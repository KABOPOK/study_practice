#include <iostream>
#include <fstream>
#include <cmath>

class OneStack {
private:
    int stack[52]{ 0 };
    int rightBorder;
    int leftBorder;
    int size = 0;
public:
    OneStack() {
        rightBorder = 0;
        leftBorder = 0;
    }
    int pop() {
        if (leftBorder == 52) { leftBorder = 0; }
        if (size == 0) { return -1;}
        --size;
        return stack[leftBorder++];
    }
    void push(int x) {
        if (rightBorder == 52) { rightBorder = 0; }
        if (size == 52) { throw std::overflow_error("Overflow"); }
        ++size;
        stack[rightBorder++] = x;
    }
};

int main(int argc, const char* argv[])
{
    std::ifstream cin(argv[1]);
    OneStack stack_1;
    OneStack stack_2;
    int HP = 1000000;
    int stack[52]{ 0 };
    int size = 0;
    for (int i = 0; i < 26; ++i) {
        char in[10];
        cin.getline(in,10);
        switch (in[0]) {
        case 'J':
            stack_1.push(11);
            break;
        case 'Q':
            stack_1.push(12);
            break;
        case 'K':
            stack_1.push(13);
            break;
        case 'A':
            stack_1.push(14);
            break;
        case '1':
            stack_1.push(10);
            break;
        default:
            stack_1.push((int)in[0] - '0');
        }
    }
    for (int i = 0; i < 26; ++i) {
        char in[10];
        cin.getline(in, 10);
        switch (in[0]) {
        case 'J':
            stack_2.push(11);
            break;
        case 'Q':
            stack_2.push(12);
            break;
        case 'K':
            stack_2.push(13);
            break;
        case 'A':
            stack_2.push(14);
            break;
        case '1':
            stack_2.push(10);
            break;
        default:
            stack_2.push((int)(in[0] - '0'));
        }
    }
    while (HP != 0) {
        if (size == 50) { 
            std::cout << "draw"; return 0; }
        int first = stack_1.pop();
        if (first == -1) { std::cout << "second";  return 0; }
        int second = stack_2.pop();
        if (second == -1) { std::cout << "first";  return 0; }
        if (abs(second - first) == 12) {
            if (first == 2) {
                for (int i = 0; i < size; ++i) {
                    stack_1.push(stack[i]);
                }
                size = 0;
                stack_1.push(first);
                stack_1.push(second);
            }
            else {
                for (int i = 0; i < size; ++i) {
                    stack_2.push(stack[i]);
                }
                size = 0;
                stack_2.push(first);
                stack_2.push(second);
            }
        }
        else if (first > second) {
            for (int i = 0; i < size; ++i) {
                stack_1.push(stack[i]);
            }
            size = 0;
            stack_1.push(first);
            stack_1.push(second);
        }
        else if(first < second){
            for (int i = 0; i < size; ++i) {
                stack_2.push(stack[i]);
            }
            size = 0;
            stack_2.push(first);
            stack_2.push(second);
        }
        else {
            stack[size++] = second;
            stack[size++] = first;
        }
        --HP;
    }
    std::cout << "unknown";
    return 0;
}
