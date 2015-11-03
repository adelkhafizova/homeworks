#include <iostream>
#include <vector>

bool getBit(int data, int pos) {
    if (data & (1 << pos))
        return true;
    else
        return false;
}

void setBit(int * const data, int pos, int value) {
    if (!value) {
        *data = *data & (~(1 << pos));
    }
    else {
        *data = *data | (1 << pos);
    }
}

int main() {
    int a = 3;
    std::cout << getBit(a, 2) << std::endl;
    setBit(&a, 4, 1);
    std::cout << a << std::endl;
}
