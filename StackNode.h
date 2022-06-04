#ifndef _STACKNODE_H_
#define _STACKNODE_H_

template <class T> class StackNode {
public:
  T data;
  StackNode<T> *next;
  StackNode();
  StackNode(T val);
};

template <class T> StackNode<T>::StackNode() : data{}, next{nullptr} {}

template <class T> StackNode<T>::StackNode(T val) {
  data = val;
  next = nullptr;
}

#endif // _STACKNODE_H_