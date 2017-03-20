//Colin Aslett, C++ Period 07, Shunting Yard Algorithm
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
using namespace std;
struct Node{
  char fir[1];
  Node* next;
  int pre;
};
Node* head = NULL;
void push(char* ch,int a,char* as);
Node* peek();
Node* pop();
int main(){
  cout << "HELLO!" << endl;
  char input[100];
  cin.getline(input,100);
  //taking out spaces
  bool kg = false;
  int i = 0;
  size_t length = strlen(input);
  //cout << "length of input: " << length << endl;
  char ans[length];
  ans[0] = '\0';
  while(kg == false){
    push(input,i,ans);
    i++;
    if(i == length){
      //end of queue
      while(head != NULL){
	Node* check = head;
	Node* prev = head;
	cout << "THE END THE END" << endl;
	if(check->fir[0] != '('){
	  size_t len = strlen(ans);
	  ans[len] = check->fir[0];
	  ans[len+1] = '\0';
	}
	if(check->next != NULL){
	  prev = check->next;
	}
	else{
	  prev = NULL;
	}
	//check = NULL;
	delete check;
	head = prev;
	cout << "FINAL ANSWER: " << ans << endl;
      }
      kg = true;
    }
  }
  return 0;
}
//pushing the char to either the output queue or to the stack
void push(char* ch,int a,char* as){
  if(isdigit(ch[a])){
    cout << "digit" << endl;
    size_t len = strlen(as);
    as[len] = ch[a];
    as[len+1] = '\0';
    cout << "output queue: " << as << endl;
  }
  if(ch[a] == '-' || ch[a] == '+' || ch[a] == '*' || ch[a] == '/' || ch[a] == '^'){
    int prec;//precedence
    if(ch[a] == '-'){
      prec = 2;
    }
    if(ch[a] == '+'){
      prec = 2;
    }
    if(ch[a] == '/'){
      prec = 3;
    }
    if(ch[a] == '*'){
      prec = 3;
    }
    if(ch[a] == '^'){
      prec = 4;
    }
    Node* current = head;
    if(current == NULL){
      head = new Node;
      head->next = NULL;
      head->fir[0] = ch[a];
      head->pre = prec;
    }
    else{
      while(peek()->pre > prec || peek()->pre == prec){
	if(peek()->pre == 4 & prec == 4){
	  break;
	}
	else{
	  cout << "hello" << endl;
	  Node* nn = pop();
	  if(ch[a] != '('){
	    size_t leng = strlen(as);
	    as[leng] = nn->fir[0];
	    as[leng+1] = '\0';
	  }
          delete nn;
	}
        if(peek() == NULL){
	  break;
	}
      }
      Node* temp = new Node;
      temp->next = head;
      temp->fir[0] = ch[a];
      temp->pre = prec;
      head = temp;
      cout << "NEW NODEs" << endl;
    }
    Node* prin = head;
    while(prin != NULL){
      cout << prin->fir[0] << " , " << prin->pre << endl;
      prin = prin->next;
    }    
  }
  if(ch[a] == ')' || ch[a] == '('){
    if(ch[a] == ')'){
      while(peek()->fir[0] != '('){
	Node* nnn = pop();
	if(ch[a] != '('){
	  size_t lengx = strlen(as);
	  as[lengx] = nnn->fir[0];
	  as[lengx+1] = '\0';
	}
	delete nnn;
      }
    }
    if(ch[a] == '('){
      Node* tempx = new Node;
      tempx->next = head;
      tempx->fir[0] = ch[a];
      tempx->pre = 0;
      head = tempx;
    }
  }
}
//peeking at the head of the stack
Node* peek(){
  return head;
}
//popping the thingy off the stack
Node* pop(){
  if(head == NULL){
    return NULL;
  }
  Node* temp = head;
  head = head->next;
  return temp;
}
