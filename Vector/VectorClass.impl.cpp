#include "VectorClass.h"

template <typename T>
Vector<T>::Vector() 
    : m_capacity{0}
    , m_size{0}
    , m_arr{nullptr} {}

template <typename T>
Vector<T>::Vector(std::size_t size)
    : m_capacity{size}
    , m_size{0}
    , m_arr{new T[m_capacity]} {}

template <typename T>
Vector<T>::Vector(const Vector& rhs) 
    : m_capacity{rhs.m_capacity}
    , m_size{rhs.m_size} 
{
    m_arr = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = rhs.m_arr[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete[] m_arr;

    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;
    m_arr = new T[m_capacity];

    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = rhs.m_arr[i];
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& rhs) noexcept {
    moveFrom(rhs);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    cleanup();
    moveFrom(rhs);

    return *this;
}

template <typename T>
Vector<T>::~Vector() { 
    delete[] m_arr; 
}

template <typename T>
void Vector<T>::push_back(T* arr, std::size_t size) {
    for (int i = 0; i < size; ++i) {
        push_back(arr[i]);
    }
}

template <typename T>
void Vector<T>::push_back(const T& value, std::size_t count) {
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}

template <typename T>
void Vector<T>::push_back(const T& elem) {
    if (m_size == m_capacity) {
        realloc();
    }
    m_arr[m_size] = elem;
    ++m_size;
}

template <typename T>
void Vector<T>::push_front(const T& value) {
    if (m_size == 0) {
        push_back(value);
        return;
    }
    if (m_size == m_capacity) {
        realloc();
    }

    for (int i = m_size; i > 0; --i) {
        m_arr[i] = m_arr[i - 1];
    }
    m_arr[0] = value;
    ++m_size;
}

template <typename T>
void Vector<T>::pop_back() {
    if (m_size < 0) {
        return;
    }
    --m_size;
}

template <typename T>
void Vector<T>::pop_front() {
    erase(0);
}

template <typename T>
int Vector<T>::find(const T& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_arr[i] == value) {
            return i;
        }
    }
    return -1;
} 

template <typename T>
void Vector<T>::insert(std::size_t index, const T& elem) {
    if (index < 0 && index >= m_size) {
        std::cout << "Out of ranges" << std::endl;
        return;
    }
    if (index == m_size - 1) {
        push_back(elem);
        return;
    }
    if (index == 0) {
        push_front(elem);
        return;
    }
    realloc();
    for (int i = m_size - 1; i >= index; --i) {
        m_arr[i + 1] = m_arr[i];
    }
    m_arr[index] = elem;
    ++m_size;
}

template <typename T>
void Vector<T>::insert(std::size_t index, const T& value, std::size_t count) {
    for (int i = 0; i < count; ++i) {
        insert(index, value);
        index++;
    }
}

template <typename T>
void Vector<T>::erase(std::size_t index) {
    if (index >= m_size || index < 0) {
        throw std::out_of_range("out of range !");
    }
    if (index == m_size - 1) {
        pop_back();
        return;
    }

    for (int i = index; i < m_size - 1; ++i) {
        m_arr[i] = m_arr[i + 1];
    }
    --m_size;
}

template <typename T>
void Vector<T>::erase(std::size_t index, std::size_t count) {
    if (count - index < 0) {
        throw std::out_of_range("out of range!");
    }
    for (int i = 0; i < count; ++i) {
        erase(index);
    }
}


template <typename T>
void Vector<T>::resize(std::size_t size) {
    if (size == m_capacity) {
        return;
    }

    if (size < m_capacity) {
        T* tmp = m_arr;
        for (int i = 0; i < size; ++i) {
            ++tmp;
        }
        if (m_capacity - size == 1) {
            delete tmp;
        }
        else {
            delete[] tmp;
        }
    }
    else if (size > m_capacity) {
        if (m_capacity == 0) {
            m_capacity = 1;
        }
        m_capacity = size;
        T* tmp = new T[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp;
        tmp = nullptr;
    }
    m_size = size;
    m_capacity = size;
}

template <typename T>
void Vector<T>::shrink() {
    resize(m_size);
}

template <typename T>
T& Vector<T>::operator[](std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Out of bound!");
    }
    return m_arr[index];
}

template <typename T>
std::size_t Vector<T>::size() const {
    return m_size;
}

template <typename T>
void Vector<T>::clear() {
    for (int i = 0; i < m_size; ++i) {
        m_arr[i].~T();
    }
    m_size = 0;
}

template <typename T>
void Vector<T>::realloc() {
    if (m_capacity == 0) {
        m_capacity = 1;
    }
    m_capacity *= 2;
    T* tmp = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        tmp[i] = std::move(m_arr[i]);
    }
    delete[] m_arr;
    m_arr = tmp;
    tmp = nullptr;
}

template <typename T>
void Vector<T>::moveFrom(Vector& rhs) noexcept {
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_arr = rhs.m_arr;

    rhs.m_arr = nullptr;
    rhs.m_capacity = 0;
    rhs.m_size = 0;
}

template <typename T>
void Vector<T>::cleanup() noexcept {
    delete[] m_arr;
}