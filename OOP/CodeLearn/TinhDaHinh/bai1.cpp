#include <iostream>
using namespace std;

class Animal {
public:
  virtual void sound() { cout << "some sound" << endl; }
};

class Dog : public Animal {
public:
  void sound() { cout << "bow wow" << endl; }
};

class Cat : public Animal {
public:
  void sound() { cout << "meow meow" << endl; }
};

class Duck : public Animal {
public:
  void sound() { cout << "quack quack" << endl; }
};

int main() {
  Animal *animal[4];
  animal[0] = new Animal();
  animal[1] = new Dog();
  animal[2] = new Cat();
  animal[3] = new Duck();

  for (int i = 0; i < 4; i++) {
    animal[i]->sound();
  }
}