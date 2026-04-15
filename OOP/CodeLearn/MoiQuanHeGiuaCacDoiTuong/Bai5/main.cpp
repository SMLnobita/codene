#include "Point.h"
#include "PolyLine.h"
#include <iostream>

using namespace std;

int main() {
  PolyLine polyLine;
  polyLine.appendPoint(1, 1);
  polyLine.appendPoint(2, 3);
  polyLine.appendPoint(3, 0);
  polyLine.appendPoint(4, 2);
  cout << polyLine.getLength();
  return 0;
}