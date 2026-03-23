#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();


    bool isEmpty() const noexcept;

  private:
    T* data;
    size_t size, capacity;
  };


}

#endif

