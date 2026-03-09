#include <iostream>
using namespace std;
class Math {
public:
  static int abs(int x) {
    if (x < 0) {
      return -x;
    }
    return x;
  }
  static int add(int x, int y) { return x + y; }
  static int subtract(int x, int y) { return x - y; }
  static int min(int x, int y) {
    if (x > y) {
      return y;
    } else {
      return x;
    }
  }
  static int max(int x, int y) {
    if (x > y) {
      return x;
    } else {
      return x;
    }
  }
  static int pow(int x, int y) {
    int power = 1;
    for (int i = 0; i < y; i++) {
      power *= x;
    }
    return power;
  }
};