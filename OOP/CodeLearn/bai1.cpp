#include <iostream>
using namespace std;

class Student {
public:
  string name;
  int age;
  void getinformation(void) { cin >> name >> age; }
  void display(void) {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
  }
};

int main(void) {
  Student s;
  s.getinformation();
  s.display();
  return 0;
}