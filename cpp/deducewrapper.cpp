#include <algorithm>
#include <vector>
#include <iostream>

// Let's consider we want simplify the use of std::transform by introducing a wrapper function.
// The funcion should transform any `Container<S>` to `Container<T>` with arbitrary `T` and `S`
// and a suitable mapper from `S` -> `T`.

// first draft:  Container<T> transform(Container<S> ss, F mapper);

// both `S` and `Container` shall be deduced, it is not possible to deduce `T` so we must
// explicitely provide it. Hence, `T` should be the first template parameter

#ifdef EXAMPLE_1
template<typename T, template<typename ...> class Container, typename S, typename F>
Container<T> transform(Container<S> ss, F mapper)
{
  Container<T> ts;
  std::transform(std::begin(ss), std::end(ss), std::back_inserter(ts), mapper);
  return ts;
}
#endif

// okay, but there is a flaw:
// `ss` is passed by value. What if copying `Container<S>` is expensive or prohibited?
// proposal A: passing by const-ref: change `Container<S>` to `const Container<S>&`
//    + temporaries can be passed to const-ref still
//    + copying is avoided under all circumstances
//    - not possible to use non-const `S` in `mapper`.
// proposal B: passing by ref: change `Container<S>` to `Container<S>&`
//    - temporaries and const values cannot be passed anymore, even if mapper does not require
//      non-const access to `S`.
//    + copying is avoided under all circumstances
//    - possible to use non-const `S` in `mapper`.
// proposal C: using "universal-reference"-technique
//    + for temporaries and const values it behaves like (A)
//    + for non-temporary, non-const values it behaves like (B)
//    - not possible with templated arguments
//
// (A) is what I've used for a long time. However, it became unhandy when mapper was required to
//  produce a wrapper around `S` which requires non-const access to `S`.
// (B) is not a real option. If we were not able to pass temporary or const values, the approach
//  wouldn't gain much convenience compared to std::transform.
// (C) That's the way to go. We just need to find a way to work around the technical issue.

// Let's implement (C) and see what happens. I will also replace the return type with `auto`.

#ifdef EXAMPLE_2
template<typename T, template<typename ...> class Container, typename S, typename F>
auto transform(Container<S>&& ss, F mapper)
{
  Container<T> ts;
  std::transform(std::begin(ss), std::end(ss), std::back_inserter(ts), mapper);
  return ts;
}

// looks very nice, but will not compile without the `std::move`.
// But that's certainly not what we want.
// The problem is that "universal-reference"-matching does not occur because the argument of
// interest (first argument in ::transform) is a template argument and it simply does not work
// with template agumemts (https://stackoverflow.com/q/21022724/4248972)

int main()
{
  std::vector<int> vec { 1, 2, 3 };
  const auto mapper = [](int i) { return i / 2.0; };
  auto vec_div_2 = ::transform<double>(std::move(vec), mapper);

  std::cout << vec_div_2[0] << std::endl;
}

#endif

// Okay when it's not possible to match templated types, lets not use templated types.
// Proposed signature:
#ifdef EXAMPLE_3
template<typename T, typename ContainerS, typename F> auto transform(ContainerS&& ss, F mapper);
#endif
// while it solves our problem, it introduces another problem: How should we define the return
// type? We cannot write `Container<T>` because there is no `Container<...>` anymore.
// We need some way to extract the `Container` from `ContainerS`.

// declaring a struct like
//    template<templaye<typename...> class Container, typename T> struct
//      { using container = Container<T> };
// and attempting to use `ContainerS` as first template parameter will not work because
// `ContainerS` is not a templated type but the first parameter is expected to be templated.
// Unfortunately I did not find a solution to properly declare the desired `Container<T>`-type
// directly, but I was able to find a function which creates a plain `Container<T>` using
// overloading. It requires passing an ugly dummy value, but I guess that's

template<typename T, template<typename...> class Container, typename S>
auto make_container(const Container<S>&) { return Container<T>(); }

template<typename T, typename ContainerS, typename F> auto transform(ContainerS&& ss, F mapper)
{
  auto ts = make_container<T>(ss);
  std::transform(std::begin(ss), std::end(ss), std::back_inserter(ts), mapper);
  return ts;
}

int main()
{
  std::vector<int> vec { 1, 2, 3 };
  const auto mapper = [](int i) { return i / 2.0; };
  auto vec_div_2 = ::transform<double>(std::move(vec), mapper);

  std::cout << vec_div_2[0] << std::endl;
}




