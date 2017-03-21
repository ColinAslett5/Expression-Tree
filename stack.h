//stack header file for expression tree
#include <iostream>
#pragma once
struct Node{
  char fir;
  Node* next = NULL;//doesnt have to be set to null?
};

class stack{
 public:
  char peek();
  void push(char fir);
  char pop();
 private:
  Node* head = NULL;
};
