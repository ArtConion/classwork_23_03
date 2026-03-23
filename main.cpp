#include <iostream>
#include "vector-top-it.hpp"

using topit::Vector;
bool test1()
{
  Vector< int > v;
  return v.isEmpty();
}

bool test2()
{
  Vector< int > v;
  return v.getSize() == 0;
}

bool test3()
{
  size_t size = 3ull;
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try
  {
    int& value =v.at(0);
    return value == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool test5()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try
  {
    v.at(size + 1);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool test6()
{
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  try
  {
    const int& value = v.at(0);
    return value == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool test7()
{
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 0);
  try
  {
    v.at(size + 1);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

int main()
{
  using test_t = bool(*)();
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
    {test1, "Default constructed vector is empty"},
    {test2, "Defaul constructed vector size is zero"},
    {test3, "Vector constructed with size has non-zero size"},
    {test4, "In range access does not generate exceptions"},
    {test5, "Out of range access generates std::out_of_range exception"},
    {test6, "In range access for const vector does not generate exceptions"},
    {test7, "Out of range access for const vector generates std::out_of_range exception"}
  };

  size_t size = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  bool result = true;
  size_t succceses = 0, fails = 0;

  for (size_t i = 0; i < size ; ++i)
  {
    bool case_result = tests[i].first();
    result = result && case_result;
    succceses += case_result;
    fails += !case_result;
    std::cout << case_result << ": " << tests[i].second << '\n';
  }
  std::cout << "SUMMARY\n";
  std::cout << result << ": tests RESULTS\n";
  std::cout << fails << ": failed tests\n";
  std::cout << succceses << ": successed tests\n";

}
