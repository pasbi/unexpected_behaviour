#include <iostream>
#include <vector>

/*
 * "universal references" will not work if the deduced type is templated.
 * see https://stackoverflow.com/q/21022724/4248972
 */

template<typename T> void uref_fun_1(T&& x) {}
template<typename T, template<typename ...> class ContainerT> void uref_fun_2(ContainerT<T>&& x) {}

int main()
{
  std::vector<int> vec { 1, 2, 3 };
  const std::vector<int> const_vec { 1, 2, 3 };

  uref_fun_1(vec);        // will work as the `T&&`-argument is not a template.
  uref_fun_1(const_vec);

  uref_fun_2(vec);        // will not work as the `ContainerT<T>&&`-argument in `uref_fun_2`
  uref_fun_2(const_vec);  // is a deduced template parameter (`ContainerT<...>`)

}