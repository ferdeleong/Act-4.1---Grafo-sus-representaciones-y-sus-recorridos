#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "StackNode.h"
#include <iostream>
#include <stdexcept>

template <class T> class StackLinkedList {
private:
  StackNode<T> *front;
  int numElements;

public:
  StackLinkedList();
  ~StackLinkedList();
  int getNumElements();
  void print();
  bool isEmpty();
  void push(T value);
  void pop();
  T getTop();
};

template <class T> StackLinkedList<T>::StackLinkedList() {
  std::cout << "--->Creando un stack vacio" << std::endl;
  front = nullptr;
  numElements = 0;
}

template <class T> StackLinkedList<T>::~StackLinkedList() {
  std::cout << "--->Liberando memoria del stack" << std::endl;
  StackNode<T> *p, *q;
  p = front;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  front = nullptr;
  numElements = 0;
}
template <class T> int StackLinkedList<T>::getNumElements() {
  return numElements;
}

template <class T> void StackLinkedList<T>::print() {
  StackNode<T> *ptr = front;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

template <class T> bool StackLinkedList<T>::isEmpty() {
  return (front == nullptr);
}

template <class T> void StackLinkedList<T>::push(T value) {
  StackNode<T> *newStackNode = new StackNode<T>(value);
  newStackNode->next = front;
  front = newStackNode;
  numElements++;
}

template <class T> void StackLinkedList<T>::pop() {
  if (!isEmpty()) {
    StackNode<T> *p = front;
    front = p->next;
    delete p;
    numElements--;
  }
}

template <class T> T StackLinkedList<T>::getTop() {
  T value = {};
  if (!isEmpty())
    value = front->data;
  return value;
}

#endif // _LINKEDLIST_H_