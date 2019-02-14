#include <functional>
#include <iostream>

// some people say that auto and std::function<...> can be used interchangably to declare lambdas.
// this is a counter example using C++17.

// won't compile since std::function is not literal
// constexpr std::function<int(int)> get_x2() { return [](int value) { return 2*value; }; }

// will compile, `closure` is a literal type since c++17
constexpr auto get_x2_auto() { return [](int value) { return 2*value; }; }

int main() { std::cout << get_x2_auto()(21) << std::endl; }