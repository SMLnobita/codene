#include <iostream>
#include "Point.cpp"
#include "Line.cpp"

using namespace std;

int main() {
	Point begin(1, 1);
	Point end(2, 2);
	Line line1(begin, end);
	cout << line1.getLength() << endl;

	Line line2(2, 3, 5, 4);
	cout << line2.getLength() << endl;
	return 0;
}