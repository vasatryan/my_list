#include "double_list.hpp"

template<typename T>
DoubleList<T>::DoubleList() 
    : m_head(nullptr), m_tail(nullptr), m_size(0) {

}

template<typename T>
DoubleList<T>::DoubleList(const DoubleList& other) 
    : m_head(nullptr), m_tail(nullptr), m_size(0) {
    node<T> current = other.m_head;
    while(current) {
        push_back(current->m_data);
        current = current->m_next;  
    }
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& rhs) { 
    if(this != &rhs) {
        clear();
        node<T> current = rhs.m_head;
        while(current) {
            push_back(current->m_data);
            current = current->m_next;  
        }
    }
    return *this;
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList&& other) {
    m_head = std::exchange(other.m_head, nullptr);
    m_tail = std::exchange(other.m_tail, nullptr);
    m_size = std::exchange(other.m_size, 0);
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& rhs) {
    if(this != &rhs) {
        m_head = std::exchange(rhs.m_head, nullptr);
        m_tail = std::exchange(rhs.m_tail, nullptr);
        m_size = std::exchange(rhs.m_size, 0);
    }
    return *this;
}

template<typename T>
DoubleList<T>::~DoubleList() {
    while(m_head) {
        node<T>* current = m_head;
        m_head = m_head->m_next;
        delete current;
    }
    m_size = 0;
}

template<typename T>
void DoubleList<T>::assign(size_t count, const T& value) {
    clear();
    for(size_t i = 0; i < count; ++i) {
        push_back(value);
    }
    m_size = count;
}

template<typename T>
T& DoubleList<T>::front() {
    if(!m_head) {
        throw std::runtime_error("This is empty;");
    }
    return m_head->m_data;
}

template<typename T>
const T& DoubleList<T>::front() const {
    if(!m_head) {
        throw std::runtime_error("This is empty;");
    }
    return m_head->m_data;
}

template<typename T>
T& DoubleList<T>::back() {
    if(!m_head) {
        throw std::runtime_error("This is empty");
    }
    return m_tail->m_data;
}

template<typename T>
const T& DoubleList<T>::back() const {
    if(!m_head) {
        throw std::runtime_error("This is empty");
    }
    return m_tail->m_data;
}

template<typename T>
node<T>* DoubleList<T>::begin() noexcept {
    return m_head;
}

template<typename T>
node<T>* DoubleList<T>::end() noexcept {
    return m_tail;
}

template<typename T>
bool DoubleList<T>::empty() const noexcept {
    return !m_head;
}

template<typename T>
size_t DoubleList<T>::size() const noexcept {
    return m_size;
}

template<typename T>
void DoubleList<T>::clear() noexcept{
    while(m_head) {
        node<T>* current = m_head;
        m_head = m_head->m_next;
        delete current;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template<typename T>
void DoubleList<T>::insert(size_t pos, const T& value) {
    if(pos > m_size) {
        throw std::invalid_argument("Invalid position for insert");
    } else if(pos == 0) {
        push_front(value);
    } else if(pos == m_size) {
        push_back(value);
    } else if(pos > m_size / 2) {
        node<T>* current = m_tail;
        for(int i = m_size; i > pos; --i) {
            current = current->m_prev;
        }
        current->m_prev = new node<T>(value, current->m_prev, current);
    } else {
        node<T>* current = m_head;
        for(int i = 0; i < pos - 1; ++i) {
            current = current->m_next;
        }
        current->m_next = new node<T>(value, current, current->m_next);
    }
    ++m_size;
}

template<typename T>
DoubleList<T>& DoubleList<T>::erase(const node<T>* pos) {
    if(!pos) {
        throw std::invalid_argument("Invalid position for erase:");
    }
    if(pos == m_head) {
        m_head = pos->m_next;
        if(m_head) {
            m_head->m_prev = nullptr;
        }
    } else {
        pos->m_prev->m_next = pos->m_next;
    }
    if(pos == m_tail) {
        m_tail= pos->m_prev;
        if(m_tail) {
            m_tail->m_next = nullptr;
        }
    } else {
        pos->m_next->m_prev = pos->m_prev;
    }  
    delete pos;
    --m_size;
    return *this;
}

template<typename T>
void DoubleList<T>::push_back(const T& value) {
    if(!m_head) {
        m_head = new node(value);
        m_tail = m_head;
    } else {
        m_tail->m_next = new node(value, m_tail);
        m_tail = m_tail->m_next;
    }
    ++m_size;
}

template<typename T>
void DoubleList<T>::push_back(T&& value) {
    if(!m_head) {
        m_head = new node(std::move(value));
        m_tail = m_head;
    } else {
        m_tail->m_next = new node(std::move(value), m_tail);
        m_tail = m_tail->m_next;
    }
    ++m_size;
}

template<typename T> 
void DoubleList<T>::pop_back() {
    if(!m_head) {
        throw std::runtime_error("There is no item in the list");
    }
    if(m_head == m_tail) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        m_tail = m_tail->m_prev;
        delete m_tail->m_next;
        m_tail->m_next = nullptr;
    }
    --m_size;
}

template<typename T>
void DoubleList<T>::push_front(const T& value) {
    if(!m_head) {
        m_head = new node<T>(value);
        m_tail = m_head;
    } else {
        m_head->m_prev = new node<T>(value, nullptr, m_head);
        m_head = m_head->m_prev;
    }
    ++m_size;
}

template<typename T>
void DoubleList<T>::push_front(T&& value) {
    if(!m_head) {
        m_head = new node<T>(std::move(value));
        m_tail = m_head;
    } else {
        m_head->m_prev = new node<T>(std::move(value), nullptr, m_head);
        m_head = m_head->m_prev;
    }
    ++m_size;
}

template<typename T>
void DoubleList<T>::pop_front() {
    if(!m_head) {
        throw std::runtime_error("There is no element in list");
    }
    if(m_head == m_tail) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        m_head = m_head->m_next;
        delete m_head->m_prev;
        m_head->m_prev = nullptr;
    }
    --m_size;
}

template<typename T>
void DoubleList<T>::resize(size_t count) {
    if(count == m_size) {
        return;
    } else if(count < m_size) {
        for(int i = m_size; i > count; --i) {
            pop_back();
        }
    } else if(count > m_size) {
        for(size_t i = m_size; i < count; ++i) {
            push_back(T{});
        }
    }
    m_size = count;
}

template<typename T>
void DoubleList<T>::resize(size_t count, const T& value) {
    if(count == m_size) {
        return;
    } else if(count < m_size) {
        for(int i = m_size; i > count; --i) {
            pop_back();
        }
    } else if(count > m_size) {
        for(size_t i = m_size; i < count; ++i) {
            push_back(value);
        }
    }
    m_size = count;
}

template<typename T> 
void DoubleList<T>::swap(DoubleList& other) noexcept {
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template<typename T>
void DoubleList<T>::merge(DoubleList& other) {
    if(!other.m_head) {
        return;
    } else if(!m_head && other.m_head) {
        m_head = other.m_head;
        m_tail = other.m_tail;
    } else {
        m_tail->m_next = other.m_head;
        m_tail = other.m_tail;
    }
    m_size += other.m_size;
}

template<typename T>
void DoubleList<T>::reverse() noexcept {
    if(!m_head || m_head == m_tail) {
        return;
    }
    node<T>* current_i = m_head;
    node<T>* current_j = m_tail;
    for(int i = 0; i < m_size / 2; ++i) {
        std::swap(current_i->m_next, current_i->m_prev);
        std::swap(current_j->m_next, current_j->m_prev);
        current_i = current_i->m_next;
        current_j = current_j->m_prev;
    }
    std::swap(m_head, m_tail);
}

template<typename T>
size_t DoubleList<T>::unique() {
    size_t count = 0;
    node<T>* current = m_head;
    while(current) {
        node<T>* runner = current;
        while(runner->m_next) {
            if(runner->m_next->m_data == current->m_data) {
                node<T>* tmp = runner->m_next;
                runner->m_next = tmp->m_next;
                if(runner->m_next) {
                    runner->m_next->m_prev = runner;
                }
                if(tmp == m_tail) {
                    m_tail = runner;
                }
                delete tmp;
                ++count;
            } else {
                runner = runner->m_next;
            }
        }
        current = current->m_next;
    }
    m_size -= count;
    return count;
}

template<typename T>
void DoubleList<T>::sort() {
    if (!m_head || m_head == m_tail) {
        return;
    }

    bool isSorted = false;
    node<T>* lastSorted = nullptr;

    while (!isSorted) {
        isSorted = true;
        node<T>* current = m_head;

        while (current->m_next != lastSorted) {
            if (current->m_data > current->m_next->m_data) {
                std::swap(current->m_data, current->m_next->m_data);
                isSorted = false;
            }
            current = current->m_next;
        }

        lastSorted = current;
    }
}





int main() {

    // Creating an empty DoubleList
    DoubleList<int> myList;

    // Testing assign
    myList.assign(5, 42);

    // Testing push_back
    myList.push_back(10);
    myList.push_back(5);
    myList.push_back(30);
    myList.push_back(20);

    // Displaying the original list
    std::cout << "Original List: ";
    for (node<int>* it = myList.begin(); it != nullptr; it = it->m_next) {
        std::cout << it->m_data << " ";
    }
    std::cout << std::endl;

    // Testing sort
    myList.sort();

    // Displaying the sorted list
    std::cout << "Sorted List: ";
    for (node<int>* it = myList.begin(); it != nullptr; it = it->m_next) {
        std::cout << it->m_data << " ";
    }
    std::cout << std::endl;

    // Testing unique
    size_t removedCount = myList.unique();
    std::cout << "Removed " << removedCount << " duplicates." << std::endl;

    // Displaying the unique list
    std::cout << "Unique List: ";
    for (node<int>* it = myList.begin(); it != nullptr; it = it->m_next) {
        std::cout << it->m_data << " ";
    }
    std::cout << std::endl;

    // Testing pop_back
    myList.pop_back();

    // Testing pop_front
    myList.pop_front();

    // Displaying the modified list
    std::cout << "Modified List: ";
    for (node<int>* it = myList.begin(); it != nullptr; it = it->m_next) {
        std::cout << it->m_data << " ";
    }
    std::cout << std::endl;

    // Testing clear
    myList.clear();
    std::cout << "List after clear: ";
    for (node<int>* it = myList.begin(); it != nullptr; it = it->m_next) {
        std::cout << it->m_data << " ";
    }
    std::cout << std::endl;


    return 0;
}