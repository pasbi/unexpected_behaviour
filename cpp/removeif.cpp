#include <algorithm>
#include <vector>
#include <iostream>

// abusing `std::remove_if` to sort the container in a special way leads to undefined behavior
// because the inserted values at the end have unspecified value.
// If you just want to move the item of interest to the end of the range, use `move_if`, which is,
// sadly enough, not in the standard.

template<typename Ts>
void print(const Ts& ts)
{
  for (auto&& t : ts) {
    std::cout << t << ", ";
  }
  std::cout << std::endl;
}

template<typename iterator, typename pred>
iterator move_if(iterator begin, iterator end, const pred& predicate)
{
  const iterator it = std::find_if(begin, end, predicate);
  std::iter_swap(it, std::prev(end));
  return std::prev(end);
}

int main()
{
  {
    std::vector<int> vector { 1, 2, 3, 4, 5 };
    print(vector);
    auto it = std::remove_if(vector.begin(), vector.end(), [](auto&& i) { return i == 3; });
    print(vector);
    std::cout << std::distance(vector.begin(), it) << std::endl;
  }
  {
    std::vector<int> vector { 1, 2, 3, 4, 5 };
    print(vector);
    auto it = move_if(vector.begin(), vector.end(), [](auto&& i) { return i == 3; });
    print(vector);
    std::cout << std::distance(vector.begin(), it) << std::endl;
  }
}

