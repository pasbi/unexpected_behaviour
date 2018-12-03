#include <iostream>

/**
 * This example shows how to make members of privately inherted base classes or protected members
 * of base classes publicly available in the derived class, without reimplementing them.
 * The technique is very related to constructor inheritance.
 */

class PrivateBase
{
public:
  void privately_inherited(int argument) {}

  // it also works with operators.
  PrivateBase operator+(int x) const { return *this; }

  // Note: though `PrivateBase operator+(const PrivateBase& other) const` could be made public
  // using the same technique, expressions like `PrivateBase() + Derived()` wouldn't compile
  // since `Derived` couldn't be downcasted to `PrivateBase` as the inhertance relationship is
  // hidden.
  PrivateBase operator+(const PrivateBase& other) const { return *this; }
};

class PublicBase
{
protected:
  void protected_member(int argument) {}
};

class Derived
  : private PrivateBase
  , public PublicBase   // would work the same with protected or private.
{
public:
  using PrivateBase::privately_inherited;
  using PrivateBase::operator+;
  using PublicBase::protected_member;

};

int main()
{
  // member from privately inherited class is visible
  Derived().privately_inherited(42);

  // protected member from inherited class is visible
  Derived().protected_member(43);

  // PrivateBase::operator+(int) is visible
  Derived() + 2;

  // PrivateBase::operator+(const PrivateBase&) is visible
  Derived() + PrivateBase();

  // fail: cannot convert Derived to PrivateBase (that's the point with private inheritance)
  // Derived() + Derived();

  return 0;
}