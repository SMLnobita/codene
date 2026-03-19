#include <math.h>
#include "Point.cpp"

class Line {
private:
	Point begin;
	Point end;

public:
	Line(Point begin, Point end) {
		this->begin = begin;
		this->end = end;
	}

	Line(int x1, int y1, int x2, int y2) {
		this->begin = Point(x1, y1);
		this->end = Point(x2, y2);
	}

	Point getBegin() {
		return begin;
	}

	void setBegin(Point begin) {
		this->begin = begin;
	}

	Point getEnd() {
		return end;
	}

	void setEnd(Point end) {
		this->end = end;
	}
	double getLength() {
		return sqrt(pow(end.getX() - begin.getX(), 2) + pow(end.getY() - begin.getY(), 2));
	}
};