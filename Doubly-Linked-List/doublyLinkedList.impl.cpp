#include "doublyLinkedList.hpp"

#include <iostream>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() 
    : m_size(0)
    , m_head{nullptr}
    , m_tail{nullptr} {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& rhs) 
    : m_size{rhs.m_size} 
    , m_head{rhs.m_head}
    , m_tail{rhs.m_tail} 

{
    if (m_size > 0) {
        Node<T>* currForRhs = rhs.m_head;
        Node<T>* currForThis = m_head;
        Node<T>* newNode = new Node<T>(currForRhs -> value);
        currForThis = newNode;
        newNode -> prev = currForThis;

        while (currForRhs != nullptr) {
            Node<T>* newNode = new Node<T>(currForRhs -> value);
            currForThis -> next = newNode;
            newNode -> prev = currForThis;
            currForThis = currForThis -> next;
            currForRhs = currForRhs -> next;
        }

        m_tail = currForThis;
        m_tail -> next = nullptr;
    }
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    if (rhs.m_size > 0) {
        clear();
        m_size = rhs.m_size;
        Node<T>* currForRhs = rhs.m_head;
        Node<T>* newNode = new Node<T>(currForRhs -> value);
        m_head = newNode;
        Node<T>* currForThis = m_head;
        newNode -> prev = currForThis;

        while (currForRhs -> next != nullptr) {
            Node<T>* newNode = new Node<T>(currForRhs -> value);
            currForThis -> next = newNode;
            newNode -> prev = currForThis;
            currForThis = currForThis -> next;
            currForRhs = currForRhs -> next;
        }

        m_tail = currForThis;
        m_tail -> next = nullptr;
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& rhs)
    : m_size{rhs.m_size}
    , m_head{rhs.m_head}
    , m_tail{rhs.m_tail} 
{
    rhs.m_size = 0;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& rhs) { //?
    if (this == &rhs) {
        return *this;
    }

    if (m_size > 0) {
        clear();
    }

    m_size = rhs.m_size;
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    
    rhs.m_size = 0;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;

    return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* tmp = m_head;
    while (tmp != nullptr) {
        Node<T>* tmp2 = tmp;
        tmp = tmp->next;
        delete tmp2;
    }
}

template <typename T>
void DoublyLinkedList<T>::push_back(T value) {
    ++m_size;
    Node<T>* newNode = new Node<T>(value);
    if (m_head == nullptr) {
        m_head = m_tail = newNode;
    }
    newNode -> prev = m_tail;
    m_tail -> next = newNode;
    newNode -> next = nullptr;
    m_tail = newNode;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T value) {
    ++m_size;
    Node<T>* newNode = new Node<T>(value);
    if (m_head == nullptr) {
        m_head = m_tail = newNode;
    }
    newNode -> next = m_head;
    m_head -> prev = newNode;
    newNode -> prev = nullptr;
    m_head = newNode;
}

template <typename T>
void DoublyLinkedList<T>::insert(std::size_t index, T value) {
    if (index >= m_size || index < 0) {
        std::cout << "Out of range!" << std::endl;
        return;
    }
    if ((m_head == nullptr && index == 0) || index == 0) {
        push_front(value);
        return;
    }

    Node<T>* newNode = new Node<T>(value);
    
    Node<T>* tmp = m_head;
    while (index != 0) {
        tmp = tmp -> next;
        --index;
    }

    newNode -> prev = tmp -> prev;
    tmp -> prev -> next = newNode;
    newNode -> next = tmp;
    tmp -> prev = newNode;

    ++m_size;
}

template <typename T>
void DoublyLinkedList<T>::remove(std::size_t index) {
    if (index >= m_size || index < 0 || m_size == 0) {
        std::cout << "Out of range!" << std::endl;
        return;
    }

    Node<T>* tmp = m_head;
    int counter = index;
    while (counter != 0) {
        tmp = tmp -> next;
        --counter;
    }
    if (index == m_size - 1) {
        m_tail = tmp -> prev;
        m_tail -> next = nullptr;
    }
    else if (index == 0) {
        m_head = tmp -> next;
        m_head -> prev = nullptr;
    }
    else {
        tmp -> prev -> next = tmp -> next;
        tmp -> next -> prev = tmp -> prev;
    }

    tmp -> prev = nullptr;
    tmp -> next = nullptr;
    delete tmp;
    --m_size;
}

template <typename T>
int DoublyLinkedList<T>::getValue(std::size_t index) const {
    if (index < 0 || index >= m_size) {
        std::cout << "Out of range!" << std::endl;
        return -1;
    }

    Node<T>* tmp = m_head;
    std::size_t counter = index;
    while (counter != 0) {
        tmp = tmp -> next;
        --counter;
    }
    return tmp -> value;
}

template <typename T>
void DoublyLinkedList<T>::printList() const{
    Node<T>* tmp = m_head;
    while (tmp != nullptr) {
        std::cout << tmp -> value << " ";
        tmp = tmp -> next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::traverse(bool(*fptr)(T val)) {
    Node<T>* tmp = m_head;
    while (tmp != nullptr) {
        if (fptr(tmp -> value)) {
            std::cout << tmp -> value << " ";
        }
        tmp = tmp -> next;
    }
}

template <typename T>
void DoublyLinkedList<T>::mergeSort() {
    if (m_size > 1) {
        m_head = mergeSort(m_head);

        Node<T>* newTail = m_head;
        while (newTail -> next != nullptr) {
            newTail = newTail -> next;
        }
        m_tail = newTail;
    }
}

template <typename T>
Node<T>* DoublyLinkedList<T>::mergeSort(Node<T>* node) {
    if (node == nullptr || node -> next == nullptr) {
        return node;
    }

    Node<T>* middle = getMiddle(node);
    Node<T>* nextOfMiddle = middle -> next;

    middle -> next = nullptr;
    nextOfMiddle -> prev = nullptr;

    Node<T>* left = mergeSort(node);
    Node<T>* right = mergeSort(nextOfMiddle);

    return mergeTwoSortedList(left, right);
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getMiddle(Node<T>* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    Node<T>* slow = node;
    Node<T>* fast = node -> next;

    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next;
    }

    return slow;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::mergeTwoSortedList(Node<T>* left, Node<T>* right) {
    Node<T>* dummy = new Node<T>(T{}); 
    Node<T>* current = dummy;

    while (left != nullptr && right != nullptr) {
        if (left -> value <= right -> value) {
            current -> next = left;
            left -> prev = current;
            left = left -> next;
        } else {
            current -> next = right;
            right -> prev = current;
            right = right -> next;
        }
        current = current -> next;
    }

    if (left != nullptr) {
        current -> next = left;
        left -> prev = current;
    } else {
        current -> next = right;
        right -> prev = current;
    }

    Node<T>* mergedList = dummy -> next;
    if (mergedList != nullptr) {
        mergedList -> prev = nullptr;
    }

    delete dummy;
    return mergedList;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
    Node<T>* curr = m_head;
    while (curr != nullptr) {
        Node<T>* tmp = curr -> next;
        curr -> next = curr -> prev;
        curr -> prev = tmp;
        curr = curr -> prev;
    }
    std::swap(m_head, m_tail);
}