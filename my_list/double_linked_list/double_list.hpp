#include "node.hpp"
#include <stdexcept>
#include <iostream>
#include <utility>

template<typename T>
class DoubleList {
private:
    node<T>* m_head;
    node<T>* m_tail;
    size_t m_size;
public:
    DoubleList();
    DoubleList(const DoubleList& other);
    DoubleList& operator=(const DoubleList& rhs);
    DoubleList(DoubleList&& other);
    DoubleList& operator=(DoubleList&& rhs);
    ~DoubleList();
public:
    void assign(size_t count, const T& value);
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    node<T>* begin() noexcept;
    node<T>* end() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    void insert(size_t pos, const T& value);
    DoubleList<T>& erase(const node<T>* pos);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void push_front(const T& value) ;
    void push_front(T&& value);
    void pop_front();
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void swap(DoubleList& other) noexcept;
    void merge(DoubleList& other);
    void reverse() noexcept;
    size_t unique();
    void sort();
};