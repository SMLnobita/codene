#include "ArrayCalculator.cpp"
#include <iostream>
using namespace std;

int main() {
  int arr1[] = {3, 4, 2};
  double arr2[] = {1.3, 4.2, 6.7};
  int len1 = sizeof(arr1) / sizeof(int);
  int len2 = sizeof(arr2) / sizeof(double);
  cout << "Tim max" << endl;
  cout << ArrayCalculator::maxOfArray(arr1, len1) << endl;
  cout << ArrayCalculator::maxOfArray(arr2, len2) << endl;
  cout << "Tim min" << endl;
  cout << ArrayCalculator::minOfArray(arr1, len1) << endl;
  cout << ArrayCalculator::minOfArray(arr2, len2) << endl;
  return 0;
}
