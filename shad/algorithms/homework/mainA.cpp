#include <iostream>
#include <vector>
#include <algorithm>


std::vector<int> solution(const std::vector<int> &data) {
    std::vector<int> increment(data.size(), 1), decrement(data.size(), 1);
    std::vector<int> indexes_incr(data.size(), -1), indexes_decr(data.size(), -1);
    for (size_t first_index = 0; first_index < data.size(); ++first_index) {
        for (size_t second_index = 0; second_index < first_index; ++second_index) {
            if (data[second_index] > data[first_index]) {
                if ((increment[first_index] < decrement[second_index] + 1) ||
                    ((increment[first_index] == decrement[second_index] + 1) &&
                     (indexes_decr[second_index] < indexes_decr[indexes_incr[first_index]]))) {
                    increment[first_index] = decrement[second_index] + 1;
                    indexes_incr[first_index] = static_cast<int>(second_index);
                }
            } else {
                if (data[first_index] != data[second_index]) {
                    if ((decrement[first_index] < increment[second_index] + 1) ||
                        ((decrement[first_index] == increment[second_index] + 1) &&
                         (indexes_incr[second_index] < indexes_incr[indexes_decr[first_index]]))) {
                        decrement[first_index] = increment[second_index] + 1;
                        indexes_decr[first_index] = static_cast<int>(second_index);
                    }
                }
            }
        }
    }

    int first_answer = increment[0], first_position = 0, prev_first_position = indexes_incr[0];
    int second_answer = decrement[0], second_position = 0, prev_second_position = indexes_decr[0];
    for (int index = 0; index < data.size(); ++index) {
        if (increment[index] > first_answer ||
            ((increment[index] == first_answer) && (indexes_incr[index] < prev_first_position))) {
            first_answer = increment[index];
            first_position = index;
            prev_first_position = indexes_incr[index];
        }
        if (decrement[index] > second_answer ||
            ((decrement[index] == second_answer) && (indexes_decr[index] < prev_second_position))) {
            second_answer = decrement[index];
            second_position = index;
            prev_second_position = indexes_decr[index];
        }
    }
    std::vector<int> result_increment, result_decrement;
    while (indexes_incr[first_position] != -1) {
        result_increment.push_back(first_position);
        first_position = indexes_incr[first_position];
        if (indexes_decr[first_position] == -1) {
            break;
        } else {
            result_increment.push_back(first_position);
            first_position = indexes_decr[first_position];
        }
    }
    result_increment.push_back(first_position);
    while (indexes_decr[second_position] != -1) {
        result_decrement.push_back(second_position);
        second_position = indexes_decr[second_position];
        if (indexes_incr[second_position] == -1) {
            break;
        } else {
            result_decrement.push_back(second_position);
            second_position = indexes_incr[second_position];
        }
    }
    result_decrement.push_back(second_position);
    std::reverse(result_decrement.begin(), result_decrement.end());
    std::reverse(result_increment.begin(), result_increment.end());

    if (result_decrement.size() > result_increment.size()) {
        return result_decrement;
    } else {
        if (result_increment.size() > result_decrement.size()) {
            return result_increment;
        } else {
            if (*(result_decrement.end() - 1) < *(result_increment.end() - 1)) {
                result_decrement;
            } else {
                if (*(result_decrement.end() - 1) == *(result_increment.end() - 1)&&
                    *(result_decrement.end() - 2) < *(result_increment.end() - 2)) {
                    return result_decrement;
                } else {
                    return result_increment;
                }
            }
        }
    }
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
