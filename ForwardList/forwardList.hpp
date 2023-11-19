#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    Node* next;
    T data;
};

template <typename T>
class ForwardList {
public:
    ForwardList(std::size_t size);
    ForwardList();
    ForwardList(const ForwardList& rhs);
    ForwardList& operator=(const ForwardList& rhs);
    ForwardList(ForwardList&& rhs) noexcept;
    ForwardList& operator=(ForwardList&& rhs) noexcept;
    void insert(const T& value, std::size_t index);
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    std::size_t size() const;
    std::size_t empty() const;
    int find(const T& value) const;
    T& operator[] (std::size_t index) const;
    void erase(std::size_t index);
    ~ForwardList();

private:
    Node<T>* m_head;
    std::size_t m_size;
};

#include "forwardList.impl.cpp"

#endif