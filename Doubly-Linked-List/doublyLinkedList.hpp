#ifndef DOUBLYLINKESLIST_HPP
#define DOUBLYLINKESLIST_HPP

#include <iostream>

template <typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;
    Node(T val) 
        : value{val}
        , prev{nullptr}
        , next{nullptr} {}
};
 
template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& rhs);
    DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
    DoublyLinkedList(DoublyLinkedList&& rhs);
    DoublyLinkedList& operator=(DoublyLinkedList&& rhs);
    ~DoublyLinkedList();

    void push_back(T value);
    void push_front(T value);
    void insert(std::size_t index, T value);
    void remove(std::size_t index);

    int getValue(std::size_t index) const;
    void printList() const;
    void clear();

public:
    void traverse(bool(*fptr)(T val));
    void mergeSort();
    void reverse();

private:
    Node<T>* m_head;
    Node<T>* m_tail;
    std::size_t m_size;

private:
    Node<T>* getMiddle(Node<T>* node) const;
    Node<T>* mergeTwoSortedList(Node<T>* left, Node<T>* right);
    Node<T>* mergeSort(Node<T>* node);
};

#include "doublyLinkedList.impl.cpp"

#endif