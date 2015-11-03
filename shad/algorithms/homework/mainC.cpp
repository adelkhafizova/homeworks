#include <vector>
#include <iostream>
#include <algorithm>


int FindMaxLength(std::vector<int> &x_coords, std::vector<int> &y_coords, 
                  std::vector<int> &z_coords) {
  std::vector<int> counted_lengths(x_coords.size(), 1);
  for (int i = 0; i < x_coords.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (x_coords[j] < x_coords[i] && y_coords[j] < y_coords[i] && 
          z_coords[j] < z_coords[i]) {
        counted_lengths[i] = std::max(counted_lengths[i], 
                                      counted_lengths[j] + 1);
      }
    }
  }
  return *std::max_element(counted_lengths.begin(), counted_lengths.end());
}

void ReadData(std::vector<int> &x_coords, std::vector<int> &y_coords, 
              std::vector<int> &z_coords, std::istream &in_stream = std::cin) {
  int data_num = 0;
  in_stream >> data_num;
  x_coords.reserve(data_num);
  y_coords.reserve(data_num);
  z_coords.reserve(data_num);
  int temp_coord;
  for (int i = 0; i < data_num; ++i) {
    in_stream >> temp_coord;
    x_coords.push_back(temp_coord);
    in_stream >> temp_coord;
    y_coords.push_back(temp_coord);
    in_stream >> temp_coord;
    z_coords.push_back(temp_coord);
  }
}

void WriteLength(int &max_length, std::ostream &out_stream = std::cout) {
  out_stream << max_length << std::endl;
}

int main() {
  std::vector<int> x_coords;
  std::vector<int> y_coords;
  std::vector<int> z_coords;
  ReadData(x_coords, y_coords, z_coords);
  int max_length = FindMaxLength(x_coords, y_coords, z_coords);
  WriteLength(max_length);
}

