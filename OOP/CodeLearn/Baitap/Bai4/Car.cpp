#include <Transport.cpp>
#include <iostream>
#include <vector>

using namespace std;

class Car : public Transport {
private:
  int numberSeat;
  string engineType;

public:
  Car() {}
  Car(string manufacturer, string name, int year, int speed, int numberSeat,
      string engineType)
      : Transport(manufacturer, name, year, speed) {
    this->numberSeat = numberSeat;
    this->engineType = engineType;
  }
  int getNumberSeat() { return numberSeat; }
  string getengineType() { return engineType; }
  double getSpeedBasic() { return getSpeed() / getNumberSeat(); }
  void display() {
    Transport::display();
    cout << "Number Seat: " << numberSeat << endl;
    cout << "Engine Type: " << engineType << endl;
    cout << "Speed Basic: " << getSpeedBasic() << endl;
  }
  static vector<Car> getCarHaveMaxSpeedBasic(vector<Car> vt) {
    vector<Car> xe;
    double max = vt[0].getSpeedBasic();
    for (int i = 1; i < vt.size(); i++) {
      if (vt[i].getSpeedBasic() > max) {
        max = vt[i].getSpeedBasic();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getSpeedBasic() == max) {
        xe.push_back(vt[i]);
      }
    }
    return xe;
  }
  static vector<Car> getCarHaveMaxSeat(vector<Car> vt) {
    vector<Car> xe;
    int max = vt[0].getNumberSeat();
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getNumberSeat() > max) {
        max = vt[i].getNumberSeat();
      }
    }
    for (int i = 0; i < vt.size(); i++) {
      if (vt[i].getNumberSeat() == max) {
        xe.push_back(vt[i]);
      }
    }
    return xe;
  }
};