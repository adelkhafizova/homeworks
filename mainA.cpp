#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> solution(const std::vector<int> &data) {
    std::vector<int> increment(data.size(), 1), decrement(data.size(), 1);
    std::vector<int> indexes_incr(data.size(), -1), indexes_decr(data.size(), -1);
    for (size_t first_index = 0; first_index < data.size(); ++first_index) {
        for (size_t second_index = 0; second_index < first_index; ++second_index) {
            if (data[second_index] > data[first_index]) {
                if (increment[first_index] < decrement[second_index] + 1) {
                    increment[first_index] = decrement[second_index] + 1;
                    indexes_incr[first_index] = static_cast<int>(second_index);
                }
            } else {
                if (data[first_index] != data[second_index]) {
                    if (decrement[first_index] < increment[second_index] + 1) {
                        decrement[first_index] = increment[second_index] + 1;
                        indexes_decr[first_index] = static_cast<int>(second_index);
                    }
                }
            }
        }
    }

    int first_answer = increment[0], first_position = 0;
    int second_answer = decrement[0], second_position = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (increment[i] > first_answer) {
            first_answer = increment[i];
            first_position = i;
        }
        if (decrement[i] > second_answer) {
            second_answer = decrement[i];
            second_position = i;
        }
    }
    int pos = (first_answer > second_answer) ? first_position : second_position;
    std::vector<int> path;
    bool indexes_incr_flag = false;
    if (first_answer > second_answer) {
        indexes_incr_flag = true;
    }
    while (pos != -1) {
        path.push_back(pos);
        if (indexes_incr_flag) {
            pos = indexes_incr[pos];
            indexes_incr_flag = false;
        } else {
            pos = indexes_decr[pos];
            indexes_incr_flag = true;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> data(size);
    for (size_t i = 0; i < data.size(); ++i) {
        std::cin >> data[i];
    }
    std::vector<int> result = solution(data);
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << data[result[i]] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
