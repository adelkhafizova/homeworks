//============================================================================
// Name        : task_1_1.cpp
// Author      : Nikita Volkov
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::reverse_copy;
using std::max;

struct Element_Data {
    unsigned max_size_increase;
    unsigned max_size_decrease;
    unsigned index_of_predok_increase;
    unsigned index_of_predok_decrease;
};

vector<int> ReadData()
{
    unsigned size_of_sequence;
    cin >> size_of_sequence;
    vector<int> sequence(size_of_sequence);
    for (unsigned index_element = 0; index_element < size_of_sequence; ++index_element)
    {
        cin >> sequence[index_element];
    }
    return sequence;
}

void WriteData(const vector<int>& subsequence)
{
    unsigned subsequence_size = subsequence.size();
    for (unsigned index_member = 0; index_member < subsequence_size; ++index_member)
    {
        cout << subsequence[index_member] << " ";
    }
    cout << endl;
}

vector<int> CalculateMaxAlternationSequence(const vector<int>& data) {
    std::vector<int> increment(data.size(), 1), decrement(data.size(), 1);
    std::vector<int> indexes_incr(data.size(), -1), indexes_decr(data.size(), -1);
    for (size_t first_index = 0; first_index < data.size(); ++first_index) {
        for (size_t second_index = 0; second_index < first_index; ++second_index) {
            if (data[second_index] > data[first_index]) {
                if ((increment[first_index] < decrement[second_index] + 1) ||
                    ((increment[first_index] == decrement[second_index] + 1) &&
                     (indexes_decr[second_index] < indexes_decr[indexes_incr[first_index]]))){
                    increment[first_index] = decrement[second_index] + 1;
                    indexes_incr[first_index] = static_cast<int>(second_index);
                }
            } else {
                if (data[first_index] != data[second_index]) {
                    if ((decrement[first_index] < increment[second_index] + 1) ||
                        ((decrement[first_index] == increment[second_index] + 1) &&
                         (indexes_incr[second_index] < indexes_incr[indexes_decr[first_index]]))){
                        decrement[first_index] = increment[second_index] + 1;
                        indexes_decr[first_index] = static_cast<int>(second_index);
                    }
                }
            }
        }
    }

    int first_answer = increment[0], first_position = 0, prev_first_position = indexes_incr[0];
    int second_answer = decrement[0], second_position = 0, prev_second_position = indexes_decr[0];
    for (int i = 0; i < data.size(); ++i) {
        if (increment[i] > first_answer ||
            ((increment[i] == first_answer) && (indexes_incr[i] < prev_first_position))) {
            first_answer = increment[i];
            first_position = i;
            prev_first_position = indexes_incr[i];
        }
        if (decrement[i] > second_answer ||
            ((decrement[i] == second_answer) && (indexes_decr[i] < prev_second_position))) {
            second_answer = decrement[i];
            second_position = i;
            prev_second_position = indexes_decr[i];
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

    std::cout << "Calculated max alternating subsequence" << std::endl;

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

bool CheckToCorrectSequence(const vector<int> &sequence)
{
	unsigned sequence_size = sequence.size();
	if (sequence_size < 3)
	{
		return true;
	}

	bool changed = (sequence[0] > sequence[1]);
	for (unsigned i = 2; i < sequence_size; ++i)
	{
		if (changed == (sequence[i - 1] > sequence[i]))
		{
			return false;
		}
		changed = !changed;
	}
	return true;
}

vector<int> GenerateSequence()
{
	unsigned sequence_size = 1 + rand() % 30;
	vector<int> sequence(sequence_size);
	for (unsigned i = 0; i < sequence_size; ++i)
	{
		sequence[i] = rand() % 1000;
    std::cout << sequence[i] << ' ';
	}
  std::cout << std::endl << "Generated sequence" << std::endl;
	return sequence;
}

unsigned CheckMaximum(const vector<int>& sequence)
{
	unsigned sequence_size = sequence.size();
	unsigned maximum = 0;
	for (unsigned mask = 0; mask < ((unsigned)1 << sequence_size); ++mask)
	{
		vector<int> subsequence(0);
		for(unsigned i = 0; i < sequence_size; ++i)
		{
			if (mask & (1 << i))
			{
				subsequence.push_back(sequence[i]);
			}
		}



		bool true_sequence = CheckToCorrectSequence(subsequence);
//		for (int i = 0; (i < (int)subsequence.size() - 1) && true_sequence; ++i)
//		{
			//cout << "here " << mask << " " << some_cubes.size()<< endl;
//			true_sequence = IsEmbeddedCube(some_cubes[i], some_cubes[i + 1]);
//		}

		if (true_sequence && maximum < subsequence.size())
		{
			maximum = subsequence.size();
		}
	}
	return maximum;
}

void PerformStressTest(unsigned test_count)
{
	bool everything_ok = true;
	for (unsigned number_test = 0; (number_test < test_count) && everything_ok; ++number_test)
	{
		cout << "test #" << number_test << endl;
		vector<int> sequence = GenerateSequence(); //cout << "ok" << endl;
		vector<int> subsequence = CalculateMaxAlternationSequence(sequence);//cout << "ok" << endl;
		unsigned max = CheckMaximum(sequence);
		if (CheckToCorrectSequence(subsequence) == false)
		{
			cout << "FAIL: incorrect sequence" << endl;
			cout << "sequence: ";
			WriteData(sequence);
			cout << "subsequence: ";
			WriteData(subsequence);
			everything_ok = false;
		} else if (subsequence.size() != max)
		{
			cout << "FAIL: not max sequence" << endl;
			cout << "true maximum: " << max << endl;
			cout << "calculate maximum: " << subsequence.size();
			cout << "sequence: ";
			WriteData(sequence);
			cout << "subsequence: ";
			WriteData(subsequence);
			everything_ok = false;
		}
	}
	cout << everything_ok;
}

int main()
{
	PerformStressTest(10);
//	vector<int> sequence = ReadData();
//	cout << CheckToCorrectSequence(sequence) << endl;
//	vector<int> subsequence = CalculateMaxAlternationSequence(sequence);
//	WriteData(subsequence);
	return 0;
}

//int main()
//{
//    vector<int> sequence = ReadData();
//    vector<int> subsequence = CalculateMaxAlternationSequence(sequence);
//    WriteData(subsequence);
//    return 0;
//}
