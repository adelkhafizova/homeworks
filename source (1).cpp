#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <math.h>

using std::vector;

const double COMPARISON_THRESHOLD = 1e-4;

bool less(double first, double second) {
  return first < second - COMPARISON_THRESHOLD;
}

bool lessOrEqual(double first, double second) {
  return first < second + COMPARISON_THRESHOLD;
}

bool equal(double first, double second) {
  return fabs(first - second) < COMPARISON_THRESHOLD;
}

template <typename Iterator, typename Comparator>
void Merge(Iterator FirstBegin,
            Iterator FirstEnd,
            Iterator SecondBegin,
            Iterator SecondEnd,
            Iterator ResultBegin,
            Comparator Compare = Comparator()) {
    auto FirstPointer = FirstBegin;
    auto SecondPointer = SecondBegin;
    auto WritePointer = ResultBegin;
    while ( (FirstPointer < FirstEnd) && (SecondPointer < SecondEnd) ) {
            if ( Compare(*FirstPointer, *SecondPointer) ) {
                *WritePointer = *FirstPointer;
                ++FirstPointer;
                ++WritePointer;
            } else {
                *WritePointer = *SecondPointer;
                ++SecondPointer;
                ++WritePointer;
            }
    }
    while (FirstPointer < FirstEnd) {
        *WritePointer = *FirstPointer;
        ++FirstPointer;
        ++WritePointer;
    }
    while (SecondPointer < SecondEnd) {
        *WritePointer = *SecondPointer;
        ++SecondPointer;
        ++WritePointer;
    }
}

template <typename Iterator, typename Comparator>
void MergeSort(Iterator ArrayBegin,
               Iterator ArrayEnd,
               Comparator Compare = Comparator()) {
    int CurrentSorted = 1;
    while (CurrentSorted < ArrayEnd - ArrayBegin) {
        auto MergeIndex = ArrayBegin;
        while (MergeIndex + CurrentSorted < ArrayEnd) {
            vector<typename Iterator::value_type> Buffer(MergeIndex, MergeIndex+CurrentSorted);
            Merge(Buffer.begin(),
                  Buffer.end(),
                  MergeIndex + CurrentSorted,
                  std::min(MergeIndex + 2 * CurrentSorted, ArrayEnd) ,
                  MergeIndex,
                  Compare);
            MergeIndex += 2 * CurrentSorted;
        }
        CurrentSorted *= 2;
    }
}

struct Point {
    double length;
    double height;
    Point(double Length, double Height): length(Length), height(Height) {}
};

struct Bracket {
    double position;
    bool type;
    Bracket(double Position, bool Type): position(Position), type(Type) {}
};

void CheckPoint(Point SomePoint,
                std::vector<Bracket>& Brackets,
                double Radius) {
    if (Radius < fabs(SomePoint.height)) {
        return;
    } else {
        double DistanceFromProjection = sqrt(Radius*Radius - SomePoint.height*SomePoint.height);
        Bracket Begin(SomePoint.length - DistanceFromProjection, true);
        Brackets.push_back(Begin);
        Bracket End(SomePoint.length + DistanceFromProjection, false);
        Brackets.push_back(End);
    }
}

void CreateBrackets(std::vector<Bracket>&Brackets,
                    const std::vector<Point> AllPoints,
                    double Radius) {
    for (int i = 0; i < AllPoints.size(); ++i) {
        CheckPoint(AllPoints[i], Brackets, Radius);
    }
}

bool CompareBrackets(const Bracket& lhs,
                     const Bracket& rhs) {
    return lhs.position < rhs.position;
}

void ReadPoints(std::vector<Point>& AllPoints,
                int & NumberOfPoints,
                int & NumberToBeInside) {
    std::ifstream InputFile;
    InputFile.open("input.txt");
    InputFile >> NumberOfPoints;
    InputFile >> NumberToBeInside;
    for (int i = 0; i < NumberOfPoints; ++i) {
        double length, height;
        InputFile >> length;
        InputFile >> height;
        Point NewPoint(length, height);
        AllPoints.push_back(NewPoint);
    }
}

bool ContainsKPoints(std::vector<Bracket>& Brackets,
                     const int& NumberToBeInside) {
    MergeSort(Brackets.begin(), Brackets.end(), CompareBrackets);
    int Index = 0;
    int Overall = 0;
    while (Index < Brackets.size()) {
        if (Overall >= NumberToBeInside) {
            return true;
        } else {
            if (Brackets[Index].type) {
                ++Overall;
                ++Index;
            } else {
                --Overall;
                ++Index;
            }
        }
    }
    return false;
}

double FindMinRadius(std::vector<Point>& AllPoints,
                      int & NumberToBeInside) {
    double Radius = 2000;
    double Difference = Radius / 2;
    while (Difference > 0.0001) {
        std::vector<Bracket> Brackets;
        CreateBrackets(Brackets, AllPoints, Radius);
        if (ContainsKPoints(Brackets, NumberToBeInside)) {
            Radius -= Difference;
        } else {
            Radius += Difference;
        }
        Difference /= 2;
    }
    return Radius;
}

double AnotherMinRadius(std::vector<Point>& AllPoints,
                        int& NumberToBeInside) {
    if (NumberToBeInside == 1) {
        double Min = fabs(AllPoints[0].height);
        for (int i = 0; i < AllPoints.size(); ++i) {
            if (fabs(AllPoints[i].height) < Min) {
                Min = AllPoints[i].height;
            }
        }
        return Min;
    } else {
        return 0;
    }
}



int main() {
    std::vector<Point> AllPoints;
    int NumberOfPoints, NumberToBeInside;
    ReadPoints(AllPoints, NumberOfPoints, NumberToBeInside);
    double Radius = FindMinRadius(AllPoints, NumberToBeInside);
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << Radius;
    return 0;
}




