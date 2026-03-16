#include "Person.cpp"
#include <iostream>

using namespace std;

class Teacher : public Person {
private:
  int salary;

public:
  Teacher(string name, int age, string address, int salary)
      : Person(name, age, address) {
    this->salary = salary;
  }
  void setSalary(int salary) { this->salary = salary; }
  int getSalary() { return salary; }
  void display() {
    Person::display();
    cout << "Salary: " << salary << endl;
  }
};