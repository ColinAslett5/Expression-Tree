//Colin Aslett, C++ Period 07, Expression Tree
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
struct Second{
  char first[10];
  Second* nex;
};
struct Tree{
  char* token;
  Tree* left = NULL;
  Tree* right = NULL;
  ~Tree(){
    delete[] token;
  }
};
Node* head = NULL;
Second* head2 = NULL;
//functions for initial infix to postfix
void push(char* ch,int a,char* as);
Node* peek();
Node* pop();
//functions for second stack
void push2(char* x);
char* peek2();
char* pop2();
//tree stuff
Tree* getTree();
//Is it an operator
bool isOperator(char a);
bool isOperator(char* a);
bool isOperator(Tree* tree);
int main(){
  cout << "Enter a Infix Expression!" << endl;
  char input[128];
  cin.getline(input,128);
  bool kg = false;
  int i = 0;
  size_t length = strlen(input);
  char infix[length];
  infix[0] = '\0';
  while(kg == false){
    push(input,i,infix);
    i++;
    if(i == length){
      //end of queue
      while(head != NULL){
	Node* check = head;
	Node* prev = head;
	if(check->fir[0] != '('){
	  size_t len = strlen(infix);
	  infix[len] = check->fir[0];
	  infix[len+1] = '\0';
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
	cout << "FINAL ANSWER: " << infix << endl;
      }
      kg = true;
    }
  }
  //New Stuff
  int x = 0;
  while(infix[x]){
    if(infix[x] == ' '){
      x++;
      continue;
    }
    if(isdigit(infix[x])){
      char n[10];
      int i = 0;
      while(isdigit(infix[x])){
	n[i++] = infix[x++];
      }
      n[i++] = '\0';
      push2(n);
    }
    else{
      //has to be an operator at this point
      char oper[2] = {infix[x++],'\0'};
      push2(oper);
    }
  }
  //line 73
  Tree* root = getTree();
  //cout << "enter prefix,postfix, or infix" << endl;
  return 0;
}
//pushing for the second stack
void push2(char* x){
  Second* current = new Second;
  current->nex = head2;
  strcpy(current->first,x);
  head2 = current;
}
//points to the root of the expression tree based on the postfix expression given
Tree* getTree(){
  cout << "ahh" << endl;
  cout << peek2();
  if(isOperator(peek2())){
    Tree* tree = new Tree();
    tree->token = pop2();
    tree->right = getTree();
    tree->left = getTree();
    return tree;
  }
  else{
    Tree* rootx = new Tree();
    rootx->token = pop2();
    return rootx;
  }
}
//peeking for the second stack
char* peek2(){
  return head2 == NULL ? NULL : head2->first;
}
//popping for the second stack
char* pop2(){
  if(head2 != NULL){
    char* temp = new char[10];
    strcpy(temp,head2->first);
    Second* current = head2;
    head2 = head2->nex;
    delete current;
    return temp;
  }
  else{
    return 0;
  }
}
//pushing the char to either the output queue or to the stack
void push(char* ch,int a,char* as){
  if(isdigit(ch[a])){
    //cout << "digit" << endl;
    size_t len = strlen(as);
    as[len] = ch[a];
    as[len+1] = '\0';
    //cout << "output queue: " << as << endl;
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
	  //cout << "hello" << endl;
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
      //cout << "NEW NODEs" << endl;
    }
    Node* prin = head;
    while(prin != NULL){
      //cout << prin->fir[0] << " , " << prin->pre << endl;
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
//all of the is operators
bool isOperator(char a){
  return a == '+' || a == '/' || a == '-' || a == '*' || a == '^';
}
bool isOperator(Tree* tree){
  return isOperator(tree->token);
}
bool isOperator(char* a){
  return isOperator(*a);
}
