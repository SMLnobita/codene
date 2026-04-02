#include "Student.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
  // Tao mon hoc
  vector<Subject> s1;
  s1.push_back(Subject("Toan Cao Cap", 8.5, 3, 500000));
  s1.push_back(Subject("Vat Ly", 7.0, 2, 400000));
  s1.push_back(Subject("Lap Trinh C", 9.0, 4, 600000));

  vector<Subject> s2;
  s2.push_back(Subject("Giai Tich", 6.5, 3, 500000));
  s2.push_back(Subject("Hoa Dai Cuong", 5.0, 2, 450000));

  vector<Subject> s3;
  s3.push_back(Subject("Co So Du Lieu", 8.0, 3, 550000));
  s3.push_back(Subject("Mang May Tinh", 7.5, 3, 500000));
  s3.push_back(Subject("OOP", 9.5, 4, 600000));

  // Tao sinh vien
  vector<Student> students;
  students.push_back(Student("SV001", "Nguyen Van An", s1));
  students.push_back(Student("SV002", "Tran Thi Binh", s2));
  students.push_back(Student("SV003", "Le Van Chi", s3));

  // Hien thi
  for (int i = 0; i < students.size(); i++) {
    cout << "=============================" << endl;
    students[i].display();
  }

  return 0;
}