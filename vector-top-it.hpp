#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    explicit Vector(size_t size);
    ~Vector();

    Vector(const Vector< T >&) = delete;
    Vector< T >& operator=(const Vector< T >&) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T>
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{

}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  throw std::logic_error("Bad id");
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{

}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  throw std::logic_error("Bad id");
}

#endif

