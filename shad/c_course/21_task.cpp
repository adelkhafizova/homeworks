#include <iostream>

int strlen(const char* str) {
    int size = 0;
    while (*str++ != '\0') {
        size++;
    }
    return size;
}

char* strcat(char* destination, const char* source) {
    char* write_section = destination + strlen(destination);
    while (*source != '\0') {
        *write_section++ = *source++;
    }
    return destination;
}

char* strrev(char* destination, const char* source) {
    char* write_section = destination + strlen(source);
    *write_section-- = '\0';
    while (*source != '\0') {
        *write_section-- = *source++;
    }
    return destination;
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1++ == *str2++) {}
    if (*str1 < *str2)
        return 1;
    else 
        if (*str1 == *str2)
            return 0;
        else
            return -1;
}

void buffer_init(char* buffer, const char* source) {
    do {
        *buffer++ = *source++;
    }
    while (*source != '\0');
    *buffer = '\0';
}

int main() {
    char s[] = "";
    std::cout << strlen(s) << std::endl;
    char buffer[1000];
    buffer_init(buffer, "Hello");
    char t[] = ", world!";
    std::cout << strcat(buffer, t) << std::endl;
    std::cout << strrev(buffer, "Reversed string") << std::endl;
    std::cout << strcmp("hello", "") << std::endl;
}
