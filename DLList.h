#ifndef DL_LIST_H
#define DL_LIST_H

#include <cstdlib>

template <typename T>
class ListNode{
public:
  ListNode(T d);
  ~ListNode();
  T data;
  ListNode<T>* next;
  ListNode<T>* prev;

};

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  next = NULL;
  prev = NULL;
}

template <typename T>
class DLList{
public:
  DLList();
  ~DLList();
  int size();
  bool isEmpty();
  void insertFront(T d);
  void insertBack(T d);
  void insertAt(int p, T d);
  T removeFront();
  T removeBack();
  T removeFrom(int p);
  T peek(int p);
  //methods to get data at place without removing

private:
  ListNode<T>* front;
  ListNode<T>* back;
  int m_size;
};

template <typename T>
DLList<T>::DLList(){
  front = NULL;
  back = NULL;
  m_size = 0;
}

template <typename T>
DLList<T>::~DLList(){
  //loop through list and delete all nodes
  front = NULL;
  back = NULL;
}

template <typename T>
bool DLList<T>::isEmpty(){
  return (m_size==0);
}

template <typename T>
int DLList<T>::size(){
  return m_size;
}

template <typename T>
void DLList<T>::insertFront(T d){
  ListNode<T>* newNode = new ListNode<T>(d);
  if(isEmpty()){
    back = newNode;
  } else{
    front->prev = newNode;
  }
  newNode->next = front;
  front = newNode;
  ++m_size;
}

template <typename T>
void DLList<T>::insertBack(T d){
  ListNode<T>* newNode = new ListNode<T>(d);
  if(isEmpty()){
    front = newNode;
  } else{
    back->next = newNode;
    newNode->prev = back;
  }
  back = newNode;
  ++m_size;
}

template <typename T>
void DLList<T>::insertAt(int p, T d){
  //make sure valid position


  if(isEmpty()){
    insertFront(d);
    return;
  }
  if(p>=m_size-1){
    insertBack(d);
    return;
  }
  ListNode<T>* newNode = new ListNode<T>(d);
  int currIdx = 0;
  ListNode<T>* currNode = front;
  while(currIdx < p){
    ++currIdx;
    currNode = currNode->next;
  }
  newNode->next = currNode->next;
  currNode->next->prev = newNode;
  newNode->prev = currNode;
  currNode->next = newNode;
    ++m_size;


}
//NEED TO FREE MEMORY
template <typename T>
T DLList<T>::removeFront(){
  //assume non empty list
  T ret = front->data;
  if(front->next == NULL){ //single item
    back = NULL;
  } else{
    front->next->prev = NULL;
  }
  front=front->next;
  --m_size;

  return ret;
}

template <typename T>
T DLList<T>::removeBack(){
  //assume non-empty list
  T ret = back->data;
  if(front->next==NULL){
    front = NULL;
  } else{
    back->prev->next = NULL;
  }
  back = back->prev;
  --m_size;
  return ret;
}

template <typename T>
T DLList<T>::removeFrom(int p){
  //assume non-empty

  if(p>=m_size-1){
    return removeBack();
  }
  --m_size;
  int currIdx = 0;
  ListNode<T>* currNode = front;
  while(currIdx < p){
    ++currIdx;
    currNode = currNode->next;
  }
  T ret = currNode->next->data;
  currNode->next->prev = NULL;
  currNode->next->next->prev = currNode;
  currNode->next = currNode->next->next;
  //the thing we want to delete still has active next pointer
  return ret;
}

template <typename T>
T DLList<T>::peek(int p){
  //assume non-empt
  if(p<=0){
    return front->data;
  }
  int currIdx = 0;
  ListNode<T>* currNode = front;
  while(currIdx < p){
    ++currIdx;
    currNode = currNode->next;
  }
  T ret = currNode->data;

  return ret;
}

#endif
