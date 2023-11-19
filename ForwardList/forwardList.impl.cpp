#include "forwardList.hpp"

template <typename T>
ForwardList<T>::ForwardList()
    : m_size{0}
    , m_head{nullptr} {}

template <typename T>
ForwardList<T>::ForwardList(std::size_t size) 
    : m_size{size}
    , m_head{nullptr}
{
    if (size <= 0) {
        return;
    }

    Node<T>* newNode = new Node<T>();
    m_head = newNode;

    Node<T>* curr = m_head;
    for (int i = 1; i < size; ++i) {
        Node<T>* newNode = new Node<T>();
        curr -> next = newNode;
        curr = curr -> next;
    }
    curr -> next = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& rhs) 
    : m_size{rhs.m_size}
    , m_head{nullptr}
{
    if (m_size <= 0) {
        return;
    }
    Node<T>* newNode = new Node<T>;
    newNode -> data = rhs.m_head -> data; 
    m_head = newNode;

    Node<T>* curr = rhs.m_head -> next;
    Node<T>* currForRhs = m_head;
    while (curr != nullptr) {
        Node<T>* newNode = new Node<T>;
        newNode -> data = curr -> data; 
        currForRhs -> next = newNode;
        currForRhs = currForRhs -> next;
        curr = curr -> next;
    }
    currForRhs -> next = nullptr;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        Node<T>* curr;
        while (m_head != nullptr) {
            curr = m_head;
            m_head = m_head -> next;
            delete curr;
        }
        m_head = nullptr;
        m_size = rhs.m_size;

        if (m_size <= 0) {
            return *this;;
        }

        Node<T>* newNode = new Node<T>;
        newNode -> data = rhs.m_head -> data; 
        m_head = newNode;

        Node<T>* currForThis = rhs.m_head -> next;
        Node<T>* currForRhs = m_head;
        while (currForThis != nullptr) {
            Node<T>* newNode = new Node<T>;
            newNode -> data = currForThis -> data; 
            currForRhs -> next = newNode;
            currForRhs = currForRhs -> next;
            currForThis = currForThis -> next;
        }
        currForRhs -> next = nullptr;
    }
    return *this;
}

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& rhs) noexcept
    : m_size{rhs.m_size}
    , m_head{rhs.m_head} 
{
    rhs.m_size = 0;
    rhs.m_head = nullptr;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& rhs) noexcept {
    if (this != &rhs) {
        Node<T>* curr;
        while (m_head != nullptr) {
            curr = m_head;
            m_head = m_head -> next;
            delete curr;
        }

        if (m_size <= 0) {
            return *this;;
        }

        m_head = rhs.m_head;
        m_size = rhs.m_size;
        rhs.m_size = 0;
        rhs.m_head = nullptr;
    }
    return *this;
}

template <typename T>
ForwardList<T>::~ForwardList() {
    Node<T>* curr;
    while (m_head != nullptr) {
        curr = m_head;
        m_head = m_head -> next;
        delete curr;
    }
}

template <typename T>
void ForwardList<T>::insert(std::size_t index, ForwardList& rhs) {
    Node<T>* curr = m_head;
    int i = 0;
    while (i < index - 1) {
        curr = curr -> next;
        ++i;
    }

    Node<T>* tmp = curr -> next;
    curr -> next = rhs.m_head;
    Node<T>* curr2 = rhs.m_head;
    while (curr2 -> next != nullptr) {
        curr2 = curr2 -> next;
    }
    curr2 -> next = tmp;
    rhs.m_head = nullptr;
    tmp = nullptr;
    m_size += rhs.m_size;
}

template <typename T>
void ForwardList<T>::insert(const T& value, std::size_t index) {
    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == m_size - 1) {
        push_back(value);
        return;
    }
    Node<T>* curr = m_head;
    int i = 0;
    while (i < index - 1) {
        curr = curr -> next;
        ++i;
    }
    Node<T>* newNode = new Node<T>();
    newNode -> data = value;
    newNode -> next = curr -> next;
    curr -> next = newNode;
    ++m_size;
}

template <typename T>
void ForwardList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>();
    newNode -> data = value;
    newNode->next = nullptr;

    if (m_head == nullptr) {
        m_head = newNode;
        ++m_size;
        return;
    }
    Node<T>* curr = m_head;
    while (curr -> next != nullptr) {
        curr = curr -> next;
    }
    curr -> next = newNode;
    ++m_size;
}

template <typename T>
void ForwardList<T>::push_front(const T& value) {
    if (m_head == nullptr) {
        push_back(value);
        return;
    }
    Node<T>* newNode = new Node<T>();
    newNode -> data = value;

    Node<T>* curr = m_head;
    m_head = newNode;
    m_head -> next = curr;
    ++m_size;
}

template <typename T>
void ForwardList<T>::pop_back() {
    if (m_head == nullptr) {
        return;
    }
    if (m_head -> next == nullptr) {
        delete m_head;
        m_head = nullptr;
        return;
    }
    Node<T>* curr = m_head;
    while (curr -> next -> next != nullptr) {
        curr = curr -> next;
    }
    delete curr -> next;
    curr -> next = nullptr;
    --m_size;
}

template <typename T>
void ForwardList<T>::pop_front() {
    if (m_head == nullptr) {
        return;
    }
    if (m_head -> next == nullptr) {
        delete m_head;
        m_head = nullptr;
        return;
    }
    if (m_size == 1) {
        pop_back();
    }
    Node<T>* curr = m_head;
    m_head = m_head -> next;
    delete curr;
    curr = nullptr;
    --m_size;
}

template <typename T>
void ForwardList<T>::erase(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("out of range!");
    }
    if (index == 0) {
        pop_front();
        return;
    }
    if (index == m_size - 1) {
        pop_back();
        return;
    }

    Node<T>* curr = m_head;
    int i = 0;
    while (i < index - 1) {
        curr = curr -> next;
        ++i;
    }
    Node<T>* tmp = curr -> next;
    curr -> next = curr -> next -> next;
    delete tmp;
    --m_size;
}

template <typename T>
int ForwardList<T>::find(const T& value) const {
    Node<T>* curr = m_head;
    std::size_t index = -1;
    while (curr != nullptr) {
        ++index;
        if (curr -> data == value) {
            return index;
        }
        curr = curr -> next;
    }
    return -1;
}

template <typename T>
std::size_t ForwardList<T>::size() const {
    return m_size;
}

template <typename T>
std::size_t ForwardList<T>::empty() const {
    return m_size == 0;
}

template <typename T>
T& ForwardList<T>::operator[](std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("out of range!");
    }
    Node<T>* curr = m_head;
    for (int i = 0; i < index; ++i) {
        curr = curr -> next;
    }
    return curr -> data;
}