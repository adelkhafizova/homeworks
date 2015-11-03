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

vector<int> CalculateMaxAlternationSequence(const vector<int>& sequence)
{
    unsigned size_of_sequence = sequence.size();
    vector<int> reverse_sequence(size_of_sequence);
    reverse_copy(sequence.begin(), sequence.end(), reverse_sequence.begin());

    vector<Element_Data> optimal_previous_member(size_of_sequence);

    /* Вычисляем некоторые значения */
    for (unsigned index_member = 0; index_member < size_of_sequence; ++index_member)
    {
        for (
                unsigned index_previous_members = 0; 
                index_previous_members < index_member; 
                ++index_previous_members
        )
        {
            if (reverse_sequence[index_previous_members] > reverse_sequence[index_member])
            {
                if (optimal_previous_member[index_member].max_size_decrease <=
                        optimal_previous_member[index_previous_members].max_size_increase + 1
                ) {
                    optimal_previous_member[index_member].max_size_decrease =
                            optimal_previous_member[index_previous_members].max_size_increase + 1;
                    optimal_previous_member[index_member].index_of_predok_decrease = 
                                index_previous_members;
                }
            }

            if (reverse_sequence[index_previous_members] < reverse_sequence[index_member])
            {
                if (optimal_previous_member[index_member].max_size_increase <=
                        optimal_previous_member[index_previous_members].max_size_decrease + 1
                ) {
                    optimal_previous_member[index_member].max_size_increase =
                        optimal_previous_member[index_previous_members].max_size_decrease + 1;
                    optimal_previous_member[index_member].index_of_predok_increase = 
                        index_previous_members;
                }
            }
        }

        if (optimal_previous_member[index_member].max_size_increase == (unsigned)0)
        {
            optimal_previous_member[index_member].max_size_increase = (unsigned)1;
            optimal_previous_member[index_member].index_of_predok_increase = index_member;
        }
        if (optimal_previous_member[index_member].max_size_decrease == (unsigned)0)
        {
            optimal_previous_member[index_member].max_size_decrease = 1;
            optimal_previous_member[index_member].index_of_predok_decrease = index_member;
        }
    }

    /* Ищем последний индекс, на котором достигается максимум */
    unsigned max_size_subsequence = 0;
    unsigned last_index_subsequence = 0;
    for (unsigned index_member = 0; index_member < size_of_sequence; ++index_member)
    {
        if (optimal_previous_member[index_member].max_size_increase >= max_size_subsequence)
        {
            max_size_subsequence = optimal_previous_member[index_member].max_size_increase;
            last_index_subsequence = index_member;
        }

        if (optimal_previous_member[index_member].max_size_decrease >= max_size_subsequence)
        {
            max_size_subsequence = optimal_previous_member[index_member].max_size_decrease;
            last_index_subsequence = index_member;
        }
    }

    vector<int> max_alternation_subsequence(0);
    unsigned next_index;
    bool increase;

    max_alternation_subsequence.push_back(reverse_sequence[last_index_subsequence]);

    if (
            optimal_previous_member[last_index_subsequence].max_size_increase
            < optimal_previous_member[last_index_subsequence].max_size_decrease
    ) {
        next_index = optimal_previous_member[last_index_subsequence].index_of_predok_decrease;
        increase = false;
    } else if (
            optimal_previous_member[last_index_subsequence].max_size_increase
            > optimal_previous_member[last_index_subsequence].max_size_decrease
    ) {
        next_index = optimal_previous_member[last_index_subsequence].index_of_predok_increase;
        increase = true;
    } else {
        next_index = max(
                optimal_previous_member[last_index_subsequence].index_of_predok_increase,
                optimal_previous_member[last_index_subsequence].index_of_predok_decrease
                );
        increase = 
         (next_index == optimal_previous_member[last_index_subsequence].index_of_predok_increase);
    }

    while (next_index != last_index_subsequence)
    {
        last_index_subsequence = next_index;
        max_alternation_subsequence.push_back(reverse_sequence[last_index_subsequence]);

        if (increase == false)
        {
            next_index = optimal_previous_member[last_index_subsequence].index_of_predok_increase;
        } else {
            next_index = optimal_previous_member[last_index_subsequence].index_of_predok_decrease;
        }

        increase = !increase;
    }

    return max_alternation_subsequence;
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
		sequence[i] = rand() % 1000000;
	}
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
