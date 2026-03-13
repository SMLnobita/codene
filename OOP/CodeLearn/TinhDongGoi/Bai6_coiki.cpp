#include <iostream>
#include <cmath>

using namespace std;

class Point {
private:
  double x;
  double y;

public:
  Point() {}
  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }
  void setX(double x) { this->x = x; }
  double getX() { return x; }
  void setY(double y) { this->y = y; }
  double getY() { return y; }
  void setXY(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double distance(double x, double y) {
    double dodai =
        sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y));
    return dodai;
  }
  double distance(Point another) {
    return distance(another.getX(), another.getY());
  }
};


int main() {
  Point p1(1.5, 6.7);
  Point p2(2.8, 3.2);
  cout << p1.distance(p2) << endl;
  cout << p1.distance(2.34, 7.8) << endl;
  return 0;
}