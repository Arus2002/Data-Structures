#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <iostream>
#include <vector>
#include <initializer_list>

class MaxHeap {
public:
    MaxHeap() = default;
    MaxHeap(std::size_t size);
    MaxHeap(std::initializer_list<int> list);
    void insert(int element);
    int getMax() const;
    void extractMax();
    void increaseKey(int elem1, int elem2);
    void print() const;

private: 
    void buildHeap();
    void maxHeapify(int index);
private:
    std::vector<int> m_arr;
};

#endif