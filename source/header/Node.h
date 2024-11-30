#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;
template <class T> class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node();
    Node(T data);
    ~Node();
};

template <class T> Node<T>::Node() {
    this->next = nullptr;
    this->prev = nullptr;
}

template <class T> Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template <class T> Node<T>::~Node() {
    // nothing to do here
}

#endif