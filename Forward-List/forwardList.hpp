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
    ForwardList();
    explicit ForwardList(std::size_t size);
    ForwardList(const ForwardList& rhs);
    ForwardList& operator=(const ForwardList& rhs);
    ForwardList(ForwardList&& rhs) noexcept;
    ForwardList& operator=(ForwardList&& rhs) noexcept;
    virtual ~ForwardList();
    void insert(std::size_t index, ForwardList& rhs);
    void insert(const T& value, std::size_t index);
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void erase(std::size_t index);
    int find(const T& value) const;
    std::size_t size() const;
    std::size_t empty() const;
    T& operator[] (std::size_t index) const;

public:
    Node<T>* getMiddleNode() const;
    Node<T>* getHead() const;
    Node<T>* getCyclStartPoint() const;

public:
    void sort();
    Node<T>* reverseRec();
    void reverseIter();
    bool hasCycle() const;

private:
    Node<T>* merge_two_lists(Node<T>* list1, Node<T>* list2);
    void merge(ForwardList<T>& other);
    Node<T>* sort_lists(Node<T>* head);
    Node<T>* reverseRec(Node<T>* head);

private:
    Node<T>* m_head;
    std::size_t m_size;
};

#include "forwardList.impl.cpp"

#endif