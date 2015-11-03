#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

template <typename T>
struct TLessCmp {
    static unsigned int CmpCount;
    bool operator ()(const T& lhs, const T& rhs) const {
	CmpCount++;
	return lhs < rhs;
    }; 
};

template <typename T>
unsigned int TLessCmp<T>::CmpCount = 0;

int main() {
    std::vector<int> array(20);
    static std::uniform_int_distribution<int> distribution(0, 1000);
    static std::default_random_engine generator;
    std::generate(array.begin(), array.end(), []() { return distribution(generator); });
    for (int i = 0; i < array.size(); ++i) {
	std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    //TLessCmp comparator;
    std::sort(array.begin(), array.end(), TLessCmp<int>());
    std::sort(array.begin(), array.end(), TLessCmp<int>());
    for (int i = 0; i < array.size(); ++i) {
	std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << TLessCmp<int>::CmpCount/20 << std::endl;
}
