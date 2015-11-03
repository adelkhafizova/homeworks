#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <functional>
#include <climits>
#include <iterator>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::swap;

struct Player {
    unsigned efficiency;
    size_t id;
};

bool ComparePlayersLessEfficiency(const Player& player_first, const Player& player_second)
{
    return player_first.efficiency < player_second.efficiency;
}

bool ComparePlayersLessId(const Player& player_first, const Player& player_second)
{
    return player_first.id < player_second.id;
}

// By QuicSort. Decides where to put the current element relative to the pivot.
// If they are equal, then the choice is random.
template <class RandomAccessIterator, class Compare>
bool CompareWithPivot(
        const RandomAccessIterator& element,
        const RandomAccessIterator& pivot,
        const Compare& comparator
) {
    return comparator(*element, *pivot) ||
            (
                    !(comparator(*element, *pivot))
                    && !(comparator(*pivot, *element))
                    && (rand() % 2 == 1)
            );
}

template <class RandomGenerator>
unsigned int GenerateRandom(unsigned int max_number, RandomGenerator& generator)
{
    std::uniform_int_distribution<int> distribution(0, max_number);
    return distribution(generator);
}

// By QuicSort. Select pivot element in partition
template <class RandomAccessIterator, class RandomGenerator>
RandomAccessIterator SelectPivot(
        const RandomAccessIterator& left,
        const RandomAccessIterator& right,
        RandomGenerator& generator
) {
    return right - GenerateRandom(right - left - 1, generator) - 1;
}

// Partition the array into 2 parts - lower than pivot and large than it.
// Returns an iterator to the supporting element.
template <class RandomAccessIterator, class Compare, class RandomGenerator>
RandomAccessIterator PartitionSequence(
        const RandomAccessIterator& left,
        const RandomAccessIterator& right,
        const Compare& comparator,
        RandomGenerator& generator
) {
    swap(*(right - 1), *SelectPivot(left, right, generator));
    RandomAccessIterator pivot = (right - 1);
    RandomAccessIterator left_bound = left;
    for (
            RandomAccessIterator right_bound = left;
            right_bound < right - 1;
            ++right_bound
    ) {
        if (CompareWithPivot(right_bound, pivot, comparator))
        {
            ++left_bound;
            swap(*(left_bound - 1), *right_bound);
        }
    }
    swap(*left_bound, *(right - 1));
    return left_bound;
}

template <class RandomAccessIterator, class Compare, class RandomGenerator>
void QuickSort(
        const RandomAccessIterator& left,
        const RandomAccessIterator& right,
        const Compare& comparator,
        RandomGenerator& generator
) {
    if (left < right - 1)
    {
        RandomAccessIterator medium = PartitionSequence(left, right, comparator, generator);
        QuickSort(left, medium, comparator, generator);
        QuickSort(medium + 1, right, comparator, generator);
    }
}

template <class RandomAccessIterator,
        class Compare = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void QuickSort(
        const RandomAccessIterator& left,
        const RandomAccessIterator& right,
        const Compare& comparator = Compare()
) {
    std::mt19937 generator;
    QuickSort(left, right, comparator, generator);
}

vector<unsigned long long> CalculatePartialEfficiencySums(const vector<Player>& players)
{
    const size_t players_count = players.size();
    vector<unsigned long long> partial_sums(players_count);
    if (players_count == 0)
    {
        return partial_sums;
    }

    partial_sums[0] = players[0].efficiency;
    for (size_t i = 1; i < players_count; ++i)
    {
        partial_sums[i] =
                partial_sums[i - 1] + static_cast<unsigned long long> (players[i].efficiency);
    }
    return partial_sums;
}

// Search a team that satisfy the condition of unity, which has the highest common efficiency.
vector<Player> FindMostEffectiveTeam(const vector<Player>& players)
{
    const size_t players_count = players.size();
    if (players_count < 3)
    {
        return players;
    }

    vector<Player> sorted_players = players;
    QuickSort(sorted_players.begin(), sorted_players.end(), ComparePlayersLessEfficiency);

    vector<unsigned long long> partical_sum = CalculatePartialEfficiencySums(sorted_players);
    size_t left_optimal = 0;
    size_t right_optimal = 1;
    size_t right = 1;
    long long optimal_effectiveness = 0;

    for (size_t left = 0; left < players_count - 1; ++left)
    {
        while (
                (right < players_count)
                && (sorted_players[left].efficiency + sorted_players[left + 1].efficiency
                        >= sorted_players[right].efficiency)
        ) {
            ++right;
        }

        long long current_effectiveness =
                (left == 0)
                ? partical_sum[right - 1]
                : (partical_sum[right - 1] - partical_sum[left - 1]);
        if (optimal_effectiveness < current_effectiveness)
        {
            left_optimal = left;
            right_optimal = right;
            optimal_effectiveness = current_effectiveness;
        }
    }
    return {sorted_players.begin() + left_optimal, sorted_players.begin() + right_optimal};
}

vector<Player> ReadPlayers(std::istream& in = cin)
{
    size_t players_count;
    in >> players_count;
    vector<Player> data(players_count);
    for (size_t i = 0; i < players_count; ++i)
    {
        in >> data[i].efficiency;
        data[i].id = i + 1;
    }
    return data;
}

unsigned long long FindSummaryEfficiency(const vector<Player>& team)
{
    size_t team_size = team.size();
    unsigned long long summary_efficiency = 0;
    for (size_t i = 0; i < team_size; ++i)
    {
        summary_efficiency += team[i].efficiency;
    }

    return summary_efficiency;
}

// Write common efficiency and ids of all players
void WriteMostEffectiveTeam(const vector<Player>& team, std::ostream& out = cout)
{
    unsigned long long summary_efficiency = FindSummaryEfficiency(team);
    out << summary_efficiency << endl;

    vector<Player> sorted_team = team;
    QuickSort(sorted_team.begin(), sorted_team.end(), ComparePlayersLessId);

    size_t team_size = team.size();
    for (unsigned index_member = 0; index_member < team_size; ++index_member)
    {
        out << sorted_team[index_member].id << " ";
    }
    out << endl;
}

int main()
{
    vector<Player> players = ReadPlayers();

    vector<Player> most_effective_team = FindMostEffectiveTeam(players);

    WriteMostEffectiveTeam(most_effective_team);
    return 0;
}
