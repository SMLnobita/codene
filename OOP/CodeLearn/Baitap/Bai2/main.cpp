#include "Student.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<Student> students;
  students.push_back(Student("An", 8.0, 7.0, 6.0));
  students.push_back(Student("Binh", 5.0, 9.0, 7.0));
  students.push_back(Student("Chi", 9.0, 8.0, 9.0));
  students.push_back(Student("Dung", 6.0, 5.0, 4.0));
  students.push_back(Student("Em", 9.0, 6.0, 9.0));

  cout << "=== DANH SACH ===" << endl;
  for (int i = 0; i < students.size(); i++) {
    students[i].display();
    cout << "---" << endl;
  }

  cout << "\n=== MAX TRUNG BINH ===" << endl;
  vector<Student> maxAvg = Student::getStudentMaxAvg(students);
  for (int i = 0; i < maxAvg.size(); i++) {
    maxAvg[i].display();
    cout << "---" << endl;
  }

  cout << "\n=== MAX TOAN ===" << endl;
  vector<Student> maxMath = Student::getStudentMaxMath(students);
  for (int i = 0; i < maxMath.size(); i++) {
    maxMath[i].display();
    cout << "---" << endl;
  }

  cout << "\n=== MAX LY ===" << endl;
  vector<Student> maxPhysic = Student::getStudentMaxPhysic(students);
  for (int i = 0; i < maxPhysic.size(); i++) {
    maxPhysic[i].display();
    cout << "---" << endl;
  }

  cout << "\n=== MAX HOA ===" << endl;
  vector<Student> maxChem = Student::getStudentMaxChemistry(students);
  for (int i = 0; i < maxChem.size(); i++) {
    maxChem[i].display();
    cout << "---" << endl;
  }

  return 0;
}