#pragma once
#include <iostream>
using namespace std;

class Employee {
private:
  string name;
  int salary;

public:
  Employee(string name, int salary) {
    this->name = name;
    this->salary = salary;
  }
  void setName(string name) { this->name = name; }
  string getName() { return name; }
  void setSalary(int salary) { this->salary = salary; }
  int getSalary() { return salary; }
  void display() {
    cout << "Name: " << name << endl;
    cout << "Salary: " << salary << endl;
  }
};