#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    Vector();
    explicit  Vector(int size);
    Vector(const Vector& rhs);
    ~Vector();
    Vector& operator=(const Vector& rhs);
    Vector(Vector&& rhs) noexcept;
    Vector& operator=(Vector&& rhs) noexcept;
    void push_back(const T& elem);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    int find(const T& value) const;
    T& operator[](std::size_t index) const;
    void insert(std::size_t index, const T& elem);
    void erase(std::size_t index);
    void resize(std::size_t size);
    void shrink();
    std::size_t size() const;
    void clear();

private:
    std::size_t m_capacity;
    std::size_t m_size;
    T* m_arr;

private:
    void realloc();
    void moveFrom(Vector& rhs) noexcept;
    void cleanup() noexcept;
};

#include "VectorClass.impl.cpp"

#endif