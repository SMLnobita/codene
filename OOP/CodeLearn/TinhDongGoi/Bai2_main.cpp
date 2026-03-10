#include "Rectangle.cpp"
#include <iostream>


using namespace std;

int main() {
  Rectangle r(4, 5);
  cout << "Area: " << r.getArea() << endl;
  cout << "Perimeter: " << r.getPerimeter() << endl;
  r.setLength(2);
  r.setWidth(3);
  cout << "Area: " << r.getArea() << endl;
  cout << "Perimeter: " << r.getPerimeter() << endl;
  return 0;
}