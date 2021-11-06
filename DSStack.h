//
// Created by Zachary on 10/30/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSSTACK_H
#define INC_21F_FLIGHT_PLANNER_DSSTACK_H

#endif //INC_21F_FLIGHT_PLANNER_DSSTACK_H
template <class T> class DSStack;

template <class T> std::ostream& operator<<(std::ostream&, const DSStack<T>&);

template <class T>
class DSStack {
private:
    DSLinkedList<T>* stack;
public:
    DSStack();
    DSStack(const DSStack<T>&);
    ~DSStack();

    DSStack<T>& operator=(const DSStack<T>&);
    bool operator==(const DSStack<T>&) const;

    void push(T&);
    void pop();
    T& peek();
    bool isEmpty();

    std::string toString();

    friend std::ostream& operator<< <>(std::ostream&, const DSStack<T>&);
};

template <class T>
DSStack<T>::DSStack() {
    stack = new DSLinkedList<T>();
}

template <class T>
DSStack<T>::DSStack(const DSStack<T>& other) {
    this->stack =  new DSLinkedList<T>(*other.stack);
}

template <class T>
DSStack<T>::~DSStack() {
    delete stack;
}

template <class T>
DSStack<T>& DSStack<T>::operator=(const DSStack<T>& other) {
    delete stack;
    stack = new DSLinkedList<T>();
    Node<T>* temp = other.stack->getHead();
    while (temp != nullptr) {
        this->stack->push_back(temp->data);
        temp = temp->next;
    }
    return *this;
}

template <class T>
bool DSStack<T>::operator==(const DSStack<T>& other) const {
    return *this->stack == *other.stack;
}

template <class T>
void DSStack<T>::push(T& val) {
    stack->push_back(val);
}

template <class T>
void DSStack<T>::pop() {
    stack->pop_back();
}

template <class T>
T& DSStack<T>::peek() {
    return stack->getTail()->data;
}

template <class T>
bool DSStack<T>::isEmpty() {
    return stack->isEmpty();
}

template <class T>
std::string DSStack<T>::toString() {
    return stack->toString();
}

template <class T>
std::ostream& operator<<(std::ostream& fout, const DSStack<T>& s) {
    DSLinkedList<T>* l = s.stack;
    Node<T>* temp = l->getHead();
    while (temp != nullptr) {
        fout << temp->data;
        if (temp->next != nullptr)
            fout << " -> ";
        temp = temp->next;
    }
    return fout;
}