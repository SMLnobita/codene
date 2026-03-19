#include <iostream>
#include "Shape.cpp"
#include "Rectangle.cpp"
#include "Circle.cpp"
using namespace std;

int main() {
	Shape* behoa[3];
	behoa[0] = new Rectangle(2, 3);
	behoa[1] = new Circle(4);
	behoa[2] = new Rectangle(7.4, 4.3);
	for (int i = 0; i < 3; i++)
	{	
		cout << "-------------------------" << endl;
		cout << behoa[i]->getArea() << endl;
		cout << behoa[i]->getPerimeter() << endl;
	}
}