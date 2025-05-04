// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>
template<typename T>
class TPQueue {
 private:
  struct Node {
    Node* next;
    T data;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };
  Node* head;
 public:
  TPQueue() : head(nullptr) {}
  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
      }
  }
  void push(const T& el) {
    Node* nNode = new Node(el);
    if (el.prior > head->data.prior || head == nullptr) {
      nNode->next = head;
      head = nNode;
    } else {
      Node* curr = head;
      Node* prev = nullptr;
      while (curr != nullptr && curr->data.prior >= el.prior) {
        prev = curr;
        curr = curr->next;
      }
      prev->next = nNode;
      nNode->next = curr;
    }
  }
  bool isEmpty() const { return head == nullptr; }
  T pop() {
    if (isEmpty())
      throw std::runtime_error("queue is empty");
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
