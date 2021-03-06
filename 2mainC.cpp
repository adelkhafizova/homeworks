#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class Point {
public:
  Point(int x_coord, int y_coord) {
    x_coord_ = x_coord;
    y_coord_ = y_coord; 
    radius_ = sqrt(x_coord_*x_coord_ + y_coord_*y_coord_);
  }
  double get_x() {
    return x_coord_;
  }
  double get_y() {
    return y_coord_;
  }
  double get_radius() {
    return radius_;
  }
  bool operator < (const Point &point) const {
    return radius_ < point.radius_;
  }

 private:
  int x_coord_;
  int y_coord_;
  double radius_;
};

class Mark {
public:
  Mark(double position, bool covered) {
    position_ = position;
    covered_ = covered;
  }
  bool operator < (const Mark &mark) const {
    if (std::abs(position_ - mark.position_) < pow(10, -6)) {
      return false;
    }
    return position_ < mark.position_;
  }
  double position_;
  bool covered_;
};

void ProcessPoint(Point point, std::vector<Mark> &marks, double radius) {
  if (radius < std::abs(point.get_y())) {
      return;
  } else {
    double distance = sqrt(pow(radius, 2) - pow(point.get_y(), 2));
    Mark first(point.get_x() - distance, true);
    Mark last(point.get_x() + distance, false);
    marks.push_back(first);
    marks.push_back(last);
  }
}

std::vector<Point> ReadPoints(int &points_to_cover, std::istream &input_stream = std::cin) {
  int point_number = 0;
  input_stream >> point_number >> points_to_cover;
  std::vector<Point> points;
  points.reserve(point_number);
  for (int i = 0; i < point_number; ++i) {
    int x_coord, y_coord;
    input_stream >> x_coord >> y_coord;
    Point cur_point(x_coord, y_coord);
    points.push_back(cur_point);
  }
  return points;
}

bool covers(std::vector<Point> &points, double radius, int &points_to_cover) {
  std::vector<Mark> marks;
  for (int i = 0; i < points.size(); ++i) {
    ProcessPoint(points[i], marks, radius);
  }
  std::sort(marks.begin(), marks.end());
  int covered_num = 0;
  for (int index = 0; index < marks.size(); ++index) {
    if (marks[index].covered_) {
      ++covered_num;
    } else {
      --covered_num;
    }
    if (covered_num >= points_to_cover) {
      return true;
    }
  }
  return covered_num >= points_to_cover;
}

double FindCoveringRadius(std::vector<Point> &points, int &points_to_cover) {
  double upper_bound = 1500;
  double lower_bound = 0;
  double eps = pow(10, -3);
  while (upper_bound - lower_bound > eps) {
    if (covers(points, (upper_bound + lower_bound)/2, points_to_cover)) {
      upper_bound = (upper_bound + lower_bound)/2;
    } else {
      lower_bound = (upper_bound + lower_bound)/2;
    }
  }
  return upper_bound;
}

int main() {
  int points_to_cover = 0;
  std::vector<Point> points = ReadPoints(points_to_cover);
  std::cout << FindCoveringRadius(points, points_to_cover) << std::endl;
}
