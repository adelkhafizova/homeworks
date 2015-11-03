#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int a, n;
    std::cin >> a >> n;
    std::vector<bool> degree_bits;
    int temp;
    while (true) {
        bool digit = n % 2;
        n = n / 2;
        if (n == 0) {
            degree_bits.push_back(n % 2 ? false : true);
            break;
        }
        degree_bits.push_back(digit);
    }
    std::reverse(degree_bits.begin(), degree_bits.end());
    std::vector<int> cache(degree_bits.size(), 1);
    int degree = degree_bits.size() - 1;
    while (degree >= 0) {
        if (degree_bits[degree]) {
            cache[degree] = a;
        }
        a*=a;
        --degree;
    }
    int result = 1;
    for (int i = 0; i < cache.size(); i++) {
        result *= cache[i];
    }
    std::cout << result << std::endl;
}
