#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    Vector(size_t size, const T& val);
    ~Vector();

    Vector(const Vector< T >&);
    Vector< T >& operator=(const Vector< T >&);
    Vector(Vector < T >&&) noexcept;
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T >&) noexcept;
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& val);
    void pushFront(const T& val);

    void insert(size_t pos, const T& val);
    void insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e);
    void erase(size_t pos);

    // H/W
    // 1. Реализовать итераторы для вектора (Сами итераторы не тестировать)
    // 2. Придумать по 3 штуки insert/erase с итераторами (+ константные)
    struct VectorIT;
    void insert(VectorIT pos, const T& val);
    void erase(VectorIT pos);

    template< class IT >
    void insert(VectorIT pos, IT begin, IT end);
    // ...

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    bool operator==(const Vector< T >& rhs) const noexcept;
    bool operator!=(const Vector< T >& rhs) const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);
  };
}

template < class T >
bool topit::Vector< T >::operator==(const Vector< T >& rhs) const noexcept
{
  if (size_ != rhs.getSize())
  {
    return false;
  }

  for (size_t i = 0; i < size_; ++i)
  {
    if (data_[i] != rhs.data_[i])
    {
      return false;
    }
  }

  return true;
}

template < class T >
bool topit::Vector< T >::operator!=(const Vector< T >& rhs) const noexcept
{
  return !(*this == rhs);
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
topit::Vector< T >::Vector(size_t size, const T& val):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = val;
  }
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }

  Vector< T > cpy(rhs);
  swap(cpy);

  return *this;
}
template< class T >
topit::Vector< T >::Vector(Vector < T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template<class T>
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
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
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T>
void topit::Vector< T >::pushBack(const T& val)
{
  if (size_ == capacity_)
  {
    T* newData = new T[size_ * 2];
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }
    T* tmp = data_;
    data_ = newData;
    delete[] tmp;
    capacity_ *= 2;
  }
  data_[size_++] = val;
}

template< class T >
void topit::Vector< T >::pushFront(const T& val)
{
  Vector< T > result(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i)
  {
    result[i + 1] = (*this)[i];
  }
  swap(result);
}

template< class T >
void topit::Vector< T >::insert(size_t pos, const T& val)
{
    if (pos > size_)
    {
        throw std::out_of_range("insert position out of range");
    }

    Vector<T> result(size_ + 1);

    for (size_t i = 0; i < pos; ++i)
    {
        result[i] = data_[i];
    }

    result[pos] = val;

    for (size_t i = pos; i < size_; ++i)
    {
        result[i + 1] = data_[i];
    }

    swap(result);
}

template< class T >
void topit::Vector< T >::insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e)
{
    if (pos > size_)
    {
        throw std::out_of_range("insert position out of range");
    }
    if (b > e || e > rhs.getSize())
    {
        throw std::out_of_range("source range out of range");
    }

    size_t count = e - b;

    Vector<T> result(size_ + count);

    for (size_t i = 0; i < pos; ++i)
    {
        result[i] = data_[i];
    }

    for (size_t i = b; i < e; ++i)
    {
        result[pos + (i - b)] = rhs[i];
    }

    for (size_t i = pos; i < size_; ++i)
    {
        result[count + i] = data_[i];
    }

    swap(result);
}

template< class T >
void topit::Vector< T >::erase(size_t pos)
{
    if (pos >= size_)
    {
        throw std::out_of_range("erase position out of range");
    }

    if (size_ == 1)
    {
        Vector<T> result;
        swap(result);
        return;
    }
    Vector<T> result(size_ - 1);

    for (size_t i = 0; i < pos; ++i)
    {
        result[i] = data_[i];
    }

    for (size_t i = pos + 1; i < size_; ++i)
    {
        result[i - 1] = data_[i];
    }

    swap(result);
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  return data_[id];
}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  return const_cast< T& >(static_cast< const Vector< T >* >(this)->at(id));
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

#endif

