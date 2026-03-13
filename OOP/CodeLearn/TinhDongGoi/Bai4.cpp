#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Date {
private:
  int day;
  int month;
  int year;

public:
  Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
  }
  void setDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
  }
  void setDay(int day) { this->day = day; }
  void setMonth(int month) { this->month = month; }
  void setYear(int year) { this->year = year; }
  int getDay() { return day; }
  int getMonth() { return month; }
  int getYear() { return year; }
  void display() {
    // cout << setw(2) << setfill('0') << day << '/' << setw(2) << setfill('0')
    //      << month << '/' << year << endl;
    string day = to_string(this->day);
    string month = to_string(this->month);
    string year = to_string(this->year);
    if (day.size() == 1) {
      day = '0' + day;
    }
    if (month.size() == 1) {
      month = '0' + month;
    }
    cout << day << '/' << month << '/' << year << endl;
  }
};