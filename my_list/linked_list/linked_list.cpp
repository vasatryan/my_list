#include "linked_list.hpp"

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const LinkedList<T>& src) {
//     for (node<T>* current = src.begin(); current != src.end(); current = current->m_next) {
//         os << current->m_data << " ";
//     }
//     return os;
// }

template<typename T>
LinkedList<T>::LinkedList() : m_head(nullptr), m_size(0) {

}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : m_head(nullptr), m_size(0) {
    node<T>* ptr = other.m_head;
    while (ptr != nullptr) {
        push_back(ptr->m_data);
        ptr = ptr->m_next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) {
    if(this != &rhs) {
        clear();
        node<T>* ptr = rhs.m_head;
        while (ptr != nullptr) {
            push_back(ptr->m_data);
            ptr = ptr->m_next;
        }
        m_size = rhs.m_size;
    }
    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other) {
    m_head = std::exchange(other.m_head, nullptr);
    m_size = std::exchange(other.m_size, 0);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& rhs) {
    if(this != &rhs) {
        m_head = std::exchange(rhs.m_head, nullptr);
        m_size = std::exchange(rhs.m_size, 0);
    } 
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while(m_head) {
        node<T>* current = m_head;
        m_head = m_head->m_next;
        delete current;
    }
    m_size = 0;
}

template<typename T>
void LinkedList<T>::assign(size_t count, const T& value) {
    clear();
    for(size_t i = 0; i < count; ++i) {
        push_back(value);
    }
    m_size = count;
}

template<typename T>
T& LinkedList<T>::front() {
    if(!m_head) {
        throw std::runtime_error("This is empty;");
    }
    return m_head->m_data;
}

template<typename T>
const T& LinkedList<T>::front() const {
    if(!m_head) {
        throw std::runtime_error("This is empty;");
    }
    return m_head->m_data;
}

template<typename T>
T& LinkedList<T>::back() {
    if (!m_head) {
        throw std::runtime_error("This is empty;");
    }
    node<T>* current = m_head;
    while (current->m_next) {
        current = current->m_next;
    }
    return current->m_data;
}

template<typename T>
const T& LinkedList<T>::back() const {
    if (!m_head) {
        throw std::runtime_error("This is empty;");
    }
    node<T>* current = m_head;
    while (current->m_next) {
        current = current->m_next;
    }
    return current->m_data;
}

template<typename T>
node<T>* LinkedList<T>::begin() noexcept {
    return m_head;
}

template<typename T>
node<T>* LinkedList<T>::end() noexcept {
    if(!m_head) {
        return nullptr;
    }
    node<T>* current = m_head;
    while (current->m_next) {
        current = current->m_next;
    }
    return current;
}

template<typename T>
bool LinkedList<T>::empty() const noexcept {
    return !m_head;
}

template<typename T>
size_t LinkedList<T>::size() const noexcept {
    return m_size;
}

template<typename T>
void LinkedList<T>::clear() noexcept {
    while (m_head) {
        node<T>* current = m_head;
        m_head = m_head->m_next;
        delete current;
    }
    m_head = nullptr;
    m_size = 0;
}

template<typename T>
void LinkedList<T>::insert(size_t pos, const T& value) {
    if(pos > m_size) {
        throw std::out_of_range("Invalid position");
    }
    if(pos == 0) {
        push_front(value);
    } else {
        node<T>* current = m_head;
        for(size_t i = 0; i < pos - 1; ++i) {
            current = current->m_next;
        }
    current->m_next = new node<T>(value, current->m_next);
    }
   
    ++m_size;
}

template<typename T>
LinkedList<T>& LinkedList<T>::erase(const node<T>* pos) {
    if (!pos) {
        throw std::invalid_argument("Invalid position");
    }
    node<T>* current = m_head;
    while(current && current->m_next != pos) {
        current = current->m_next;
    }
    if(!current) {
        throw std::invalid_argument("Invalid position");
    }
    current->m_next = pos->m_next;
    delete pos;
    --m_size;
    return *this;
}

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    if(!m_head) {
        m_head = new node<T>(value);
    } else {    
        node<T>* current = m_head;
        while(current->m_next) {
            current = current->m_next;
        }
        current->m_next = new node<T>(value);
    }
    ++m_size;
}

template<typename T>
void LinkedList<T>::push_back(T&& value) {
    if(!m_head) {
        m_head = new node<T>(std::move(value));
    } else {
        node<T>* current = m_head;
        while(current->m_next) {
            current = current->m_next;
        }
        current->m_next = new node<T>(std::move(value));
    }
    ++m_size;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if(!m_head) {
        throw std::runtime_error("There is no item in the list");
    }
    if(m_head->m_next = nullptr) {
        delete m_head;
        m_head = nullptr;
        --m_size;
        return;
    }
    node<T>* current = m_head;
    node<T>* prev = nullptr;
    while(current->m_next) {
        prev = current;
        current = current->m_next;
    }
    delete current;
    current = nullptr;
    if(prev) {
        prev->m_next = nullptr;
    } else {
        m_head = nullptr;
    }
    --m_size;
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    m_head = new node<T>(value, m_head);
    ++m_size;
}

template<typename T>
void LinkedList<T>::push_front(T&& value) {
    m_head = new node<T>(std::move(value), m_head);
    ++m_size;
}

template<typename T>
void LinkedList<T>::pop_front() {
    node<T>* tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    --m_size;
}

template<typename T>
void LinkedList<T>::resize(size_t count) {
    if(count == m_size) {
        return;
    } else if(count < m_size) {
        for(size_t i = m_size; i > count; --i) {
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
void LinkedList<T>::resize(size_t count, const T& value) {
    if(count == m_size) {
        return;
    } else if(count < m_size) {
        for(size_t i = m_size; i > count; --i) {
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
void LinkedList<T>::swap(LinkedList& other) noexcept {
    std::swap(m_head, other.m_head);
    std::swap(m_size, other.m_size);
}

template<typename T>
void LinkedList<T>::merge(LinkedList& other) {
    if (!m_head || !other.m_head) {
        return;
    }
    node<T>* current = m_head;
    while(current->m_next) {
        current = current->m_next;
    }
    current->m_next = other.m_head;
    m_size += other.m_size;
}

template<typename T>
void LinkedList<T>::reverse() noexcept {
    if(!m_head) {
        return;
    }
    node<T>* current = m_head;
    node<T>* prev = nullptr;
    node<T>* next = nullptr;
    while(current) {
        next = current->m_next;
        current->m_next = prev;
        prev = current;
        current = next;
    }
    m_head = prev;
}

template<typename T>
size_t LinkedList<T>::unique() {
    node<T>* current = m_head;
    size_t count = 0;
    while(current) {
        node<T>* runner = current;
        while(runner->m_next) {
            if(runner->m_next->m_data == current->m_data) {
                node<T>* dup = runner->m_next;
                runner->m_next = runner->m_next->m_next;
                ++count;
                delete dup;
            } else {
                runner = runner->m_next;
            }
        }
        current = current->m_next;
    }
    return count;
}

template<typename T>
void LinkedList<T>::sort() {
    node<T>* current_i = m_head;
    while(current_i != nullptr) {
        node<T>* current_j = current_i->m_next;
        while(current_j != nullptr) {
            if(current_j->m_data < current_i->m_data) {
                T tmp = current_j->m_data;
                current_j->m_data = current_i->m_data;
                current_i->m_data = tmp;
            }
            current_j = current_j->m_next;
        }
        current_i = current_i->m_next;
    }
}


int main() {
    // Create an empty LinkedList of integers
    LinkedList<int> myList;

    // Check if the list is empty
    if (myList.empty()) {
        std::cout << "The list is empty." << std::endl;
    } else {
        std::cout << "The list is not empty." << std::endl;
    }

    // Add elements to the list
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // Display the elements in the list
    std::cout << "Elements in the list: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Access front and back elements
    std::cout << "Front element: " << myList.front() << std::endl;
    std::cout << "Back element: " << myList.back() << std::endl;

    // Add more elements using push_front
    myList.push_front(5);
    myList.push_front(15);

    // Display the updated list
    std::cout << "Updated elements in the list: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Remove the first element
    myList.pop_front();

    // Display the list after popping front
    std::cout << "Elements after pop_front: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Insert an element at position 1
    myList.insert(1, 25);

    // Display the list after inserting
    std::cout << "Elements after inserting at position 1: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Erase an element at position 1
    myList.erase(myList.begin()->m_next);

    // Display the list after erasing
    std::cout << "Elements after erasing at position 1: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Reverse the list
    myList.reverse();

    // Display the reversed list
    std::cout << "Reversed elements in the list: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    // Sort the list
    myList.sort();
    myList.unique();

    // Display the sorted list
    std::cout << "Sorted elements in the list: ";
    for (node<int>* current = myList.begin(); current != myList.end()->m_next; current = current->m_next) {
        std::cout << current->m_data << " ";
    }
    std::cout << std::endl;

    return 0;
}
