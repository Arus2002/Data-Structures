#include "MaxHeap.hpp"

#include <exception>

MaxHeap::MaxHeap(std::size_t size) {
    m_arr.resize(size);
}

MaxHeap::MaxHeap(std::initializer_list<int> list) {
    for (const auto& itr: list) {
        m_arr.push_back(itr);
    }
    buildHeap();
}

void MaxHeap::maxHeapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largestIndex = index;
    int size = m_arr.size();
    
    if (left < size && m_arr[index] < m_arr[left]) {
        largestIndex = left;
    }
    if (right < size && m_arr[largestIndex] < m_arr[right]) {
        largestIndex = right;
    }
    if (largestIndex != index) {
        std::swap(m_arr[largestIndex], m_arr[index]);
        maxHeapify(largestIndex);
    }
}

void MaxHeap::buildHeap() {
    int size = m_arr.size();
    for (int i = (size / 2) - 1; i >= 0; --i) {
        maxHeapify(i);
    }
}

int MaxHeap::getMax() const {
    if (m_arr.size() != 0) {
        return m_arr[0];
    }
    throw std::logic_error("no max element");
}

void MaxHeap::insert(int element) {
    m_arr.push_back(element);
    int size = m_arr.size();
    int parentIndex = size / 2  - 1;
    for (int i = parentIndex; i >= 0; --i) {
        maxHeapify(i);
    }
}

void MaxHeap::extractMax() {
    std::swap(m_arr[0], m_arr[m_arr.size() - 1]);
    m_arr.pop_back();
    maxHeapify(0);
}

void MaxHeap::increaseKey(int elem1, int elem2) {
    if (elem2 <= elem1) {
        throw std::logic_error("your element is less than current element");
    }
    if (m_arr[0] == elem1) {
        m_arr[0] = elem2;
    }
    int parentIndex = 0;
    for (int i = 1; i < m_arr.size(); ++i) {
        if (m_arr[i] == elem1) {
            m_arr[i] = elem2;
            parentIndex = (i - 1) / 2;
        }
    }
    for (int i = parentIndex; i >= 0; --i) {
        maxHeapify(i);
    }
}

void MaxHeap::print() const {
    std::cout << "[ ";
    for (int i = 0; i < m_arr.size(); ++i) {
        std::cout << m_arr[i] << " ";
    }
    std::cout << "]" << std::endl;
}
