#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Student {
private:
  string name;
  double math;
  double physic;
  double chemistry;

public:
  Student() {}
  Student(string name, double math, double physic, double chemistry) {
    this->name = name;
    this->math = math;
    this->physic = physic;
    this->chemistry = chemistry;
  }
  double getMath() { return math; }
  double getPhysic() { return physic; }
  double getChemistry() { return chemistry; }
  void display() {
    cout << "Name: " << name << endl;
    cout << "Point math: " << math << endl;
    cout << "Point physic: " << physic << endl;
    cout << "Point chemistry" << chemistry << endl;
    cout << "Average: " << avgPoint() << endl;
  }
  double avgPoint() { return (math + physic + chemistry) / 3; }
  static vector<Student> getStudentMaxAvg(vector<Student> vt) {
    double max = vt[0].avgPoint();
  }
};