#include <iostream>

// It might be surprising that compiler prefers to cast a pointer to bool
// over applying an implicit constructor.

struct Foo { Foo(int*) {} };
void bar(bool) { std::cout << "bool" << std::endl; }
void bar(Foo) { std::cout << "Foo" << std::endl; }
int main() { bar(static_cast<int*>(nullptr)); }
