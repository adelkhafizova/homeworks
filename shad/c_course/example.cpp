#include <iostream>

int main() {
    int a = 1;
    const int &b = a;
    a = 2;
    std::cout << b << std::endl;
}
