#include <iostream>

struct Base
{
  std::string name;
};

struct EmptyStruct { };

struct AnotherBase
{
  // AnotherBase is non-zero even if its only member is zero-size.
  EmptyStruct s;
};

struct Bar : AnotherBase, Base { };

int main()
{
  Bar* bar = new Bar;
  bar->name = "My name is bar";

  void* ptr = static_cast<Base*>(bar);

#define SINGLE_CAST 1
  
#if SINGLE_CAST
  // this is UB since a void* must not be casted to a derived class.
  std::cout << "direct cast: "
            << static_cast<Bar*>(ptr)->name << std::endl;
#else

  // this works since the casting the void* to Base* is safe and static_cast to Bar* does
  // what one expectes.
  // note that the reinterpret_cast actually does nothing, i.e., it onlt changes the
  // visible type for the compiler. One could replace reinterpret_cast with static_cast.
  // However, reinterpret_cast explicitely tells that no pointer arithmetic happens here.
  // On the other hand, static_cast advanced the pointer as AnotherBase has non-zero size.
  std::cout << "step cast: "
            << static_cast<Bar*>(reinterpret_cast<Base*>(ptr))->name << std::endl;
#endif

  // Remeber: static_cast from void* is dangerous.
  // The compiler lacks important information and cannot do the cast correctly.
  
}
