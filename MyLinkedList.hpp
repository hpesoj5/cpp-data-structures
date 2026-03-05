#ifndef MyList_H
#define MyList_H

#include <memory>
#include <cstddef>
#include <utility>

template <typename T>
struct Node
{
    T val;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;    // non-owning

    Node(const T& val_, std::shared_ptr<Node> next_, std::weak_ptr<Node> prev_)
        : val { val_ }
        , next { std::move(next_) }
        , prev { prev_ }
    {}

    Node(T&& val_, std::shared_ptr<Node> next_, std::weak_ptr<Node> prev_)
        : val { std::move(val_) }
        , next { std::move(next_) }
        , prev { prev_ }
    {}

    Node(const Node& other) = delete;
    Node& operator=(const Node& other) = delete;

    Node(Node&& other) noexcept
        : val { std::move(other.val) }
        , next { std::move(other.next) }
        , prev { other.prev }
    {}

    Node& operator=(Node&& other) noexcept
    {
        if (this == &other)
            return *this;

        val = std::move(other.val);
        next = std::move(other.next);
        prev = other.prev;

        return *this;
    }

    ~Node() = default;
};

template <typename T>
class MyList
{
public:
    MyList();
    MyList(const MyList& other);
    MyList(MyList&& other) noexcept;
    MyList& operator=(const MyList& other);
    MyList& operator=(MyList&& other) noexcept;
    ~MyList();

    // class iterator
    // {

    // };

    // getters
    T& front() const;
    T& back() const;
    std::size_t size() const;
    bool empty() const;
    void print() const;

    // modification
    void push_front(const T& val);
    void push_front(T&& val);
    void push_back(const T& val);
    void push_back(T&& val);
    T pop_front();
    T pop_back();
    // void insert(iterator it, const T& val);
    // void insert(iterator it, T&& val);
    // void erase(iterator it);
    void clear();
    // emplace soon

private:
    std::shared_ptr<Node<T>> head;
    std::weak_ptr<Node<T>> tail;

    size_t size_;
};


template <typename T>
MyList<T>::MyList()
    : head { nullptr }
    , tail { nullptr }
    , size_ { 0 }
{}

template <typename T>
MyList<T>::MyList(const MyList& other)
    : head { other.head ? std::make_shared<Node<T>>(other.head->val, nullptr, std::weak_ptr<Node<T>> {}) : nullptr }
    , tail { std::weak_ptr<Node<T>> {} }
    , size_ { other.size_ }
{
    std::weak_ptr<Node<T>> curr { other.head };
    std::weak_ptr<Node<T>> prev {};

    while (true) // stops when curr is nullptr
    {
        auto curr_shared { curr.lock() };
        auto prev_shared { prev.lock() };

        if (!curr_shared)
            break;

        if (prev_shared)
            prev_shared->next = std::make_shared<Node<T>>(curr_shared->val, nullptr, prev);

        prev = prev_shared ? prev_shared->next : head;
        curr = curr_shared->next;
    }

    tail = prev;
}

template <typename T>
MyList<T>::MyList(MyList&& other) noexcept
    : head { std::move(other.head) }
    , tail { other.tail }
    , size_ { other.size_ }
{
    other.tail.reset();
    other.size_ = 0;
}

template <typename T>
MyList<T>& MyList<T>::operator=(const MyList& other)
{
    if (this == &other)
        return *this;

    MyList temp { other };
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    std::swap(size_, temp.size_);

    return *this;
}

template <typename T>
MyList<T>& MyList<T>::operator=(MyList&& other) noexcept
{
    if (this == &other)
        return *this;

    MyList temp { std::move(*this) };

    head = std::move(other.head);
    tail = other.tail;
    size_ = other.size_;

    other.tail.reset();
    other.size_ = 0;

    return *this;
}

template <typename T>
MyList<T>::~MyList()
{
    while (head)
        head = head->next;
}

template <typename T>
T& MyList<T>::front() const
{

}

template <typename T>
T& MyList<T>::back() const
{

}

template <typename T>
std::size_t MyList<T>::size() const
{

}

template <typename T>
bool MyList<T>::empty() const
{

}

template <typename T>
void MyList<T>::print() const
{

}

template <typename T>
void MyList<T>::push_front(const T& val)
{

}

template <typename T>
void MyList<T>::push_front(T&& val)
{

}

template <typename T>
void MyList<T>::push_back(const T& val)
{

}

template <typename T>
void MyList<T>::push_back(T&& val)
{

}

template <typename T>
T MyList<T>::pop_front()
{

}

template <typename T>
T MyList<T>::pop_back()
{

}

template <typename T>
void MyList<T>::clear()
{

}

#endif
