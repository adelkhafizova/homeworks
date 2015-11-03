#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

bool operator < (const std::string& lh, const std::string& rh) {
    if (lh.size() < rh.size()) {
        return true;
    }
    else {
        if (lh.size() > rh.size()) {
            return false;
        }
        else {
            for (int i = 0; i < lh.size(); ++i) {
                int lhval = lh[i] - '0';
                int rhval = rh[i] - '0';
                if (lhval > rhval)
                    return false;
                else {
                    if (lhval < rhval)
                        return true;
                }
            }
            return false;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> strings(n, "");
    for (int i = 0; i < n; i++) {
        std::string temp;
        std::cin >> temp;
        strings[i] = temp;
    }
    std::sort(strings.begin(), strings.end());
    for (int i = 0; i < n; i++) {
        std::cout << strings[i] << std::endl;
    }
}
