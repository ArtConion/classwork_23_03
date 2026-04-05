#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
#include <stdexcept>

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

    struct Iter;
    struct CIter;

    Iter begin() noexcept;
    Iter end() noexcept;
    CIter begin() const noexcept;
    CIter end() const noexcept;
    CIter cbegin() const noexcept;
    CIter cend() const noexcept;

    Iter insert(Iter pos, const T& val);
    Iter insert(Iter pos, size_t count, const T& val);
    Iter insert(Iter pos, CIter first, CIter last);
    Iter insert(Iter pos, Iter first, Iter last);

    Iter erase(Iter pos);
    Iter erase(Iter first, Iter last);
    Iter erase(Iter first, Iter last, const T& val);

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

    void reallocate(size_t new_capacity);
  };

  template< class T >
  struct Vector< T >::Iter
  {
    Iter() noexcept:
      ptr_(nullptr)
    {}

    explicit Iter(T* ptr) noexcept:
      ptr_(ptr)
    {}

    T& operator*() const noexcept
    {
      return *ptr_;
    }

    T* operator->() const noexcept
    {
      return ptr_;
    }

    Iter& operator++() noexcept
    {
      ++ptr_;
      return *this;
    }

    Iter operator++(int) noexcept
    {
      Iter tmp = *this;
      ++ptr_;
      return tmp;
    }

    Iter& operator--() noexcept
    {
      --ptr_;
      return *this;
    }

    Iter operator--(int) noexcept
    {
      Iter tmp = *this;
      --ptr_;
      return tmp;
    }

    Iter& operator+=(int n) noexcept
    {
      ptr_ += n;
      return *this;
    }

    Iter& operator-=(int n) noexcept
    {
      ptr_ -= n;
      return *this;
    }

    Iter operator+(int n) const noexcept
    {
      return Iter(ptr_ + n);
    }

    Iter operator-(int n) const noexcept
    {
      return Iter(ptr_ - n);
    }

    int operator-(const Iter& other) const noexcept
    {
      return static_cast<int>(ptr_ - other.ptr_);
    }

    T& operator[](int n) const noexcept
    {
      return ptr_[n];
    }

    bool operator==(const Iter& other) const noexcept
    {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const Iter& other) const noexcept
    {
      return ptr_ != other.ptr_;
    }

    bool operator<(const Iter& other) const noexcept
    {
      return ptr_ < other.ptr_;
    }

    bool operator<=(const Iter& other) const noexcept
    {
      return ptr_ <= other.ptr_;
    }

    bool operator>(const Iter& other) const noexcept
    {
      return ptr_ > other.ptr_;
    }

    bool operator>=(const Iter& other) const noexcept
    {
      return ptr_ >= other.ptr_;
    }

  private:
    T* ptr_;
  };

  template< class T >
  struct Vector< T >::CIter
  {
    CIter() noexcept:
      ptr_(nullptr)
    {}

    explicit CIter(const T* ptr) noexcept:
      ptr_(ptr)
    {}

    CIter(const Iter& other) noexcept:
      ptr_(&(*other))
    {}

    const T& operator*() const noexcept
    {
      return *ptr_;
    }

    const T* operator->() const noexcept
    {
      return ptr_;
    }

    CIter& operator++() noexcept
    {
      ++ptr_;
      return *this;
    }

    CIter operator++(int) noexcept
    {
      CIter tmp = *this;
      ++ptr_;
      return tmp;
    }

    CIter& operator--() noexcept
    {
      --ptr_;
      return *this;
    }

    CIter operator--(int) noexcept
    {
      CIter tmp = *this;
      --ptr_;
      return tmp;
    }

    CIter& operator+=(int n) noexcept
    {
      ptr_ += n;
      return *this;
    }

    CIter& operator-=(int n) noexcept
    {
      ptr_ -= n;
      return *this;
    }

    CIter operator+(int n) const noexcept
    {
      return CIter(ptr_ + n);
    }

    CIter operator-(int n) const noexcept
    {
      return CIter(ptr_ - n);
    }

    int operator-(const CIter& other) const noexcept
    {
      return static_cast<int>(ptr_ - other.ptr_);
    }

    const T& operator[](int n) const noexcept
    {
      return ptr_[n];
    }

    bool operator==(const CIter& other) const noexcept
    {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const CIter& other) const noexcept
    {
      return ptr_ != other.ptr_;
    }

    bool operator<(const CIter& other) const noexcept
    {
      return ptr_ < other.ptr_;
    }

    bool operator<=(const CIter& other) const noexcept
    {
      return ptr_ <= other.ptr_;
    }

    bool operator>(const CIter& other) const noexcept
    {
      return ptr_ > other.ptr_;
    }

    bool operator>=(const CIter& other) const noexcept
    {
      return ptr_ >= other.ptr_;
    }

  private:
    const T* ptr_;
  };

  template< class T >
  typename Vector< T >::Iter Vector< T >::begin() noexcept
  {
    return Iter(data_);
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::end() noexcept
  {
    return Iter(data_ + size_);
  }

  template< class T >
  typename Vector< T >::CIter Vector< T >::begin() const noexcept
  {
    return CIter(data_);
  }

  template< class T >
  typename Vector< T >::CIter Vector< T >::end() const noexcept
  {
    return CIter(data_ + size_);
  }

  template< class T >
  typename Vector< T >::CIter Vector< T >::cbegin() const noexcept
  {
    return CIter(data_);
  }

  template< class T >
  typename Vector< T >::CIter Vector< T >::cend() const noexcept
  {
    return CIter(data_ + size_);
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::insert(Iter pos, const T& val)
  {
    int index = pos - begin();
    insert(static_cast<size_t>(index), val);
    return begin() + index;
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::insert(Iter pos, size_t count, const T& val)
  {
    if (count == 0)
    {
      return pos;
    }

    int index = pos - begin();

    if (size_ + count > capacity_)
    {
      reallocate(size_ + count);
    }

    for (size_t i = size_; i > static_cast<size_t>(index); --i)
    {
      data_[i + count - 1] = data_[i - 1];
    }

    for (size_t i = 0; i < count; ++i)
    {
      data_[static_cast<size_t>(index) + i] = val;
    }

    size_ += count;
    return begin() + index;
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::insert(Iter pos, CIter first, CIter last)
  {
    int index = pos - this->begin();
    size_t count = static_cast<size_t>(last - first);

    if (count == 0)
    {
      return this->begin() + index;
    }

    if (size_ + count > capacity_)
    {
      reallocate(size_ + count);
    }

    for (size_t i = size_; i > static_cast<size_t>(index); --i)
    {
      data_[i + count - 1] = data_[i - 1];
    }

    CIter it = first;
    for (size_t i = 0; i < count; ++i)
    {
      data_[static_cast<size_t>(index) + i] = *it;
      ++it;
    }

    size_ += count;
    return this->begin() + index;
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::insert(Iter pos, Iter first, Iter last)
  {
    return insert(pos, CIter(first), CIter(last));
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::erase(Iter pos)
  {
    int index = pos - begin();
    erase(static_cast<size_t>(index));

    if (size_ == 0)
    {
      return end();
    }

    return begin() + index;
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::erase(Iter first, Iter last)
  {
    if (first == last)
    {
      return first;
    }

    int first_index = first - begin();
    int last_index = last - begin();
    size_t count = static_cast<size_t>(last_index - first_index);

    Vector<T> result(size_ - count);

    for (int i = 0; i < first_index; ++i)
    {
      result[i] = data_[i];
    }

    for (size_t i = static_cast<size_t>(last_index); i < size_; ++i)
    {
      result[static_cast<size_t>(first_index) + (i - static_cast<size_t>(last_index))] = data_[i];
    }

    swap(result);

    if (size_ == 0)
    {
      return end();
    }

    return begin() + first_index;
  }

  template< class T >
  typename Vector< T >::Iter Vector< T >::erase(Iter first, Iter last, const T& val)
  {
    if (first == last)
    {
      return first;
    }

    int first_index = first - begin();
    int last_index = last - begin();

    Vector<T> result;

    for (int i = 0; i < first_index; ++i)
    {
      result.pushBack(data_[i]);
    }

    for (int i = first_index; i < last_index; ++i)
    {
      if (data_[i] != val)
      {
        result.pushBack(data_[i]);
      }
    }

    for (size_t i = static_cast<size_t>(last_index); i < size_; ++i)
    {
      result.pushBack(data_[i]);
    }

    swap(result);

    if (size_ == 0)
    {
      return end();
    }

    return begin() + first_index;
  }

  template< class T >
  void Vector< T >::reallocate(size_t new_capacity)
  {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }

  template< class T >
  bool Vector< T >::operator==(const Vector< T >& rhs) const noexcept
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

  template< class T >
  bool Vector< T >::operator!=(const Vector< T >& rhs) const noexcept
  {
    return !(*this == rhs);
  }

  template< class T >
  Vector< T >::Vector():
    data_(nullptr),
    size_(0),
    capacity_(0)
  {}

  template< class T >
  Vector< T >::Vector(size_t size):
    data_(size ? new T[size] : nullptr),
    size_(size),
    capacity_(size)
  {}

  template< class T >
  Vector< T >::Vector(size_t size, const T& val):
    Vector(size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      data_[i] = val;
    }
  }

  template< class T >
  Vector< T >::~Vector()
  {
    delete[] data_;
  }

  template< class T >
  Vector< T >::Vector(const Vector< T >& rhs):
    Vector(rhs.getSize())
  {
    for (size_t i = 0; i < getSize(); ++i)
    {
      data_[i] = rhs.data_[i];
    }
  }

  template< class T >
  Vector< T >& Vector< T >::operator=(const Vector< T >& rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }

    Vector< T > cpy(rhs);
    swap(cpy);

    return *this;
  }

  template< class T >
  Vector< T >::Vector(Vector < T >&& rhs) noexcept:
    data_(rhs.data_),
    size_(rhs.size_),
    capacity_(rhs.capacity_)
  {
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
  }

  template<class T>
  Vector< T >& Vector< T >::operator=(Vector< T >&& rhs) noexcept
  {
    if (this != &rhs)
    {
      delete[] data_;
      data_ = rhs.data_;
      size_ = rhs.size_;
      capacity_ = rhs.capacity_;
      rhs.data_ = nullptr;
      rhs.size_ = 0;
      rhs.capacity_ = 0;
    }
    return *this;
  }

  template< class T >
  void Vector< T >::swap(Vector< T >& rhs) noexcept
  {
    T* tmp_data = data_;
    data_ = rhs.data_;
    rhs.data_ = tmp_data;

    size_t tmp_size = size_;
    size_ = rhs.size_;
    rhs.size_ = tmp_size;

    size_t tmp_capacity = capacity_;
    capacity_ = rhs.capacity_;
    rhs.capacity_ = tmp_capacity;
  }

  template< class T >
  bool Vector< T >::isEmpty() const noexcept
  {
    return !size_;
  }

  template< class T>
  size_t Vector< T >::getSize() const noexcept
  {
    return size_;
  }

  template< class T >
  size_t Vector< T >::getCapacity() const noexcept
  {
    return capacity_;
  }

  template< class T>
  void Vector< T >::pushBack(const T& val)
  {
    if (size_ == capacity_)
    {
      size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reallocate(new_capacity);
    }
    data_[size_++] = val;
  }

  template< class T >
  void Vector< T >::pushFront(const T& val)
  {
    Vector< T > result(getSize() + 1);
    for (size_t i = 0; i < getSize(); ++i)
    {
      result[i + 1] = (*this)[i];
    }
    result[0] = val;
    swap(result);
  }

  template< class T >
  void Vector< T >::insert(size_t pos, const T& val)
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
  void Vector< T >::insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e)
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
  void Vector< T >::erase(size_t pos)
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
  T& Vector< T >::operator[](size_t id) noexcept
  {
    return data_[id];
  }

  template< class T >
  const T& Vector< T >::operator[](size_t id) const noexcept
  {
    return data_[id];
  }

  template< class T >
  T& Vector< T >::at(size_t id)
  {
    if (id >= size_)
    {
      throw std::out_of_range("bad id");
    }
    return data_[id];
  }

  template< class T >
  const T& Vector< T >::at(size_t id) const
  {
    if (id >= size_)
    {
      throw std::out_of_range("bad id");
    }
    return data_[id];
  }

}

#endif

