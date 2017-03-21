//Second stack header file for the expression tree
#include <iostream>
#pragma once

struct Scstack{
  char fir[15];
  Scstack* next;
};
class scstack{
 public:
  char* peek();
  char* pop();
  void push(char* fir);
 private:
  Scstack* head = NULL;
};
