#include <iostream>
#include <cmath>


int strlen(const char* str) {
    int size = 0;
    while (*str++ != '\0') {
        size++;
    }
    return size;
}

int atoi(const char* number_string) {
    int number = 0;
    int degree = strlen(number_string) - 1;
    do {
        number += pow(10, degree--)*(*number_string++ - '0');
    } while (*number_string != '\0');
    return number;
}

int main() {
    std::cout << atoi("123") + 1 << std::endl;
}
