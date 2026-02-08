#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
template <typename T>
class MyVector
{
public:
    MyVector();
    MyVector(size_t n);
    MyVector(size_t n, const T& val);
    MyVector(std::initializer_list<T> list);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    size_t size() const { return static_cast<size_t>(m_size - m_arr); }
    size_t capacity() const { return static_cast<size_t>(m_capacity - m_arr); }
    bool empty() const { return m_size == m_arr; }

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    // iterators soon
    
    void reserve(size_t n);
    void resize(size_t n);
    void push(const T& val);
    void push(T&& val);
    T pop();
    void clear() { m_size = m_arr; }

    // const T* get() const { return m_arr; }
    void print() const;

private:
    T* m_arr;
    T* m_size;
    T* m_capacity;

};

template <typename T>
MyVector<T>::MyVector()
    : m_arr { new T[1] {} }
    , m_size { m_arr }
    , m_capacity { m_arr + 1 }
{}

template <typename T>
MyVector<T>::MyVector(size_t n)
    : m_arr { n == 0 ? new T[1] {} : new T[n] {} }
    , m_size { m_arr + n }
    , m_capacity { n == 0 ? m_arr + 1 : m_arr + n }
{}

template <typename T>
MyVector<T>::MyVector(size_t n, const T& val)
    : m_arr { n == 0 ? new T[1] {} : new T[n] {} }
    , m_size { m_arr + n }
    , m_capacity { n == 0 ? m_arr + 1 : m_arr + n }
{
    std::fill_n(m_arr, n, val);
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
    : MyVector(list.size())
{
    std::copy(list.begin(), list.end(), m_arr);
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    : MyVector(other.capacity())
{
    std::copy(other.m_arr, other.m_size, m_arr);
    m_size = m_arr + other.size();
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : m_arr { other.m_arr }
    , m_size { other.m_size }
    , m_capacity { other.m_capacity }
{
    other.m_arr = nullptr;
    other.m_size = nullptr;
    other.m_capacity = nullptr;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this == &other)
        return *this;

    MyVector temp{ other };
    std::swap(m_arr, temp.m_arr);
    std::swap(m_size, temp.m_size);
    std::swap(m_capacity, temp.m_capacity);

    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept
{
    if (this == &other)
        return *this;

    delete[] m_arr;
    m_arr = other.m_arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_arr = nullptr;
    other.m_size = nullptr;
    other.m_capacity = nullptr;

    return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_arr;
}

template <typename T>
T& MyVector<T>::front()
{
    if (this->empty())
        throw std::length_error("Vector must be non-empty");

    return *m_arr;
}

template <typename T>
const T& MyVector<T>::front() const
{
    if (this->empty())
        throw std::length_error("Vector must be non-empty");

    return *m_arr;
}

template <typename T>
T& MyVector<T>::back()
{
    if (this->empty())
        throw std::length_error("Vector must be non-empty");

    return *(m_size - 1);
}

template <typename T>
const T& MyVector<T>::back() const
{
    if (this->empty())
        throw std::length_error("Vector must be non-empty");

    return *(m_size - 1);
};

template <typename T>
T& MyVector<T>::operator[](size_t index)
{
    if (index >= this->size())
        throw std::out_of_range("Attempting to access vector out of bounds");

    return m_arr[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const
{
    if (index >= this->size())
        throw std::out_of_range("Attempting to access vector out of bounds");

    return m_arr[index];
}

template <typename T>
T& MyVector<T>::operator[](int index)
{
    if (index >= 0)
        return (*this)[static_cast<size_t>(index)];

    if (index < -static_cast<int>(this->size()))
        throw std::out_of_range("Attempting to access vector out of bounds");

    return *(m_size + index);
}

template <typename T>
const T& MyVector<T>::operator[](int index) const
{
    if (index >= 0)
        return (*this)[static_cast<size_t>(index)];

    if (index < -static_cast<int>(this->size()))
        throw std::out_of_range("Attempting to access vector out of bounds");

    return *(m_size + index);
}

template <typename T>
void MyVector<T>::reserve(size_t n)
{
    if (n <= this->capacity())
        return;

    auto new_arr { n == 0 ? new T[1] {} : new T[n] {} };

    auto oldSize { this->size() };
    std::copy(m_arr, m_size, new_arr);

    delete[] m_arr;
    m_arr = new_arr;
    m_size = m_arr + oldSize;
    m_capacity = (n == 0 ? new_arr + 1 : new_arr + n);
}

template <typename T>
void MyVector<T>::resize(size_t n)
{
    if (n <= this->capacity())
    {
        m_size = m_arr + n;
        return;
    }

    auto new_arr { n == 0 ? new T[1] {} : new T[n] {} };

    std::copy(m_arr, m_size, new_arr);
    
    delete[] m_arr;
    m_arr = new_arr;
    m_size = m_arr + n;
    m_capacity = (n == 0 ? m_arr + 1 : m_arr + n);
}

template <typename T>
void MyVector<T>::push(const T& val)
{
    if (m_size == m_capacity)
    {
        auto oldSize { this->size() };
        this->resize(oldSize == 0 ? 1 : oldSize * 2);
        m_size = m_arr + oldSize;
    }

    *m_size = val;
    ++m_size;
}

template <typename T>
void MyVector<T>::push(T&& val)
{
    if (m_size == m_capacity)
    {
        auto oldSize { this->size() };
        this->resize(oldSize == 0 ? 1 : oldSize * 2); // this might throw
        m_size = m_arr + oldSize; }

    *m_size = std::move_if_noexcept(val);
    ++m_size;
}

template <typename T>
T MyVector<T>::pop()
{
    if (this->size() == 0)
        throw std::length_error("Vector must be non-empty");

    return *(--m_size);
}

template <typename T>
void MyVector<T>::print() const
{
    size_t size { this->size() };
    for (size_t i {}; i < size; ++i)
    {
        std::cout << m_arr[i];
        if (i != size - 1)
            std::cout << ' ';
    }

    if (size > 0)
        std::cout << '\n';
}

#endif
