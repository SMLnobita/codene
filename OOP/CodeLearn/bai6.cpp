#include <iostream>
using namespace std;
class ArrayCalculator {
public:
  static int sumOfArray(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += arr[i];
    }
    return sum;
  }
  static double sumOfArray(double *arr, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      sum += arr[i];
    }
    return sum;
  }
};

int main() {
  int arr[] = {3, 4, 2};
  double arr2[] = {1.3, 4.2, 6.7};
  int len = sizeof(arr) / sizeof(int);
  int len2 = sizeof(arr2) / sizeof(double);
  cout << ArrayCalculator::sumOfArray(arr, len) << endl;
  cout << ArrayCalculator::sumOfArray(arr2, len) << endl;
  return 0;
}