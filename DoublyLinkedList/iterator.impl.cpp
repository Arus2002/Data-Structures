#include "doublyLinkedList.hpp"

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator() = default;

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(std::shared_ptr<Node<T>> start)
    : m_ptr{start} {}

template <typename T>
DoublyLinkedList<T>::Iterator::~Iterator() = default;

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(const DoublyLinkedList<T>::Iterator& rhs) 
    : m_ptr{rhs.m_ptr} {}

template <typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator=(const DoublyLinkedList<T>::Iterator& rhs) {
    if (this != &rhs) {
        m_ptr = rhs.m_ptr;
    }
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator::reference_type DoublyLinkedList<T>::Iterator::operator*() {
    return m_ptr -> value;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator::pointer_type DoublyLinkedList<T>::Iterator::operator->() {
    return &(m_ptr -> value);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    m_ptr = m_ptr -> next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    DoublyLinkedList<T>::Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() {
    m_ptr = m_ptr -> prev;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    DoublyLinkedList<T>::Iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const DoublyLinkedList<T>::Iterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const DoublyLinkedList<T>::Iterator& other) const {
    return !(*this == other);
}
