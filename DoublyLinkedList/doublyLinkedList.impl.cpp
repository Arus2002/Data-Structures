#include "doublyLinkedList.hpp"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() 
    : m_size(0)
    , m_head{nullptr}
    , m_tail{nullptr} {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& rhs) 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_size{rhs.m_size} 
{
    if (m_size <= 0) {
        return;
    }

    std::shared_ptr<Node<T>> currForRhs = rhs.m_head;
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
    newNode -> value = currForRhs -> value;
    m_head = newNode;
    m_head -> prev = nullptr;
    currForRhs = currForRhs -> next;

    std::shared_ptr<Node<T>> currForThis = m_head;
    for (int i = 1; i < m_size; ++i) {
        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
        newNode -> value = currForRhs -> value;

        currForThis -> next = newNode;
        newNode -> prev = currForThis;

        currForThis = currForThis -> next;
        currForRhs = currForRhs -> next;
    }

    m_tail = currForThis;
    m_tail -> next = nullptr;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs) {

    if (this == &rhs) {
        return *this;
    }

    clear();
    m_size = rhs.m_size;

    if (m_size > 0) {
        std::shared_ptr<Node<T>> currForRhs = rhs.m_head;
        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
        newNode -> value = currForRhs -> value;
        m_head = newNode;
        m_head -> prev = nullptr;
        currForRhs = currForRhs -> next;

        std::shared_ptr<Node<T>> currForThis = m_head;

        for (int i = 1; i < m_size; ++i) {
            std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
            newNode -> value = currForRhs -> value;

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
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& rhs) {
    if (this == &rhs) {
        return *this;
    }
    clear();
    m_size = rhs.m_size;
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;

    rhs.m_size = 0;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;

    return *this;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    std::shared_ptr<Node<T>> curr = m_head;
    while (curr != nullptr) {
        std::shared_ptr<Node<T>> currNext = curr -> next;
        curr -> prev.reset();
        curr -> next.reset();
        curr.reset();
        curr = currNext;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}



template <typename T>
void DoublyLinkedList<T>::push_back(T value) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
    newNode -> value = value;
    if (m_head == nullptr) {
        m_head = m_tail = newNode;
    }
    newNode -> prev = m_tail;
    m_tail -> next = newNode;
    newNode -> next = nullptr;
    m_tail = newNode;
    ++m_size;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T value) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
    newNode -> value = value;
    if (m_head == nullptr) {
        push_back(value);
    }
    newNode -> next = m_head;
    m_head -> prev = newNode;
    newNode -> prev = nullptr;
    m_head = newNode;
    ++m_size;
}

template <typename T>
void DoublyLinkedList<T>::insert(std::size_t index, T value) {
    if (index >= m_size || index < 0) {
        throw std::out_of_range("out of range!");
    }
    if ((m_head == nullptr && index == 0) || index == 0) {
        push_front(value);
        return;
    }

    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>();
    newNode -> value = value;
    
    std::shared_ptr<Node<T>> tmp = m_head;
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
        throw std::out_of_range("out of range!");
    }

    std::shared_ptr<Node<T>> tmp = std::make_shared<Node<T>>();
    std::size_t counter = index;
    while (counter != 0) {
        tmp = tmp -> next;
        --counter;
    }
    if (index == m_size - 1) {
        m_tail = tmp -> prev;
        if (m_tail) {
            m_tail -> next = nullptr;
        } else {
            m_head = nullptr; 
        }
    }
    else if (index == 0) {
        m_head = tmp -> next;
        if (m_head) {
            m_head -> prev = nullptr;
        } else {
            m_tail = nullptr;
        }
    }
    else {
        tmp -> prev -> next = tmp -> next;
        tmp -> next -> prev = tmp -> prev;
    }

    tmp -> prev = nullptr;
    tmp -> next = nullptr;
    --m_size;
}

template <typename T>
T DoublyLinkedList<T>::getValue(std::size_t index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("out of range!");
    }

    std::shared_ptr<Node<T>> tmp = m_head;
    std::size_t counter = index;
    while (counter != 0) {
        tmp = tmp -> next;
        --counter;
    }
    return tmp -> value;
}

template <typename T>
void DoublyLinkedList<T>::printList() const{
    Iterator it = begin();
    Iterator endIt = end();
    while (it != endIt) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const {
    return Iterator(m_head);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const {
    return Iterator(nullptr);
}

