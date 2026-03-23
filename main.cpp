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
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
    {testDefaultVector, "Default constructed vector must be empty"}
  };

  size_t size = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < size ; ++i)
  {
    std::cout << tests[i].first() << ": " << tests[i].second << '\n';
  }
}
