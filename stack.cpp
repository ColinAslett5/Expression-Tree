//Stack cpp file for expression tree
#include <iostream>
#include "stack.h"

using namespace std;
//peeking at the char value in the head
char stack::peek(){
  //return head->fir;
  return head == NULL ? '\0' : head->fir;
}
//pushing a char value onto the stack
void stack::push(char fir){
  Node* current = new Node();
  current->next = head;
  current->fir = fir;
  head = current;
}
char stack::pop(){
  //if there is something at the top then we gotta pop it off
  if(head != NULL){
    char temp = head->fir;
    Node* current = head;
    head = head->next;
    delete current;
    return temp;
  }
  //nothing is there so nothing to return
  else{
    
    return 0;
  }
}
