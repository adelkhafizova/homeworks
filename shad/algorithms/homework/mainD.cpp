#include <vector>
#include <iostream>
#include <deque>


void set_query_maximum(char query, int &left_index, int &right_index, 
                       std::vector<int> &input_data, 
                       std::deque<int> &max_deque, int &current_maximum) {
  if (query == 'R') {
    ++right_index;
    while (max_deque.size() && input_data[right_index] > max_deque.back()) {
      max_deque.pop_back();
    }                      
    max_deque.push_back(input_data[right_index]);
    current_maximum = max_deque.front();
  } else {
    ++left_index;
    if (input_data[left_index - 1] == max_deque.front()) {
      max_deque.pop_front();
    }
    current_maximum = max_deque.front();
  }
}

std::vector<int> ReadData(std::istream &input_stream = std::cin) {
  int data_number;
  input_stream >> data_number;
  std::vector<int> input_data;
  input_data.reserve(data_number);
  for (int i = 0; i < data_number; ++i) {
    int current_number;
    input_stream >> current_number;
    input_data.push_back(current_number);
  }
  return input_data;
}

void ProcessQueries(std::istream &input_stream, std::vector<int> &input_data, 
                    std::vector<int> &max_data) {
  int number_of_queries = 0;
  input_stream >> number_of_queries;
  
  max_data.reserve(input_data.size());

  int left_index = 0;
  int right_index = 0;
  
  std::deque<int> max_deque;
  int current_maximum = *input_data.begin();
  max_deque.push_back(current_maximum);

  while (number_of_queries) {
    char query = 0;
    input_stream >> query;
    set_query_maximum(query, left_index, right_index, input_data,
                      max_deque, current_maximum);
    max_data.push_back(current_maximum);
    number_of_queries--;
  }
}

void WriteMaximums(std::vector<int> &max_data, 
                   std::ostream &output_stream = std::cout) {
  for (int i = 0; i < max_data.size(); ++i) {
    output_stream << max_data[i];
    if (i != max_data.size() - 1) {
      output_stream << ' ';
    } else {
      output_stream << std::endl;
    }
  }
}

int main() {
  std::vector<int> input_data = ReadData();
  std::vector<int> max_data;
  ProcessQueries(std::cin, input_data, max_data);
  WriteMaximums(max_data);
}
