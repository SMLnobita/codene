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
    cout << "Point chemistry: " << chemistry << endl;
    cout << "Average: " << avgPoint() << endl;
  }
  double avgPoint() { return (math + physic + chemistry) / 3; }
  static vector<Student> getStudentMaxAvg(vector<Student> vt) {
    double max = vt[0].avgPoint();
    vector<Student> v;
    for (int i = 1; i < vt.size(); i++) {
      if (vt[i].avgPoint() > max) {
        max = vt[i].avgPoint();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].avgPoint() == max) {
        v.push_back(vt[i]);
      }
    }
    return v;
  }
  static vector<Student> getStudentMaxMath(vector<Student> vt) {
    double max = vt[0].getMath();
    vector<Student> v;
    for (int i = 1; i < vt.size(); i++) {
      if (vt[i].getMath() > max) {
        max = vt[i].getMath();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getMath() == max) {
        v.push_back(vt[i]);
      }
    }
    return v;
  }
  static vector<Student> getStudentMaxPhysic(vector<Student> vt) {
    double max = vt[0].getPhysic();
    vector<Student> v;
    for (int i = 1; i < vt.size(); i++) {
      if (vt[i].getPhysic() > max) {
        max = vt[i].getPhysic();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getPhysic() == max) {
        v.push_back(vt[i]);
      }
    }
    return v;
  }
  static vector<Student> getStudentMaxChemistry(vector<Student> vt) {
    double max = vt[0].getChemistry();
    vector<Student> v;
    for (int i = 1; i < vt.size(); i++) {
      if (vt[i].getChemistry() > max) {
        max = vt[i].getChemistry();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getChemistry() == max) {
        v.push_back(vt[i]);
      }
    }
    return v;
  }
};