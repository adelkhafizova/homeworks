#include <iostream>

int strlen(const char* str) {
    int size = 0;
    while (*str++ != '\0') {
        size++;
    }
    return size;
}

char get_char(int num) {
    if (0 <= num && num <= 9)
        return ('0' + num);
    else {
        switch (num) {
            case 10:
                return 'A';
            case 11:
                return 'B';
            case 12:
                return 'C';
            case 13:
                return 'D';
            case 14:
                return 'E';
            case 15:
                return 'F';
        }
    }
}

char* strrev(char* destination, const char* source) {
    char* write_section = destination + strlen(source);
    *write_section-- = '\0';
    while (*source != '\0') {
        *write_section-- = *source++;
    }
    return destination;
}

char* itoa(unsigned int value, char* str, unsigned int base) {
    char* begin = str;
    do {
        *str++ = get_char(value % base);
        value /= base;
    } while ( value != 0);
    *str = '\0';
    return begin;
}

int main() {
    char buffer1[1000];
    char buffer2[1000];
    std::cout << strrev(buffer2, itoa(2047, buffer1, 16)) << std::endl;
}
