#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

template <class T> class LinkedList {
    Node<T>* head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    void add(const T &data);
    void remove(int index);
    void remove(Node<T>* node);
    // void display();
    int getSize() const;

    bool isEmpty();

    // Trả về phần tử ở vị trí index
    T &elementAt(int);

    bool contains(T data);
    bool contains(Node<T>* node);

    // Trả về head->next
    Node<T>* begin() const;   
    // Trả về head
    Node<T>* end() const;   
    // Trả về head->prev
    Node<T>* last() const;
};

template <class T> LinkedList<T>::LinkedList() {
    this->head = new Node<T>;
    this->head->next = this->head;
    this->head->prev = this->head;
    this->size = 0;
}

template <class T> LinkedList<T>::~LinkedList() {
    Node<T> *temp = this->head->next;
    Node<T> *prev;
    while(temp != this->head) {
        prev = temp;
        temp = temp->next;
        delete prev;
    }
    delete this->head;
}

/**
 * @brief Thêm một phần tử vào cuối danh sách.
 */
template <class T> void LinkedList<T>::add(const T &data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = this->head;
    newNode->prev = this->head->prev;
    this->head->prev->next = newNode;
    this->head->prev = newNode;
    ++this->size;
}

template <class T> void LinkedList<T>::remove(int pos) {
    if(pos < 0 || pos >= this->size) {
        return;
    }
    int index = 0;
    Node<T> *temp = this->begin();
    while(temp != this->end()) {
        if(index == pos) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            --this->size;
            return;
        }
        index++;
        temp = temp->next;
    }
}

template <class T> void LinkedList<T>::remove(Node<T>* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --this->size;
}

template <class T> Node<T>* LinkedList<T>::begin() const {
    return head->next; 
}

template <class T> Node<T>* LinkedList<T>::end() const {
    return head; 
}

template <class T> Node<T>* LinkedList<T>::last() const {
    return head->prev; 
}

template <class T> int LinkedList<T>::getSize() const{
    return this->size;
}

template <class T> bool LinkedList<T>::isEmpty() {
    return this->size == 0;
}

template <class T> T &LinkedList<T>::elementAt(int index) {
    int i = 0;
    Node<T> *temp = this->begin();
    while(temp != this->end()) {
        if(i == index) {
            return temp->data;
        }
        ++i;
        temp = temp->next;
    }
}

template <class T> bool LinkedList<T>::contains(T data) {
    Node<T> *temp = this->begin();
    while(temp != this->end()) {
        if(temp->data == data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <class T> bool LinkedList<T>::contains(Node<T>* node) {
    Node<T> *temp = this->begin();
    while(temp != this->end()) {
        if(temp == node) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

#endif