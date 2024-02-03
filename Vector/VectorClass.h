#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    Vector();
    explicit  Vector(std::size_t size);
    virtual ~Vector();
    Vector(const Vector& rhs);
    Vector& operator=(const Vector& rhs);
    Vector(Vector&& rhs) noexcept;
    Vector& operator=(Vector&& rhs) noexcept;
    void push_back(const T& elem);
    void push_back(T* arr, std::size_t size);
    void push_back(const T& value, std::size_t count);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    int find(const T& value) const;
    void insert(std::size_t index, const T& elem);
    void insert(std::size_t index, const T& value, std::size_t count);
    void erase(std::size_t index, std::size_t count);
    void erase(std::size_t index);
    void resize(std::size_t size);
    void shrink();

public:
    T& operator[](std::size_t index) const;
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