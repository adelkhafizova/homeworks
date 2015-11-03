#include <vector>
#include <iostream>
#include <algorithm>

class heap_element {
public:
  heap_element() {
  }
  heap_element(int value, int array_number) {
    value_ = value;
    array_number_ = array_number;
  }
  int get_value() {
    return value_;
  }
  int get_array_number() {
    return array_number_;
  }
  bool operator < (const heap_element &rhe) {
    return this->value_ < rhe.value_;
  }

private:
  int array_number_;
  int value_;
};

class Heap {
public:
  explicit Heap(std::vector<heap_element> &array) {
    heap_ = std::vector<heap_element>(array.begin(), array.end());
    length_ = heap_.size();
    BuildHeap();
  }

  void Heapify(size_t current) {
    size_t left_child = 2 * current + 1;
    size_t right_child = 2 * current + 2;
    size_t smallest = current;
    if (left_child < length_ && heap_[left_child] < heap_[smallest]) {
      smallest = left_child;
    }
    if (right_child < length_ && heap_[right_child] < heap_[smallest]) {
      smallest = right_child;
    }
    if (smallest != current) {
      std::swap(heap_[current], heap_[smallest]);
      Heapify(smallest);
    }
  }

  void BuildHeap() {
    for (size_t i = length_ / 2 - 1; i != (size_t)(-1); --i) {
      Heapify(i);
    }
  }

  void HeapInsertKey(size_t current, heap_element key) {
    heap_[current] = key;
    size_t parent = (current - 1)/2;
    while (current > 0 && (heap_[current] < heap_[parent])) {
      std::swap(heap_[parent], heap_[current]);
      current = parent;
      parent = (current - 1)/2;
    }
  }

  void HeapInsert(heap_element key) {
    ++length_;
    if (length_ > heap_.size()) {
      heap_.resize(length_*2);
    }
    HeapInsertKey(length_ - 1, key);
  }

  heap_element HeapExtract() {
    if (length_ == 0) {
      heap_element to_return(-1, -1);
      return to_return;
    }
    heap_element min_element = heap_[0];
    heap_[0] = heap_[length_ - 1];
    --length_;
    Heapify(0);
    return min_element;
  }

private:
  std::vector<heap_element> heap_;
  int length_;
};

std::vector<std::vector<int> > ReadSorted(std::istream &input_stream = std::cin) {
  int sorted_number, number_in_sorted;
  input_stream >> sorted_number >> number_in_sorted;
  std::vector<std::vector<int> > data;
  std::vector<int> sorted(number_in_sorted, 0);
  for (int i = 0; i < sorted_number; ++i) {
    data.push_back(sorted);
  }
  for (int i = 0; i < sorted_number; ++i) {
    for (int j = 0; j < number_in_sorted; ++j) {
      int current = 0;
      input_stream >> current;
      data[i][j] =  current;
    }
  }
  return data;
}

std::vector<int> MergeSorted(std::vector<std::vector<int> > &data) {
  std::vector<int> indexes(data.size(), 0);
  std::vector<int> final_data(data.size()*data[0].size(), 0);
  int index = 0;
  std::vector<heap_element> first_elements;
  first_elements.reserve(data.size());
  for (int i = 0; i < data.size(); ++i) {
    heap_element element = heap_element(data[i][0], i);
    first_elements.push_back(element);
  }
  Heap min_heap = Heap(first_elements);
  while (index < final_data.size()) {
    heap_element current_minimum = min_heap.HeapExtract();
    final_data[index] = current_minimum.get_value();
    int array_index = current_minimum.get_array_number();
    int index_in_sorted = ++indexes[current_minimum.get_array_number()];
    if (indexes[current_minimum.get_array_number()] < data[0].size()) {
      heap_element next_element = heap_element(data[array_index][index_in_sorted], array_index);
      min_heap.HeapInsert(next_element);
    }
    ++index;
  }
  return final_data;
}

int main() {
  std::vector<std::vector<int> > data = ReadSorted();
  std::vector<int> final_data = MergeSorted(data);
  for (int i = 0; i < final_data.size(); ++i) {
    std::cout << final_data[i] << ' ';
  }
  std::cout << std::endl;
}
