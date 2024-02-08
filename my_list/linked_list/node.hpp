#ifndef NODE
#define NODE

template<typename T>
struct node {
    node(const T& data = {}, node* next = nullptr) : m_data(data), m_next(next) {

    } 
    T m_data;
    node* m_next;
};

#endif //Node
