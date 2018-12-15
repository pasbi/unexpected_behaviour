#include <iostream>

// see: https://isocpp.org/wiki/faq/strange-inheritance#hiding-rule

// if you derive from a class and declare a function with same name (but other signature),
// the base class' function becomes hidden. You can only call it by explicitely saying that
// you want to use the base class' implementation.
// That apparently happens before overload resolution:
// It may be that there is a perfectly matching overload, which is, however, not being considered
// because it is hidden by a not-matching declaration (-> compiler erro) or, even worse, by a
// matching declaration (unexpected behavior).

enum class Enum { v };

struct BaseInt
{
  void foo(int) { std::cout << "BaseInt::foo(int)" << std::endl; }
};

struct DerivesInt : BaseInt
{
  void foo(double) { std::cout << "DerivesInt::foo(double)" << std::endl; }
};

int main()
{
  // calls `foo(double)`, because `BaseInt::foo(int)` is hidden. If `int` couldn't be implicitely
  // converted to `double`, this line wouldn't compile.
  DerivesInt().foo(42);

  // call foo(int) explicitely
  DerivesInt().BaseInt::foo(42);

}

