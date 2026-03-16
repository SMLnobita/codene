#pragma once
#include <iostream>
using namespace std;

class Person {
private:
  string name;
  int age;
  string address;

public:
  Person(string name, int age, string address) {
    this->name = name;
    this->age = age;
    this->address = address;
  }
  void setName(string name) { this->name = name; }
  string getName() { return name; }
  void setAge(int age) { this->age = age; }
  int getAge() { return age; }
  void setAddress(string address) { this->address = address; }
  string getAddress() { return address; }
  void display() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl;
  }
};
