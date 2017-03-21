//second stack cpp file for expression tree
#include <iostream>
#include "scstack.h"
#include <cstring>

using namespace std;
//peeking at the top of the stack
char* scstack::peek(){
  return head == NULL ? NULL : head->fir;
}
//pushing onto the top of the stack
void scstack::push(char* fir){
  Scstack* current = new Scstack();
  current->next = head;
  strcpy(current->fir, fir);
  head = current;
}
//popping off the head's char value
char* scstack::pop(){
  if(head != NULL){
    char* t = new char[15];
    strcpy(t,head->fir);
    Scstack* current = head;
    head = head->next;
    delete current;
    return t;
  }
  else{
    return 0;
  }
}
