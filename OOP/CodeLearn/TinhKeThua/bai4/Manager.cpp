#include "Employee.cpp"
#include <iostream>

using namespace std;

class Manager : public Employee {
private:
  int bonus;

public:
  Manager(string name, int salary, int bounus) : Employee(name, salary) {
    this->bonus = bounus;
  }

  int getSalary() { return Employee::getSalary() + bonus; }

  void setBonus(int bonus) { this->bonus = bonus; }
  int getBonus() { return bonus; }
  void display() {
    cout << "Name: " << getName() << endl;
    cout << "Salary: " << getSalary() << endl;
  }
};