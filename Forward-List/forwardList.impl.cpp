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

template <typename T>
Node<T>* ForwardList<T>::getHead() const {
    return m_head;
}

template <typename T>
Node<T>* ForwardList<T>::reverseRec(Node<T>* head) {
    if (head == nullptr || head -> next == nullptr) {
        return head;
    }
    Node<T>* tmp = reverseRec(head -> next);
    head -> next -> next = head;
    head -> next = nullptr;
    return tmp;
}

template <typename T>
Node<T>* ForwardList<T>::reverseRec() {
    m_head = reverseRec(m_head);
    return m_head;
}

template <typename T>
void ForwardList<T>::reverseIter() {
    Node<T>* prev = nullptr;
    Node<T>* curr = m_head;
    Node<T>* next = nullptr;

    while (curr != nullptr) {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

template <typename T>
bool ForwardList<T>::hasCycle() const {
    if (m_head == nullptr) {
        return false;
    }
    Node<T>* slow = m_head;
    Node<T>* fast = m_head;
    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

template <typename T>
Node<T>* ForwardList<T>::getMiddleNode() const {
    if (m_head == nullptr) {
        return nullptr;
    }
    Node<T>* slow = m_head;
    Node<T>* fast = m_head -> next;;
    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}

template <typename T>
Node<T>* ForwardList<T>::merge_two_lists(Node<T>* head_1, Node<T>* head_2) {
    Node<T> dummy;
    Node<T>* curr = &dummy;

    while (head_1 != nullptr && head_2 != nullptr) {
        if (head_1 -> data < head_2 -> data) {
            curr -> next = head_1;
            head_1 = head_1 -> next;
        } 
        else {
            curr -> next = head_2;
            head_2 = head_2 -> next;
        }
        curr = curr -> next;
    }

    if (head_1 != nullptr) {
        curr -> next = head_1;
    }
    else if (head_2 != nullptr) {
        curr -> next = head_2;
    }

    return dummy.next;
}

template <typename T>
void ForwardList<T>::merge(ForwardList<T>& other) {
    m_head = merge_two_lists(m_head, other.m_head); 
}

template <typename T>
Node<T>* ForwardList<T>::sort_lists(Node<T>* head) {
    if (!head || !head -> next) {
        return head;
    }
    Node<T>* slow = head;
    Node<T>* fast = head -> next;
    while (fast && fast -> next) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    fast = slow -> next;
    slow -> next = nullptr;
    Node<T>* left = sort_lists(head);
    Node<T>* right = sort_lists(fast);
    return merge_two_lists(left, right);
}

template <typename T>
void ForwardList<T>::sort() {
    m_head = sort_lists(m_head);
}

template <typename T>
Node<T>* ForwardList<T>::getCyclStartPoint() const {
    if (!hasCycle()) {
        return nullptr;
    }

    Node<T>* slow = m_head;
    Node<T>* fast = m_head;
    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
        if (slow == fast) {
            break;
        }
    }

    fast = m_head;
    

}

