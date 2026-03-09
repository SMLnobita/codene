#include <iostream>
using namespace std;

class ArrayCalculator {
public:
  static int maxOfArray(int *arr, int n) {
    int maxValue = arr[1];
    for (int i = 0; i < n; i++) {
      if (arr[i] > maxValue) {
        maxValue = arr[i];
      }
    }
    return maxValue;
  }
  static double maxOfArray(double *arr, int n) {
    double maxValue = arr[1];
    for (int i = 0; i < n; i++) {
      if (arr[i] > maxValue) {
        maxValue = arr[i];
      }
    }
    return maxValue;
  }
  static int minOfArray(int *arr, int n) {
    int minValue = arr[1];
    for (int i = 0; i < n; i++) {
      if (arr[i] < minValue) {
        minValue = arr[i];
      }
    }
    return minValue;
  }
  static double minOfArray(double *arr, int n) {
    double minValue = arr[1];
    for (int i = 0; i < n; i++) {
      if (arr[i] < minValue) {
        minValue = arr[i];
      }
    }
    return minValue;
  }
};