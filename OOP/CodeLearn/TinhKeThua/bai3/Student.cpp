#include "Person.cpp"
#include <iostream>

using namespace std;

class Student : public Person {
private:
  double gpa;

public:
  Student(string name, int age, string address, double gpa)
      : Person(name, age, address) {
    this->gpa = gpa;
  }
  void setGpa(double gpa) { this->gpa = gpa; }
  double getGpa() { return gpa; }
  void display() {
    Person::display();
    cout << "GPA: " << gpa << endl;
  }
};