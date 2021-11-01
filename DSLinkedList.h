//
// Created by Zachary on 10/29/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H
#define INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H

#include <ostream>

template <class T>
struct Node {
    Node<T>* next,* prev;
    T data;
    Node(T data) {
        next = nullptr;
        prev = nullptr;
        this->data = data;
    }
};

template <class T> class DSLinkedList;

template <class T> std::ostream& operator<<(std::ostream&, const DSLinkedList<T>&);

template <class T>
class DSLinkedList {
private:
    Node<T>* head,* tail,* itr;
public:
    DSLinkedList();

    Node<T>* getHead();
    Node<T>* getTail();
    Node<T>* getItr();

    void moveItr();
    void resetItr();

    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();

    bool insertAfter(T&, T);
    bool insertBefore(T&, T);

    bool contains(T&);
    Node<T>* find(T&);
    bool remove(T&);

    bool isEmpty();

    friend std::ostream& operator<< <>(std::ostream&, const DSLinkedList<T>&);
};

template <class T>
DSLinkedList<T>::DSLinkedList() {
    head = nullptr;
    tail = nullptr;
    itr = nullptr;
}

template <class T>
Node<T>* DSLinkedList<T>::getHead() {
    return head;
}

template <class T>
Node<T>* DSLinkedList<T>::getTail() {
    return tail;
}

template <class T>
Node<T>* DSLinkedList<T>::getItr() {
    return itr;
}

template <class T>
void DSLinkedList<T>::moveItr() {
    itr = itr->next;
}

template <class T>
void DSLinkedList<T>::resetItr() {
    itr = head;
}

template <class T>
void DSLinkedList<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
        tail = head;
        itr = head;
    }
    else {
        tail->next = new Node<T>(data);
        tail->next->prev = tail;
        tail = tail->next;
    }
}

template <class T>
void DSLinkedList<T>::push_front(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
        tail = head;
        itr = head;
    }
    else {
        head->prev = new Node<T>(data);
        head->prev->next = head;
        head = head->prev;
        itr = head;
    }
}

template <class T>
void DSLinkedList<T>::pop_back() {
    if (head == tail) {
        if (tail != nullptr)
            delete tail;
        head = nullptr;
        tail = nullptr;
        itr = nullptr;
    }
    else {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
}

template <class T>
void DSLinkedList<T>::pop_front() {
    if (head == tail) {
        if (head != nullptr)
            delete head;
        head = nullptr;
        tail = nullptr;
        itr = nullptr;
    }
    else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        itr = head;
    }
}

template <class T>
bool DSLinkedList<T>::insertAfter(T& val, T data) {
    Node<T>* it = find(val);
    if (it != nullptr) {
        Node<T>* temp = new Node<T>(data);
        if (it == tail)
            tail = temp;
        temp->next = it->next;
        temp->prev = it;
        if (temp->next != nullptr)
            temp->next->prev = temp;
        it->next = temp;
        return true;
    }
    return false;
}

template <class T>
bool DSLinkedList<T>::insertBefore(T& val, T data) {
    Node<T>* it = find(val);
    if (it != nullptr) {
        Node<T>* temp = new Node<T>(data);
        if (it == head) {
            head = temp;
            if (itr == it)
                itr = temp;
        }
        temp->next = it;
        temp->prev = it->prev;
        if (temp->prev != nullptr)
            temp->prev->next = temp;
        it->prev = temp;
        return true;
    }
    return false;
}

template <class T>
bool DSLinkedList<T>::contains(T& val) {
    Node<T>* it = head;
    while (it != nullptr) {
        if (it->data == val)
            return true;
        it = it->next;
    }
    return false;
}

template <class T>
Node<T>* DSLinkedList<T>::find(T& val) {
    Node<T>* it = head;
    while (it != nullptr) {
        if (it->data == val)
            return it;
        it = it->next;
    }
    return nullptr;
}

template <class T>
bool DSLinkedList<T>::remove(T& val) {
    Node<T>* it = head;
    while (it != nullptr) {
        if (it->data == val) {
            if (it == head) {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
                itr = head;
            }
            else if (it == tail) {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            }
            else {
                it->prev->next = it->next;
                it->next->prev = it->prev;
                delete it;
            }
            return true;
        }
        it = it->next;
    }
    return false;
}

template <class T>
bool DSLinkedList<T>::isEmpty() {
    return head == nullptr;
}

template <class T>
std::ostream& operator<<(std::ostream& fout, const DSLinkedList<T>& l) {
    Node<T>* temp = l.head;
    while (temp != nullptr) {
        fout << temp->data;
        if (temp->next != nullptr)
            fout << " -> ";
        temp = temp->next;
    }
    return fout;
}

#endif //INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H
