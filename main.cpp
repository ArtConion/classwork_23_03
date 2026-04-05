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

bool test8()
{
  Vector< int > a(3,1);
  Vector< int > b(3,1);
  return a == b;
}

bool test9()
{
  Vector< int > a(3,1);
  Vector< int > b(3,2);
  return a != b;
}

bool test10()
{
  Vector< int > v;
  return v.getCapacity() == 0;
}

bool test11()
{
  size_t size = 3ull;
  Vector< int > v(size, 0);
  return v.getCapacity() == size;
}

bool test12()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  const int& value = v[0];
  return value == 1;
}


bool test13()
{
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  const int& value = v[0];
  return value == 1;
}

bool test14()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  v.pushBack(2);
  return v[size] == 2;
}

bool test15()
{
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  v.pushBack(2);
  v.pushBack(3);
  return v[size+1] == 3;
}

bool test16()
{
  Vector< int > v(2, 0);
  Vector< int > yav = v;
  return yav == v;
}

bool test17()
{
  Vector< int > v;
  Vector< int > yav(2, 0);
  bool res = v != yav;
  v = yav;
  return res && yav == v;
}

bool test18()
{
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);

  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);

  v.swap(yav);
  return cpy_v == yav && cpy_yav == v;
}

bool test19()
{
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);

  Vector< int > yav = std::move(v);
  return yav == cpy_v;
}

bool test20()
{
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;

  yav = std::move(v);
  return yav == cpy;
}

bool test21()
{
    Vector<int> v(3, 1);
    v.insert(1, 5);

    return v.getSize() == 4 && v[0] == 1 && v[1] == 5 && v[2] == 1 && v[3] == 1;
}

bool test22()
{
    Vector<int> v(3, 1);
    try
    {
        v.insert(5, 99);
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

bool test23()
{
    Vector<int> v(2, 1);
    Vector<int> toInsert(3, 5);
    v.insert(1, toInsert, 0, 3);

    bool result = v.getSize() == 5;
    result = result && v[0] == 1;
    result = result && v[1] == 5 && v[2] == 5 && v[3] == 5;
    result = result && v[4] == 1;
    return result;
}

bool test24()
{
    Vector<int> v(2, 1);
    Vector<int> toInsert(3, 5);

    try
    {
        v.insert(1, toInsert, 5, 3);
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

bool test25()
{
    Vector<int> v(5, 0);
    v[1] = 1;
    v[2] = 2;
    v[3] = 3;
    v.erase(2);

    bool result = v.getSize() == 4;
    result = result && v[0] == 0 && v[1] == 1;
    result = result && v[2] == 3 && v[3] == 0;
    return result;
}

bool test26()
{
    Vector<int> v(3, 1);
    try
    {
        v.erase(3);
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
    { test1, "Default constructed vector is empty" },
    { test2, "Defaul constructed vector size is zero" },
    { test3, "Vector constructed with size has non-zero size" },
    { test4, "In range access does not generate exceptions" },
    { test5, "Out of range access generates std::out_of_range exception" },
    { test6, "In range access for const vector does not generate exceptions" },
    { test7, "Out of range access for const vector generates std::out_of_range exception" },
    { test8, "Operator ==" },
    { test9, "Operator !=" },
    { test10, "Defaul constructed vector capacity is zero" },
    { test11, "Vector constucted with capacity ihas non-zero capacity" },
    { test12, "Operator [] for range access in vector" },
    { test13, "Operator [] for range access in const vector" },
    { test14, "pushBack method with extention of capacity" },
    { test15, "pushBack method without extention of capacity" },
    { test16, "Copy constructor" },
    { test17, "Copy assignment operator" },
    { test18, "Swap for 2 vectors" },
    { test19, "Move constructor" },
    { test20, "Move assignment operator" },
    { test21, "insert by index (middle)" },
    { test22, "insert by index (out of range throws)" },
    { test23, "insert range from vector (middle)" },
    { test24, "insert range (invalid source range throws)" },
    { test25, "erase by index (middle)" },
    { test26, "erase by index (out of range throws)" },
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
