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
    this->next = NULL;
    this->prev = NULL;
}

template <class T> Node<T>::Node(T data) {
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
}

template <class T> Node<T>::~Node() {
    
}

#endif