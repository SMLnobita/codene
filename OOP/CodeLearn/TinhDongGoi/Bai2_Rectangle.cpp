#include <iostream>
using namespace std;

class Rectangle {
private:
  double length;
  double width;

public:
  Rectangle() {}
  Rectangle(double length, double width) {
    this->length = length;
    this->width = width;
  }
  void setLength(double length) { this->length = length; }
  double getLength() { return length; }
  void setWidth(double width) { this->width = width; }
  double getWidth() { return width; }
  double getArea() { return length * width; }
  double getPerimeter() { return (length + width) * 2; }
};