#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <memory>
#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    std::shared_ptr<Node<T>> next;
    std::shared_ptr<Node<T>> prev;
    T value;
    Node()
        : next{nullptr}
        , prev{nullptr}
        , value() {}
};

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& rhs);
    DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
    DoublyLinkedList(DoublyLinkedList&& rhs);
    DoublyLinkedList& operator=(DoublyLinkedList&& rhs);
    void push_back(T value);
    void push_front(T value);
    void insert(std::size_t index, T value);
    void remove(std::size_t index);
    T getValue(std::size_t index) const;
    void printList() const;
    void clear();

public:
    class Iterator {
    public:
        using reference_type = T&;
        using pointer_type = T*;
        using value_type = T;

        Iterator();
        Iterator(std::shared_ptr<Node<T>> start);
        ~Iterator();
        Iterator(const Iterator& rhs);
        Iterator& operator=(const Iterator& rhs);
        reference_type operator*();
        pointer_type operator->();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        std::shared_ptr<Node<T>> m_ptr;
        friend class DoublyLinkedList;
    };

public:
    Iterator begin() const;
    Iterator end()const ;
    
private:
    std::shared_ptr<Node<T>> m_head;
    std::shared_ptr<Node<T>> m_tail;
    std::size_t m_size;
};

#include "doublyLinkedList.impl.cpp"
#include "iterator.impl.cpp"

#endif
