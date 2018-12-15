#include <memory>
#include <iostream>

// Let's suppose you have a tree structure.
// An item gets represented by the `Base` class, which acts as a wrapper around any type `T`.
// A `Base` can only be constructed by providing a reference to a parent of type `T`.

template<typename T>
struct Base
{
  Base(T& parent) : parent(&parent) { std::cout << "  Base(T&)\n"; }
  Base() = default;
  T* parent;
};

struct Item : Base<Item>
{
  Item(Item& parent) : Base(parent) { std::cout << "  Item(Item&)\n"; }
  // using Base<Item>::Base;
  Item() = default;
};

int main()
{
  std::cout << std::boolalpha;
  {
    std::cout << "\nExample 1: explicit ctor\n";
    std::cout << "create tree: \n";
    Item root;
    Item child(root);

    std::cout << "assign: \n";
    Base<Item> assigned = Base<Item>(child);

    // `assigned.parent` was set to `child` using the ctor of `Base`.
    // hence, it is expected that `assigned.parent` actually is `child`.
    std::cout << (assigned.parent == &child) << std::endl;
  }

  {
    std::cout << "\nExample 2: expected assignment, but actually implicit ctor.\n";
    std::cout << "create tree: \n";
    Item root;
    Item child(root);

    std::cout << "assign: \n";
    // we'd expect that the assignment operator copies the `child.parent` into `assigned.parent`.
    Base<Item> assigned = child;

    // so we'd expect that `assigned` and `child` have same parent.
    std::cout << (assigned.parent == child.parent) << std::endl;

    // but that's not the case. Instead, the constructor `Base(T&)` gets called and sets
    // `assigned.parent` to `child`.
    std::cout << (assigned.parent == &child) << std::endl;

    // That is, implicit constructor calls are preferred over assignment.
    // Note: make `Base`-ctor explicit to make Example 2 behave as expected.
  }

}
