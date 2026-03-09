#include <iostream>

using namespace std;

class Person {
private:
  int id;
  string name;
  int age;
  string address;

public:
  int getId() { return id; }
  void setId(int id) { this->id = id; }
  string getName() { return name; }
  void setName(string name) { this->name = name; }
  int getAge() { return age; }
  void setAge(int age) { this->age = age; }
  string getAddress() { return address; }
  void setAddress(string address) { this->address = address; }
};

int main() {
  Person p;
  p.setId(1001);
  p.setName("Quynh");
  p.setAge(24);
  p.setAddress("Ha Noi");

  cout << "Id: " << p.getId() << endl;
  cout << "Name: " << p.getName() << endl;
  cout << "Age: " << p.getAge() << endl;
  cout << "Address: " << p.getAddress() << endl;
  return 0;
}
