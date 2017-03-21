//Colin Aslett, C++ Period 07, Expression Tree, Can do various things, most likely
#include <iostream>
#include "stack.h"
#include "scstack.h"
#include <cstring>
//i have more than one thing for checking for operators and precedence because of ISO c++ rules or whatever
using namespace std;
//its a tree yo, it holds the expressions and children 
struct Tree{
  char* first;
  Tree* left = NULL;
  Tree* right = NULL;
  ~Tree(){
    delete[] first;
  }
};
char* Postfix(char* input);//translating from infix to postfix
bool isOperator(char x);
bool isOperator(char* x);
bool isOperator(Tree* root);
int precedence(char x);
int precedence(char* x);
int precedence(Tree* root);
bool left(char x);
void printPostfix(Tree* root);
void printInfix(Tree* root);
void Prefix(Tree* root);
void deleteTree(Tree* root);
Tree* getTree(scstack &infix);
int main(){
  char input[100];
  bool kg = true;
  cout << "enter a infix expression" << endl;
  cin.getline(input,100);
  char* infix = Postfix(input);//the char array infix will hold the translation of infix to postfix
  cout << infix << endl;
  scstack sc;//making the second stack for translation, tree stack
  int a = 0;
  while(infix[a]){
    if(infix[a] == ' '){
      a++;
      continue;
    }
    if(isdigit(infix[a])){
      char ans[100];
      int i = 0;
      while(isdigit(infix[a])){
	ans[i++] = infix[a++];
      }
      ans[i++] = '\0';
      sc.push(ans);
    }
    //only can be an operaotr at this point
    else{
      char ax[2] = {infix[a++],'\0'};
      sc.push(ax);
    }
  }
  delete[] infix;
  Tree* root = getTree(sc);
  //what conversion/translation do you want?
  cout << "infix?prefix?postfix?" << endl;
  char inputx[128];
  cin.getline(inputx,128);
  if(strcmp(inputx,"prefix")==0){
    Prefix(root);
  }
  else if(strcmp(inputx,"postfix")==0){
    printPostfix(root);
  }
  else if(strcmp(inputx,"infix")==0){
    printInfix(root);
  }
  else{
    cout << "uh, thats not one of the commands" << endl; 
  }
  deleteTree(root);
  return 0;
}
char* Postfix(char* input){
  stack st;
  char* postfix = new char[((strlen(input)+1)*3)];
  int indexin = 0;
  int indexpost = 0;
  while(input[indexin]){
    //empty space, continue on
    if(input[indexin] == ' '){
        indexin++;
        continue;
    }
    //a digit, we can add it in onto the prefix char array
    if(isdigit(input[indexin])){
        while(isdigit(input[indexin])){
	  postfix[indexpost++] = input[indexin++];
        }
        postfix[indexpost++] = ' ';
    }
    //an operator, check for conditions, then add it onto the stack
    else if(isOperator(input[indexin])){
        while(isOperator(st.peek()) &&
               ( (left(input[indexin]) &&  precedence(input[indexin]) <= precedence(st.peek()))
            || (!left(input[indexin]) && precedence(input[indexin]) < precedence(st.peek())))){
                postfix[indexpost++] = st.pop();
                postfix[indexpost++] = ' ';
        }
        st.push(input[indexin++]);
    }
    //right facing paranthesis, add it to the stack 
    else if(input[indexin] == '('){
        st.push(input[indexin++]);
    }
    //left facing paranthesis, POP EVERYTHING IN THE STACK
    else if(input[indexin] == ')'){
        while(st.peek() != '('){
            postfix[indexpost++] = st.pop();
            postfix[indexpost++] = ' ';
            if(st.peek() == 0){
                cout << "Error: mismatched parentheses." << endl;
                break;
            }
        }
        st.pop();
        indexin++;
    }
  }
  while(st.peek()){
     postfix[indexpost++] = st.pop();
     postfix[indexpost++] = ' ';
  }
  postfix[indexpost-1] = 0;
  return postfix;
}
//is it left or right?
bool left(char x){
  return x != '^';
}
//checks for operator, all 3 different types of possible combinations for trees and chars
bool isOperator(char x){
  if(x == '+' || x == '-' || x == '^' || x == '*' || x == '/'){
    return true;
  }
  else{
    return false;
  }
}
bool isOperator(char* x){
  return isOperator(*x);
}
bool isOperator(Tree* root){
  return isOperator(root->first);
}
//determines precedence for all three different types of inputs
int precedence(char x){
  if(x == '+' || x == '-'){
    return 1;
  }
  if(x == '*' || x == '/'){
    return 2;
  }
  if(x == '^'){
    return 3;
  }
  return -1;
}
int precedence(char* x){
  return precedence(*x);
}
int precedence(Tree* root){
  return precedence(root->first);
}
//creating the tree dude
Tree* getTree(scstack &infix){
  if(isOperator(infix.peek())){
    Tree* current = new Tree();
    current->first = infix.pop();
    current->right = getTree(infix);
    current->left = getTree(infix);
    return current;
  }
  else{
    Tree* currentx = new Tree();
    currentx->first = infix.pop();
    return currentx;
  }
}
//postfix printing out
void printPostfix(Tree* root){
  if(isOperator(root->first)){
    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->first << ' ';
  }
  else{
    cout << root->first << ' ';
  }
}
//infix printing out
void printInfix(Tree* root){
  if(isOperator(root->first)){
    if(isOperator(root->left)){
      printInfix(root->left);
    }
    else{
      printInfix(root->left);
    }
    cout << root->first << ' ';
    if(isOperator(root->right)){
      printInfix(root->right);
    }
    else{
      printInfix(root->right);
    }
  }
  else{
    cout << root->first << ' ';
  }
}
//prefix printing out
void Prefix(Tree* root){
  if(isOperator(root->first)){
    cout << root->first << ' ';
    Prefix(root->left);
    Prefix(root->right);
  }
  else{
    cout << root->first << ' ';
  }
}
//deleting the tree
void deleteTree(Tree* root){
  //if it is not empty than we gotta destroy its children
  if(root != 0){
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}
