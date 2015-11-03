#include <iostream>
#include <string>

int main() {
    char v[] = "Hello";
    char u[12];
    for (int i = 0; i < 5; i++)
        u[i] = v[i];
    //std::cout << u;

    std::string s("Hello, world");
    s[3] = '\0';
    std::cout << s << std::endl << s.c_str() << std::endl;
    s.shrink_to_fit();
    std::cout << s.size() << std::endl;
}
