#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>

class Player {
public:
  Player(int number, int efficiency) {
    number_ = number;
    efficiency_ = efficiency;
  }

  long long get_efficiency() const {
    return efficiency_;
  }

  int get_number() const {
    return number_;
  }

private:
  int number_;
  long long efficiency_;
};

class IsPlayerMoreEfficient {
public:
  bool operator()(const Player &rhp, const Player &lhp) {
    return rhp.get_efficiency() > lhp.get_efficiency();
  }
};

class HasPlayerLessTeamNumber {
public:
  bool operator()(const Player &rhp, const Player &lhp) {
    return rhp.get_number() < lhp.get_number();
  }
};

template<class RandomAccessIterator, class Comparator>
RandomAccessIterator Partition(const RandomAccessIterator &begin,
                 const RandomAccessIterator &end,
                 RandomAccessIterator pivot, Comparator &comp) {
  RandomAccessIterator left = begin;
  RandomAccessIterator right = (end - 1);
  typename RandomAccessIterator::value_type pivot_value = *pivot;
  while (left <= right) {
    while (comp(*left, pivot_value) && left < (end - 1)) {
      ++left;
    }
    while (comp(pivot_value, *right) && right > begin) {
      --right;
    }
    if (left <= right) {
      std::swap(*left, *right);
      ++left;
      --right;
    }
  }
  return left;
}

template<typename RandomAccessIterator, typename RandomGenerator>
RandomAccessIterator ChoosePivot(RandomAccessIterator begin,
                 RandomAccessIterator end,
                 RandomGenerator &generator) {
  std::uniform_int_distribution<int> distribution(0, end - begin - 1);
  int random_pivot_index = distribution(generator);
  return (begin + random_pivot_index);
}

template<typename RandomAccessIterator, typename Comparator,
    typename RandomGenerator>
void QuickSort(RandomAccessIterator begin, RandomAccessIterator end,
         Comparator comp, RandomGenerator &generator) {
  if (begin >= (end - 1))
    return;
  RandomAccessIterator pivot = ChoosePivot(begin, end, generator);
  RandomAccessIterator border = Partition(begin, end, pivot, comp);
  QuickSort(border, end, comp, generator);
  QuickSort(begin, border, comp, generator);
}

template<typename RandomAccessIterator, typename Comparator>
void QuickSort(RandomAccessIterator begin, RandomAccessIterator end,
         Comparator comp) {
  std::default_random_engine generator;
  QuickSort(begin, end, comp, generator);
}

std::vector<Player> ReadFootballTeam(std::istream &input_stream = std::cin) {
  int team_size;
  input_stream >> team_size;
  std::vector<Player> football_team;
  football_team.reserve(team_size);
  for (int number_in_team = 0; number_in_team < team_size; ++number_in_team) {
    int current_efficiency;
    input_stream >> current_efficiency;
    Player player(number_in_team, current_efficiency);
    football_team.push_back(player);
  }
  return football_team;
}

std::vector<long long> CalculatePartialEfficiencySums
    (std::vector<Player> sorted_team) {
  std::vector<long long> partial_efficiency_sums;
  partial_efficiency_sums.reserve(sorted_team.size());
  partial_efficiency_sums.push_back(sorted_team.at(0).get_efficiency());
  for (int i = 1; i < sorted_team.size(); ++i) {
    long long current_sum = partial_efficiency_sums[i - 1] + 
                      sorted_team[i].get_efficiency();
    partial_efficiency_sums.push_back(current_sum);
  }
  return partial_efficiency_sums;
}

std::pair<int, int> MaxEfficientContinuousSection
    (std::vector<Player> sorted_team, long long &max_efficiency) {
  if (sorted_team.size() < 3) {
    for (int i = 0; i < sorted_team.size(); ++i) {
      max_efficiency += sorted_team[i].get_efficiency();
    }
    return std::make_pair(0, sorted_team.size());
  }
  std::vector<long long> partial_sums = CalculatePartialEfficiencySums(sorted_team);
  int left_border = 0;
  int right_border = 2;
  std::pair<int, int> best_section_borders = std::make_pair(left_border, 
                                                            right_border + 1);
  
  while (right_border < sorted_team.size()) {
    while ((sorted_team[left_border].get_efficiency() <=
            (sorted_team[right_border - 1].get_efficiency() + 
             sorted_team[right_border].get_efficiency())) 
           && right_border < sorted_team.size()) {
      ++right_border;
    }
    long long current_efficiency = partial_sums[right_border - 1] -
                             (left_border ? partial_sums[left_border - 1] : 0);
    if (current_efficiency > max_efficiency) {
      max_efficiency =  current_efficiency;
      best_section_borders = std::make_pair(left_border, right_border);
    }
    ++left_border;
  }
  return best_section_borders;
};

std::vector<Player> FindTheMostEfficientSolidTeam 
    (std::vector<Player> football_team, long long &max_efficiency) {
  IsPlayerMoreEfficient efficiency_comparator;
  QuickSort(football_team.begin(), football_team.end(), efficiency_comparator);
  auto borders = MaxEfficientContinuousSection(football_team, max_efficiency);
  std::vector<Player>::iterator first = football_team.begin();
  return std::vector<Player>(first + borders.first, first + borders.second);
}

void WriteTheMostEfficientTeam(std::vector<Player> &best_team, 
                               long long max_efficiency,
                               std::ostream &output_stream = std::cout) {
  HasPlayerLessTeamNumber index_comparator;
  QuickSort(best_team.begin(), best_team.end(), index_comparator);
  output_stream << max_efficiency << std::endl;
  for (int i = 0; i < best_team.size(); ++i) {
    output_stream << best_team[i].get_number() + 1 << ' ';
  }
  output_stream << std::endl;
}

int main() {
  std::vector<Player> football_team = ReadFootballTeam();
  long long max_efficiency = 0;
  std::vector<Player> best_solid_team = 
    FindTheMostEfficientSolidTeam(football_team, max_efficiency);
  WriteTheMostEfficientTeam(best_solid_team, max_efficiency);
}
