#include <vector>
#include <algorithm>
#include <iostream>

// it's possible that a const-ref changes its value.
// Actually it's not very surprising, as the const only means that the referenced variable does not
// change, without putting any constraint on its value itself.
// Though, the behaviour might be unexpected or not intuitive perhaps.

struct S
{

void remove(const int& x)
{
  std::cout << x << std::endl;
  xs.erase(std::remove(xs.begin(), xs.end(), x), xs.end());

  // if remove is called like depicted in `main`, `x` will have change its value here.
  std::cout << x << std::endl;
}

std::vector<int> xs { 1, 2, 3, 4, 5 };

};

int main()
{
  S s;
  s.remove(s.xs[2]);
}