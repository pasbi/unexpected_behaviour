#include <iostream>

// This is an example about what static methods a virtual method sees.
// It might not be surprising or counter-intuitive, but I find the example helpful from time to
// time.

class Base
{
public:
  virtual void foo1() { std::cout << "1 " << x << std::endl;}
  void foo2() { std::cout << "2 " << x << std::endl; }
  virtual void foo3() { std::cout << "3 " << x << std::endl; }
  static constexpr double x = 42.0;
};

class Bar : public Base
{
public:
  void foo1() override { std::cout << "1 " << x << std::endl; }
  static constexpr double x = 43.0;
};

int main()
{
  {
    Base* b = new Bar();
    b->foo1();
    b->foo2();
    b->foo3();
  }

  {
    Bar* b = new Bar();
    b->foo1();
    b->foo2();
    b->foo3();
  }

  {
    Base* b = new Base();
    b->foo1();
    b->foo2();
    b->foo3();
  }
}