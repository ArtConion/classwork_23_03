#include <iostream>
#include "vector-top-it.hpp"


bool testDefaultVector()
{
  using topit::Vector;
  Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = bool(*)();
  test_t tests[] = {
    testDefaultVector
  };

  size_t size = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < size ; ++i)
  {
    std::cout << tests[i]() << ": " << i << '\n';
  }
}
