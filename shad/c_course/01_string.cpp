#include <iostream>
#include <string>
#include <map>

int main() {
    std::string s = "abc";
    *s.begin(); // 'a'
    s.end(); 
    //auto instead of declaring type manually, compiler will insert necessary type
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << std::endl;
    }
    //'abcd' is hexadecimal constant
    //endl flushes the stream
    std::map<std::string, int> m;
    //if no such key, insert value via default constructor
    std::cout << m["abc"] << '\n'; //will print 0
    m[s] += 1;
    //map container is sorted via key
    auto it = m.find("a");
    if (it != m.end())
        std::cout << it->second << std::endl;
}
