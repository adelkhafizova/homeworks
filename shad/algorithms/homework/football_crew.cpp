#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class Player {
public:
  Player(int number, int effectiveness) {
    number_ = number;
    effectiveness_ = effectiveness;
  }
  bool operator < (const Player &right_player) {
    return this->effectiveness_ < right_player.effectiveness_;
  }
private:
  int number_;
  int effectiveness_;
};

template <typename RandomAccessIterator>
void quicksort(RandomAccessIterator begin, RandomAccessIterator end) {
  if (begin != end) {
    std::cout << *begin << std::endl;
    std::cout << *(end-1) << std::endl;
    RandomAccessIterator left = begin;
    RandomAccessIterator right = end - 1;
    RandomAccessIterator middle = left + ((right - left) / 2);
    RandomAccessIterator median = (*left > *middle) ? middle : left;
    median = (*median < *right) ? right : median;
    while (left < right) {
      while (*left <= *median && left != (end - 1)) {
        ++left;
      }
      while (*median <= *right && right != begin) {
        --right;
      }
      if (left < right) {
        std::iter_swap(left, right);
        ++left;
        --right;
      }
    }
    std::iter_swap(left, median);
    quicksort(begin, left);
    quicksort(left + 1, end);
    //quicksort(begin, median);
    //quicksort(median+1, end); 
  }
}

int main() {
  std::vector<int> data;
  int size = 0;
  std::cin >> size;
  for (int i = 0; i < size; i++) {
    int temp;
    std::cin >> temp;
    data.push_back(temp);
  }
  std::vector<int> data2(data);
  quicksort(data.begin(), data.end());
  std::sort(data2.begin(), data2.end());
  for (int i = 0; i < size; i++) {
    std::cout << data[i] << ' ';
  }
  std::cout << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << data2[i] << ' ';
  }
  std::cout << std::endl;
}
