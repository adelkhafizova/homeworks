#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Player {
public:
    Player(int number, int efficiency) {
        number_ = number;
        efficiency_ = efficiency;
    }

    int get_efficiency()  {
        return efficiency_;
    }

    int get_number()  {
        return number_;
    }
    /*operator = ( Player& player) {
      this->number_ = player.get_number();
      this->efficiency_ = player.get_efficiency();
    }*/

private:
    int number_;
    int efficiency_;
};

class IsPlayerMoreEfficient {
public:
    bool operator()( Player &rhp,  Player &lhp) {
        return rhp.get_efficiency() > lhp.get_efficiency();
    }
};

class HasPlayerLessTeamNumber {
public:
    bool operator()( Player &rhp,  Player &lhp) {
        return rhp.get_number() < lhp.get_number();
    }
};

template<typename RandomAccessIterator, typename Comparator>
RandomAccessIterator Partition( RandomAccessIterator &begin,
                                RandomAccessIterator &end,
                               RandomAccessIterator pivot, Comparator &comp) {
    //std::cout << "Pivot " << *pivot << std::endl;
    RandomAccessIterator left = begin;
    RandomAccessIterator right = (end - 1);
    typename RandomAccessIterator::value_type pivot_value = *pivot;
    while (left <= right) {
        while (comp(*left, pivot_value) && left < (end - 1)) {
            ++left;
            //    std::cout << "->";
        }
        //  std::cout << *left << std::endl;
        while (comp(pivot_value, *right) && right > begin) {
            --right;
            //    std::cout << "<-";
        }
        //  std::cout << *right << std::endl;
        if (left <= right) {
            std::swap(*left, *right);
            //    std::cout << "swap" << *left << ' ' << *right << std::endl;
            ++left;
            --right;
        }
        //std::cout << "Pivot " << *pivot << std::endl;
    }
    //std::cout << "Pivot " << *pivot << std::endl;
    /*while (begin != end) {
        std::cout << *begin << ' ';
        ++begin;
    } */
    //std::cout << std::endl;
    //std::cout << "proved pivot " << *pivot << std::endl;
    return left;
}

template<typename RandomAccessIterator, typename RandomGenerator>
RandomAccessIterator ChoosePivot(RandomAccessIterator begin,
                                 RandomAccessIterator end,
                                 RandomGenerator &generator) {
    //std::cout << "Length " <<  end - begin << std::endl;
    std::uniform_int_distribution<int> distribution(0, end - begin - 1);
    int random_pivot_index = distribution(generator);
    //std::cout << "Index " << random_pivot_index << std::endl;
    //std::cout << *(begin + random_pivot_index) << std::endl;
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
    std::cout << end - border << ' ' << border - begin << std::endl;
    QuickSort(border, end, comp, generator);
    QuickSort(begin, border, comp, generator);
    /*if (begin != end) {
      std::cout << *begin << std::endl;
      std::cout << *(end-1) << std::endl;
      RandomAccessIterator left = begin;
      RandomAccessIterator right = end - 1;
      RandomAccessIterator middle = left + ((right - left) / 2);
      RandomAccessIterator median = (*left > *middle) ? middle : left;
      median = (*median < *right) ? right : median;
      while (left < right) {
        while (*left <= *median && left != (end - 1)) {
          ++left;
        }
        while (*median <= *right && right != begin) {
          --right;
        }
        if (left < right) {
          std::iter_swap(left, right);
          ++left;
          --right;
        }
      }
      std::iter_swap(left, median);
      quicksort(begin, left);
      quicksort(left + 1, end);
    }*/
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

std::vector<int> CalculatePartialEfficiencySums
        (std::vector<Player> sorted_team) {
    std::vector<int> partial_efficiency_sums;
    partial_efficiency_sums.reserve(sorted_team.size());
    partial_efficiency_sums.push_back(sorted_team.at(0).get_efficiency());
    for (int i = 1; i < sorted_team.size(); ++i) {
        int current_sum = partial_efficiency_sums[i - 1] +
                          sorted_team[i].get_efficiency();
        partial_efficiency_sums.push_back(current_sum);
    }
    return partial_efficiency_sums;
}

std::pair<std::vector<Player>::iterator, std::vector<Player>::iterator>
        MaxEfficientContinuousSection(std::vector<Player> sorted_team) {
    if (sorted_team.size() < 3) {
        return std::make_pair(sorted_team.begin(), sorted_team.end());
    }
    std::vector<int> partial_sums = CalculatePartialEfficiencySums(sorted_team);
    int max_efficiency;
    int left_border = 0;
    int right_border = 2;
    using border = std::vector<Player>::iterator;
    std::pair<border, border> best_section_borders =
            std::make_pair(sorted_team.begin() + left_border,
                           sorted_team.begin() + right_border);
    while (right_border < sorted_team.size()) {
        while (sorted_team[left_border].get_efficiency() <=
               (sorted_team[right_border - 1].get_efficiency() +
                sorted_team[right_border].get_efficiency())) {
            ++right_border;
        }
        int current_efficiency = partial_sums[right_border - 1] -
                                 partial_sums[left_border - 1];
        if (current_efficiency > max_efficiency) {
            current_efficiency = max_efficiency;
            best_section_borders = std::make_pair(sorted_team.begin() + left_border,
                    sorted_team.begin() + right_border);
        }
        ++left_border;
    }
    return best_section_borders;
};

std::vector<Player> FindTheMostEfficientSolidTeam
        (std::vector<Player> football_team) {
    IsPlayerMoreEfficient efficiency_comparator;
    QuickSort(football_team.begin(), football_team.end(), efficiency_comparator);
    auto borders = MaxEfficientContinuousSection(football_team);
    return std::vector<Player>(borders.first, borders.second);
}

void WriteTheMostEfficientTeam( std::vector<Player> &best_team,
                               std::ostream &output_stream = std::cout) {
    HasPlayerLessTeamNumber index_comparator;
    QuickSort(best_team.begin(), best_team.end(), index_comparator);
    for (int i = 0; i < best_team.size(); ++i) {
        output_stream << best_team[i].get_efficiency() << ' ';
    }
    output_stream << std::endl;
}

int main() {
    std::vector<Player> football_team = ReadFootballTeam();
    std::vector<Player> best_solid_team = FindTheMostEfficientSolidTeam(football_team);
    WriteTheMostEfficientTeam(best_solid_team);
    /*std::vector<int> data;
    int size = 0;
    std::cin >> size;
    for (int i = 0; i < size; i++) {
        int temp;
        std::cin >> temp;
        data.push_back(temp);
    }
    std::vector<int> data2(data);
    QuickSort(data.begin(), data.end(), [](int a, int b) {
        return (a < b);
    });
    std::sort(data2.begin(), data2.end());
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << data2[i] << ' ';
    }
    std::cout << std::endl;*/
}
