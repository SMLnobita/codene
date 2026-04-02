#pragma once
#include <iostream>
using namespace std;

class Subject {
private:
  string nameSub;
  double point;
  int numberCredit;
  long money;

public:
  Subject() {}
  Subject(string nameSub, double point, int numberCredit, long money) {
    this->nameSub = nameSub;
    this->point = point;
    this->numberCredit = numberCredit;
    this->money = money;
  }
  string getNameSub() { return nameSub; }
  double getPoint() { return point; }
  int getNumberCredit() { return numberCredit; }
  long getMoney() { return money; }
  void display() {
    cout << "Name Subject: " << nameSub << endl;
    cout << "Point: " << point << endl;
    cout << "Number Credit: " << numberCredit << endl;
    cout << "Money Of One Credit: " << money << endl;
  }
};