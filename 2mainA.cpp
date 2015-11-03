#include <vector>
#include <iostream>
#include <algorithm>

int FindLengthOfLongestCommonSubsequence
    (std::vector<int> first_sequence, std::vector<int> second_sequence) {
  std::vector<std::vector<int> > lcs;
  int yes = 0;
  lcs.reserve(first_sequence.size());
  for (int i = 0; i < first_sequence.size(); ++i) {
    std::vector<int> lcs_i (second_sequence.size(), 0);
    lcs.push_back(lcs_i);
  }
  for (int i = 0; i < first_sequence.size(); ++i) {
    if (first_sequence[i] == second_sequence[0]) {
      yes = 1;
    }
    lcs[i][0] = yes;
  }
  yes = 0;
  for (int j = 0; j < second_sequence.size(); ++j) {
    if (second_sequence[j] == first_sequence[0]) {
      yes = 1;
    }
    lcs[0][j] = yes;
  }
  for (int i = 1; i < first_sequence.size(); ++i) {
    for (int j = 1; j < second_sequence.size(); ++j) {
      if (first_sequence[i] == second_sequence[j]) {
        lcs[i][j] = lcs[i-1][j-1] + 1;
      } else {
        lcs[i][j] = std::max(lcs[i-1][j], lcs[i][j-1]);
      }
    }
  }
  return lcs[first_sequence.size() - 1][second_sequence.size() - 1];
}

std::vector<int> ReadSequence(std::istream &input_stream = std::cin) {
  int sequence_size;
  input_stream >> sequence_size;
  std::vector<int> sequence;
  sequence.reserve(sequence_size);
  for (int i = 0; i < sequence_size; ++i) {
    int current_number = 0;
    input_stream >> current_number;
    sequence.push_back(current_number);
  }
  return sequence;
}

int main() {
  std::vector<int> first_sequence = ReadSequence();
  std::vector<int> second_sequence = ReadSequence();
  std::cout << FindLengthOfLongestCommonSubsequence(first_sequence, second_sequence) << std::endl;
}
