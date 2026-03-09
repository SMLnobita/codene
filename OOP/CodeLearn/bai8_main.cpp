#include "Student.cpp"
#include <iostream>
using namespace std;

int main() {
  Student s1;
  s1.display();
  Student s2("Quang");
  s2.display();
  Student s3('m');
  s3.display();
  Student s4("Thu", 'f');
  s4.display();
  return 0;
}