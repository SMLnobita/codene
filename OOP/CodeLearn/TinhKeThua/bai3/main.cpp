#include "Person.cpp"
#include "Student.cpp"
#include "Teacher.cpp"
#include <iostream>

using namespace std;

int main() {
  Student s("Hoa", 21, "Long An", 9.5);
  s.display();
  Teacher t("Trung", 22, "Sai Gon", 1700);
  t.display();
  return 0;
}