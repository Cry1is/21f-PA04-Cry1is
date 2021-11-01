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

    void push(T&);
    void pop();
    T& peek();
    bool isEmpty();

    DSLinkedList<T>& getList();

    friend std::ostream& operator<< <>(std::ostream&, const DSStack<T>&);
};

template <class T>
DSStack<T>::DSStack() {
    stack = new DSLinkedList<T>();
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
DSLinkedList<T>& DSStack<T>::getList() {
    return *stack;
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