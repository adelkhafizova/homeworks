#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int main() {
    std::cout << "Enter filename" << std::endl;
    std::string filename;
    std::cin >> filename;
    std::cout << "Enter string" << std::endl;
    std::string word;
    std::cin >> word;
    std::cout << "Enter number of context words" << std::endl;
    int n;
    std::cin >> n;
    std::vector<std::string> text;
    std::ifstream ifs(filename);
    int count = 0;
    while (ifs.good()) {
        std::string temp;
        ifs >> temp;
        if (ifs.good()) {
            text.push_back(temp);
            if (temp == word) 
                count++;
        }
    }
    std::cout << "Number of entries of word " << word << " is " << count << std::endl;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == word) {
            int back = 1;
            while (back <= n && (i - back) >= 0) {
                std::cout << text[i - back] << ' ';
                back++;
            }
            std::cout << word;
            int forward = 1;
            while (forward <= n && (i + forward) < text.size()) {
                std::cout << ' ' << text[i + forward];
                forward++;
            }
            std::cout << std::endl;
        }
    }
    
}
