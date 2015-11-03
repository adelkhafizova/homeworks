#include <iostream>
#include <string>

int main() {
    while (std::cin.good()) {
        std::string to_check;
        std::getline(std::cin, to_check);
        bool is_palindrom = true;
        if (std::cin.good()) {
            for (auto i = 0; i < to_check.size()/2; i++) {
                if (to_check[i] != to_check[to_check.size() - 1 - i]) {
                    is_palindrom = false;
                    break;
                }
            }
            std::cout << (is_palindrom ? "a palindrom" : "not a palindrom") << std::endl;
        }
    }
}
