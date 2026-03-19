#include "Person.cpp"
#include <iostream>

class Employee : public Person {
private:
  int salary;

public:
  Employee(string name, string address, int salary) : Person(name, address) {
    this->salary = salary;
  }
  void display() {
    cout << "Employee name: " << getName() << endl;
    cout << "Employee address: " << getAddress() << endl;
    cout << "Employee salary: " << salary << endl;
  }
};