// Tuan 5 - Bai 11: Lop animal co phuong thuc ao say
// person -> noi, cat -> mew, cow -> moo, dog -> go
// Dung con tro lop cha animal tro toi cac doi tuong lop con
#include <iostream>

using namespace std;

class animal {
public:
  virtual void say() { cout << "Animal say something\n"; }
  virtual ~animal() {}
};

class person : public animal {
public:
  void say() override { cout << "Person say: noi\n"; }
};

class cat : public animal {
public:
  void say() override { cout << "Cat say: mew\n"; }
};

class cow : public animal {
public:
  void say() override { cout << "Cow say: moo\n"; }
};

class dog : public animal {
public:
  void say() override { cout << "Dog say: go\n"; }
};

int main() {
  person p;
  cat c;
  cow cw;
  dog d;

  animal *ptr;

  ptr = &p;
  ptr->say();
  ptr = &c;
  ptr->say();
  ptr = &cw;
  ptr->say();
  ptr = &d;
  ptr->say();

  return 0;
}
