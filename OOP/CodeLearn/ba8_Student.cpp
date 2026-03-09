#include <iostream>
using namespace std;

class Student {
private:
  string name;
  char gender;

public:
  Student() {
    name = "Unknown";
    gender = 'u';
  }
  Student(string name) {
    this->name = name;
    gender = 'u';
  }
  Student(char gender) {
    this->gender = gender;
    name = "Unknown";
  }
  Student(string name, char gender) {
    this->name = name;
    this->gender = gender;
  }
  void display() {
    cout << "Name: " << name << endl;
    if (gender == 'u') {
      cout << "Gender: Unknown" << endl;
    } else if (gender == 'm') {
      cout << "Gender: Male" << endl;
    } else if (gender == 'f') {
      cout << "Gender: Female" << endl;
    }
  }
};