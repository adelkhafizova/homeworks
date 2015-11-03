#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main() {
    std::ifstream ifs("data/text.txt");
    std::map<std::string, int> entry_number;
    std::string temp;
    while (ifs.good()) {
        ifs >> temp;
        if (ifs.good())
            entry_number[temp] += 1;
    }
    for (auto it = entry_number.begin(); it != entry_number.end(); it++) {
        std::cout << it->first << ' ' << it->second << std::endl;
    }
}
