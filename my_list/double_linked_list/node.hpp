#ifndef DOUBLELIST
#define DOUBLELIST

template<typename T>
struct node {
    node(const T& value = {}, node* prev = nullptr, node* next  = nullptr)
        : m_data(value), m_prev(prev), m_next(next) 
    {
    }
    node* m_prev;
    node* m_next;
    T m_data;
};

#endif //DOUBLELIST