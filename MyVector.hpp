#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
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
    T& at(size_t index);
    const T& at(size_t index) const;
    T& at(int index);
    const T& at(int index) const;

    void reserve(size_t n);
    void resize(size_t n);
    void push_back(const T& val);
    void push_back(T&& val);

    template <typename... Args>
    void emplace_back(Args&&... args);

    T pop();
    void clear();

    // const T* get() const { return m_arr; }
    void print() const;

private:
    T* m_arr;
    T* m_size;
    T* m_capacity;

};

template <typename T>
MyVector<T>::MyVector()
    : m_arr { static_cast<T*>(::operator new(sizeof(T))) }
    , m_size { m_arr }
    , m_capacity { m_arr + 1 }
{}

template <typename T>
MyVector<T>::MyVector(size_t n)
    : m_arr { n == 0 ? static_cast<T*>(::operator new(sizeof(T))) : static_cast<T*>(::operator new(n * sizeof(T))) }
    , m_size { m_arr }
    , m_capacity { m_arr + (n == 0 ? 1 : n) }
{
    std::uninitialized_value_construct_n(m_arr, n);
    m_size = m_arr + n;
}

template <typename T>
MyVector<T>::MyVector(size_t n, const T& val)
    : m_arr { n == 0 ? static_cast<T*>(::operator new(sizeof(T))) : static_cast<T*>(::operator new(n * sizeof(T))) }
    , m_size { m_arr }
    , m_capacity { m_arr + (n == 0 ? 1 : n) }
{
    std::uninitialized_fill_n(m_arr, n, val);
    m_size = m_arr + n;
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
    : m_arr { list.size() == 0 ? static_cast<T*>(::operator new(sizeof(T))) : static_cast<T*>(::operator new(list.size() * sizeof(T))) }
    , m_size { m_arr }
    , m_capacity { m_arr + (list.size() == 0 ? 1 : list.size()) }
{
    std::uninitialized_copy(list.begin(), list.end(), m_arr);
    m_size = m_arr + list.size();
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    : m_arr { static_cast<T*>(::operator new(other.capacity() * sizeof(T))) }
    , m_size { m_arr }
    , m_capacity { m_arr + other.capacity() }
{
    std::uninitialized_copy(other.m_arr, other.m_size, m_arr);
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

    std::destroy(m_arr, m_size);
    ::operator delete(m_arr);
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
    std::destroy(m_arr, m_size);
    ::operator delete(m_arr);
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
    return m_arr[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const
{
    return m_arr[index];
}

template <typename T>
T& MyVector<T>::operator[](int index)
{
    if (index >= 0)
        return m_arr[index];

    return *(m_size + index);
}

template <typename T>
const T& MyVector<T>::operator[](int index) const
{
    if (index >= 0)
        return m_arr[index];

    return *(m_size + index);
}

template <typename T>
T& MyVector<T>::at(size_t index)
{
    if (index >= this->size())
        throw std::out_of_range("Attempting to access vector out of bounds");

    return m_arr[index];
}

template <typename T>
const T& MyVector<T>::at(size_t index) const
{
    if (index >= this->size())
        throw std::out_of_range("Attempting to access vector out of bounds");

    return m_arr[index];
}

template <typename T>
T& MyVector<T>::at(int index)
{
    if (index >= 0)
        return this->at(static_cast<size_t>(index));

    if (index < -static_cast<int>(this->size()))
        throw std::out_of_range("Attempting to access vector out of bounds");

    return *(m_size + index);
}

template <typename T>
const T& MyVector<T>::at(int index) const
{
    if (index >= 0)
        return this->at(static_cast<size_t>(index));

    if (index < -static_cast<int>(this->size()))
        throw std::out_of_range("Attempting to access vector out of bounds");

    return *(m_size + index);
}

template <typename T>
void MyVector<T>::reserve(size_t n)
{
    if (n <= this->capacity())
        return;

    auto new_arr { n == 0 ? static_cast<T*>(::operator new(sizeof(T))) : static_cast<T*>(::operator new(n * sizeof(T))) };
    auto old_size { this->size() };

    std::uninitialized_move(m_arr, m_size, new_arr);

    std::destroy(m_arr, m_size);
    ::operator delete(m_arr);

    m_arr = new_arr;
    m_size = m_arr + old_size;
    m_capacity = m_arr + (n == 0 ? 1 : n);
}

template <typename T>
void MyVector<T>::resize(size_t n)
{
    if (n <= this->capacity())
    {
        if (n > this->size())
            std::uninitialized_value_construct(m_size, m_arr + n);
        else
            std::destroy(m_arr + n, m_size);

        m_size = m_arr + n;
        return;
    }

    this->reserve(n);

    std::uninitialized_value_construct(m_size, m_arr + n);
    m_size = m_arr + n;
}

template <typename T>
void MyVector<T>::push_back(const T& val)
{
    if (m_size == m_capacity)
    {
        auto old_size { this->size() };
        this->reserve(old_size == 0 ? 1 : old_size * 2);
    }

    new (m_size) T(val);
    ++m_size;
}

template <typename T>
void MyVector<T>::push_back(T&& val)
{
    if (m_size == m_capacity)
    {
        auto old_size { this->size() };
        this->reserve(old_size == 0 ? 1 : old_size * 2); // this might throw
    }

    new (m_size) T(std::move(val));
    ++m_size;
}

template <typename T>
template <typename... Args>
void MyVector<T>::emplace_back(Args&&... args)
{
    if (m_size == m_capacity)
    {
        auto old_size { this->size() };
        this->reserve(old_size == 0 ? 1 : old_size * 2);
    }

    new (m_size) T(std::forward<Args>(args)...);
    ++m_size;
}

template <typename T>
T MyVector<T>::pop()
{
    if (this->size() == 0)
        throw std::length_error("Vector must be non-empty");

    T tmp { std::move(*(m_size - 1)) };
    std::destroy_at(m_size - 1);
    --m_size;

    return tmp;
}

template <typename T>
void MyVector<T>::clear()
{
    std::destroy(m_arr, m_size);
    m_size = m_arr;
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
